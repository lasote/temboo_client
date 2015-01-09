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


	  TembooClient client("lasote", "myFirstApp", "b5a322f22b16e4882b3d36c3dd82dc2f0");

	  ERR_F error_cb = [] (int status, string desc) {
		  cout << "Error: " << status <<  endl  << desc;
	  };


	  auto c3 = client.list_choreos_executions([] (jsonxx::Object out) {
	       cout << "Response: " << out << endl;
	  }, error_cb);


	  run_loop();
