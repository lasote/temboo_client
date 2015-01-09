#include "client.h"
#include <memory>

TembooClient::TembooClient(string account_name, string user, string password) : account_name(account_name), user(user), password(password){
	uri = "http://" + account_name + ".temboolive.com/temboo-api/1.0";
}


shared_ptr<LambdaRequest> TembooClient::list_choreos(JSON_F ret_cb, ERR_F err_cb){
	string path = "/choreos";
    return call_get(path, ret_cb, err_cb);
}

shared_ptr<LambdaRequest> TembooClient::details_choreos(JSON_F ret_cb, ERR_F err_cb, string choreos_id){
	string path = "/choreos/" + choreos_id;
    return call_get(path, ret_cb, err_cb);
}

shared_ptr<LambdaRequest> TembooClient::run_choreos(JSON_F ret_cb, ERR_F err_cb, string choreos_id){
	string path = "/choreos/" + choreos_id;
    return call_post(path, "", ret_cb, err_cb);
}


shared_ptr<LambdaRequest> TembooClient::list_choreos_executions(JSON_F ret_cb, ERR_F err_cb){
	string path = "/choreo-executions";
    return call_get(path, ret_cb, err_cb);
}


shared_ptr<LambdaRequest> TembooClient::get_choreo_executions(JSON_F ret_cb, ERR_F err_cb, string choreos_id){
	string path = "/choreos-executions/" + choreos_id;
    return call_post(path, "", ret_cb, err_cb);
}


shared_ptr<LambdaRequest> TembooClient::delete_choreo_executions(VOID_F ret_cb, ERR_F err_cb, string choreos_id){
	string path = "/choreos-executions/" + choreos_id;
    return call_delete(path, ret_cb, err_cb);

}


shared_ptr<LambdaRequest> TembooClient::call_delete(string path, VOID_F ret_cb, ERR_F err_cb){
	Request request;
	Method method("DELETE", uri + path);
	request.method = &method;

    auto request_call = std::make_shared<LambdaRequest>();

	request_call->on_message_complete_cb = [request_call, ret_cb, err_cb] (int status) {
		if(status > 299){
			log_debug("Error calling: " << status);
			if(err_cb != NULL){
				err_cb(status, request_call->response_buffer);
			}
		}
		else{
			ret_cb();
		}
	};
	request_call->send(request);
	return request_call;
}


shared_ptr<LambdaRequest> TembooClient::call_get(string path, JSON_F ret_cb, ERR_F err_cb, CHAR_PTR_F on_body_cb){
	log_info(path);
	Request request;
	Method method("GET", uri + path);
	request.method = &method;
	return call_and_parse_response(request, ret_cb, err_cb, on_body_cb);
}

shared_ptr<LambdaRequest> TembooClient::call_post(string path, string body, JSON_F ret_cb, ERR_F err_cb, CHAR_PTR_F on_body_cb){
	log_info(path);
	Request request;
	Method method("POST", uri + path);
	request.method = &method;
	request.body = body;
	std::pair<string,string> content_type("Content-Type", "application/json");
    request.headers.insert(content_type);
    std::pair<string,string> content_len("Content-Length", to_string(body.length()));
    request.headers.insert(content_len);

    return call_and_parse_response(request, ret_cb, err_cb, on_body_cb);
}

shared_ptr<LambdaRequest> TembooClient::call_and_parse_response(Request& request, JSON_F ret_cb, ERR_F err_cb, CHAR_PTR_F on_body_cb){
	
	//PUT COMMON HEADERS
	std::pair<string,string> domain("x-temboo-domain", "/" + account_name + "/master");
    request.headers.insert(domain);

    std::pair<string,string> accept("application", "json");
    request.headers.insert(accept);

    //SET CREDENTIALS
    request.set_basic_auth_header(user, password);

	auto request_call = std::make_shared<LambdaRequest>();

	request_call->on_message_complete_cb = [request_call, ret_cb, err_cb] (int status) {
		if(status > 299){
			log_debug("Error calling: " << status);
			if(err_cb != NULL){
				err_cb(status, request_call->response_buffer);
			}
		}
		else{
			log_debug("Status: " << status << endl);
			JSON_OBJECT json_ret;
			if(request_call->response_buffer.length() > 0){
				if(request_call->response_buffer[0] == '{'){
					json_ret.parse(request_call->response_buffer);
					log_debug("Response JSON OBJECT: " << json_ret << endl);
				}
				else if(request_call->response_buffer[0] == '['){
					JSON_ARRAY json_tmp;
					json_tmp.parse(request_call->response_buffer);
					json_ret << "data" << json_tmp;
					log_debug("Response JSON ARRAY: " << json_tmp << endl);
				}
			}
			ret_cb(json_ret);
		}
	};
	request_call->on_body_cb = on_body_cb;
	request_call->send(request);
	return request_call;
}

void run_loop(){
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}

