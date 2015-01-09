# C++ Temboo Client

[Temboo Client](https://www.temboo.com/restapi/reference) implementation with C++11 using lambda functions for callbacks.

This library is hosted in **[Biicode](http://www.biicode.com) C++ dependency manager**.

Biicode block [lasote/temboo_client](http://www.biicode.com/lasote/temboo_client)

Also in [github repository https://github.com/lasote/temboo_client](https://github.com/lasote/temboo_client)


### Build status

*Visual Studio 2012:* [![Build status](https://ci.appveyor.com/api/projects/status/h63fyc99s50y5dtn?svg=true)](https://ci.appveyor.com/project/lasote/temboo-client)

*Linux gcc:* [![Build Status](https://travis-ci.org/lasote/temboo_client.svg?branch=master)](https://travis-ci.org/lasote/temboo_client)

### Want to try it?

The project has many dependencies, we recommend you to use [biicode](http://www.biicode.com) to handle them:

[Get started with biicode](http://docs.biicode.com/c++/gettingstarted.html)

Include this header in your source code file:

    #include "lasote/temboo_client/client.h"

Download the required dependencies:

    bii find

Build the project:

    bii cpp:build # to build the project

Take a look to the example: http://www.biicode.com/examples/temboo_client


### How to use it?

Look the complete method list in client.h:

	#include "lasote/temboo_client/client.h"
	#include <iostream>

	using namespace lasote;

	int main() {

	  TembooClient client("lasote", "myFirstApp", "XXXXXXXXXXXXXXXXXXXXX");

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

