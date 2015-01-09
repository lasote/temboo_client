#include "lasote/temboo_client/client.h"
#include <iostream>

using namespace lasote;

int main() {

  TembooClient client("lasote", "myFirstApp", "b5a322f2b16e4882b3d36c3dd82dc2f0");

  ERR_F error_cb = [] (int status, string desc) {
	  cout << "Error: " << status <<  endl  << desc;
  };


  auto c3 = client.list_choreos_executions([] (jsonxx::Object out) {
       cout << "Response: " << out << endl;
  }, error_cb);


  run_loop();
}
