#include <iostream>
#include <cstdio>
#include <unistd.h>

#include <omp.h>

#include "cla3p/src/types.hpp"
#include "cla3p/src/test.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/dns_io.hpp"
#include "cla3p/src/error.hpp"
/*-------------------------------------------------*/
#if 0
static void omp_print()
{
	printf("tid: %d in parallel: %d dynamic: %d max levels: %d num procs: %d num threads: %d max threads: %d\n", 
			omp_get_thread_num(),
			omp_get_dynamic(),
			omp_get_max_active_levels(),
			omp_in_parallel(),
			omp_get_num_procs(),
			omp_get_num_threads(),
			omp_get_max_threads()
			);
}
#endif
/*-------------------------------------------------*/
int main()
{

	throw cla3p::MemoryException();

}
