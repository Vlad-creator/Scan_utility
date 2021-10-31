#include "include/includes.hpp"
#include "include/scan.hpp"
#include "include/suspicious.hpp"
#include "include/time.hpp"

using namespace susp;

int main(int argc , char* argv[])
{
	std::vector<form_susp> susps = fill_susps();

	scan::scan test(argv[1] , susps);
	test.scanning();
	test.dump();

	return 0;
}

///home/vladislav/again/LK_sc/tests/test_1