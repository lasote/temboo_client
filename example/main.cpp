#include "lasote/temboo_client/client.h"
#include <iostream>

using namespace lasote;

int main() {

  TembooClient client("lasote", "myFirstApp", "o28TvoyDF9QSQbZKl5F54niwn860cqKl");

  //Error callback
  ERR_F error_cb = [] (int status, string desc) {
	  cout << "Error: " << status <<  endl  << desc;
  };

  //keep return value from TembooClient, its necessary for asynchronous calls

  //Get available choreos for suplied credentials
  auto c1 = client.list_choreos([] (jsonxx::Object out) {
  	   auto arr = out.get<jsonxx::Array>("resources");
       cout << "Choreos first on list: " << arr.get<jsonxx::String>(0) << endl << endl;
  }, error_cb);


  // Details for choreos "Library/Google/Geocoding/GeocodeByAddress"
  auto c2 = client.details_choreos([] (jsonxx::Object out) {
       cout << "Details choreos: " << out << endl << endl;
  }, error_cb, "Library/Google/Geocoding/GeocodeByAddress");


  // Execute a choreos
  vector<pair<string, string>> params;
  pair<string, string> param1;
  param1.first = "Address"; param1.second = "Estadio Santiago Bernabeu";
  params.push_back(param1);

  auto c3 = client.run_choreos([param1] (jsonxx::Object out) {
  	   jsonxx::Object output = out.get<jsonxx::Object>("output");
       cout << "Address: " << param1.second << endl;
       cout << "Latitude: " << output.get<jsonxx::String>("Latitude") << endl;
       cout << "Longitude: " << output.get<jsonxx::String>("Longitude") << endl << endl;
  }, error_cb, "Library/Google/Geocoding/GeocodeByAddress", params);


  //Executions
  auto c4 = client.list_choreos_executions([] (jsonxx::Object out) {
       cout << "Executions: " << out << endl;
  }, error_cb);

  auto c5 = client.get_choreo_executions([] (jsonxx::Object out) {
       cout << "Response to run: " << out << endl;
  }, error_cb, "CHOREOS_EXEC_ID");

  auto c6 = client.delete_choreo_executions([] (void) {
        cout << "Deleted!";
  }, error_cb, "CHOREOS_EXEC_ID");


  // Now run all requests
  run_loop();
}
