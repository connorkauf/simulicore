#include "types_test.hpp"
#include "utils_test.hpp"

#include "cla3p/src/error_internal.hpp"

int main()
{
	cla3p::enable_dbg_messages();
	bool strict = true;

	cla3p::tests::datatypes(strict);
	cla3p::tests::utilities(strict);

	return 0;
}
