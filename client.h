#include "lasote/lambda_http_client/http_request.h"
#include "hjiang/jsonxx/jsonxx.h"
#include <string.h>
#include <iostream>
#include <functional>
#include <memory>
#include <fstream>

using namespace httpmodels;
using namespace lasote;

#define JSON_OBJECT jsonxx::Object
#define JSON_ARRAY jsonxx::Array
#define JSON_F function<void(JSON_OBJECT)>
#define VOID_F function<void(void)>
#define ERR_F function<void(int status, string desc)>
#define CHAR_PTR_F function<void(const char*, long unsigned int)>

void run_loop();

class TembooClient{
	public:
		TembooClient(string account_name, string user, string password);
		
		//Choreos
		shared_ptr<LambdaRequest> list_choreos(JSON_F ret_cb, ERR_F err_cb);
		shared_ptr<LambdaRequest> details_choreos(JSON_F ret_cb, ERR_F err_cb, string choreos_id);
		shared_ptr<LambdaRequest> run_choreos(JSON_F ret_cb, ERR_F err_cb, string choreos_id);

		//Executions
		shared_ptr<LambdaRequest> list_choreos_executions(JSON_F ret_cb, ERR_F err_cb);
		shared_ptr<LambdaRequest> get_choreo_executions(JSON_F ret_cb, ERR_F err_cb, string choreos_id);
		shared_ptr<LambdaRequest> delete_choreo_executions(VOID_F ret_cb, ERR_F err_cb, string choreos_id);
		
		string account_name;
		string uri;
		string user;
		string password;
	private:
		shared_ptr<LambdaRequest> call_delete(string path, VOID_F ret_cb, ERR_F err_cb);
		shared_ptr<LambdaRequest> call_get(string path, JSON_F ret_cb, ERR_F err_cb, CHAR_PTR_F on_body_cb=CHAR_PTR_F());
		shared_ptr<LambdaRequest> call_post(string path, string body, JSON_F ret_cb, ERR_F err_cb, CHAR_PTR_F on_body_cb=CHAR_PTR_F());
		shared_ptr<LambdaRequest> call_and_parse_response(Request& request, JSON_F ret_cb, ERR_F err_cb, CHAR_PTR_F on_body_cb=CHAR_PTR_F());
		
};

