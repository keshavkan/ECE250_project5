/****************************************************
 * Executable:   Weighted_graph_driver
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-9 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *
 * Create an instance of the Weighted_graph_tester class
 * and call the member function run().
 *
 * The member function run() will interpret the
 * input appropriately and exit when the interpreter
 * receives either the command 'exit' or and
 * end-of-file.
 ****************************************************/

#include <iostream>
#include "Weighted_graph_tester.h"

int main() {
	Weighted_graph_tester tester;

	std::cout << "Starting Test Run" << std::endl;

	tester.run();

	std::cout << "Finishing Test Run" << std::endl;



	return 0;
}
