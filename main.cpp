#include "include/includes.hpp"
#include "include/scan.hpp"
#include "include/suspicious.hpp"
#include "include/time.hpp"

/*!
 * Use TEST for compile and start Unit/E2E tests of this utility
 */

#ifdef TEST
	#include <gtest/gtest.h>
	#include "build/test_scan/start_test.h"
#endif

using namespace susp;

int main(int argc , char* argv[])
{
	#ifdef TEST
	    ::testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
	#endif
	std::vector<form_susp> susps = fill_susps();

	scan::scan test(argv[1] , susps);
	test.scanning();
	test.dump();

	return 0;
}