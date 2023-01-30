#include "types_test.hpp"
#include "utils_test.hpp"
#include "bulk_dns_test.hpp"

#include <string>

#include "cla3p/src/error_internal.hpp"

int main(int argc, const char **argv)
{
  bool strict = false;

	if(argc > 1) {
		if(std::stoi(argv[1])) {
			cla3p::enable_dbg_messages();
			strict = false;
		} // argv
	} // argc

	cla3p::tests::datatypes(strict);
	cla3p::tests::utilities(strict);
	cla3p::tests::bulk_dns(strict);

	return 0;
}
