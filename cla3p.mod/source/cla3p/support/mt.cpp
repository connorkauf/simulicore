/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/support/mt.hpp"

// system
#include <omp.h>

// 3rd

// cla3p
#if defined(CLA3P_INTEL_MKL)
#include "cla3p/proxies/mkl_proxy.hpp"
#endif

/*-------------------------------------------------*/
namespace cla3p {
namespace mt {
/*-------------------------------------------------*/
void initialize()
{
#if defined(CLA3P_INTEL_MKL)
	mkl::set_num_threads(mkl::get_max_threads());
#endif
}
/*-------------------------------------------------*/
nint_t maxThreads()
{
	return omp_get_max_threads();
}
/*-------------------------------------------------*/
nint_t numThreads()
{
	return omp_get_num_threads();
}
/*-------------------------------------------------*/
nint_t threadId()
{
	return omp_get_thread_num();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
ThreadManager::ThreadManager()
{
	defaults();
}
/*-------------------------------------------------*/
ThreadManager::ThreadManager(nint_t numThreads)
{
	setNumThreads(numThreads);
}
/*-------------------------------------------------*/
ThreadManager::~ThreadManager()
{
	restoreNumThreads();
}
/*-------------------------------------------------*/
void ThreadManager::defaults()
{
	m_ompThreads = -1;
	m_mklThreads = -1;
}
/*-------------------------------------------------*/
void ThreadManager::setNumThreads(nint_t numThreads)
{
	m_ompThreads = omp_get_max_threads();
	omp_set_num_threads(numThreads);

#if defined(CLA3P_INTEL_MKL)
	m_mklThreads = mkl::get_max_threads();
	mkl::set_num_threads_local(numThreads);
#endif
}
/*-------------------------------------------------*/
void ThreadManager::restoreNumThreads()
{
	if(m_ompThreads >= 0)
		omp_set_num_threads(m_ompThreads);

#if defined(CLA3P_INTEL_MKL)
	if(m_mklThreads >= 0)
		mkl::set_num_threads_local(m_mklThreads);
#endif

	defaults();
}
/*-------------------------------------------------*/
} // namespace mt
} // namespace cla3p
/*-------------------------------------------------*/
