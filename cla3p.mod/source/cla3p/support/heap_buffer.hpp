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

#ifndef CLA3P_HEAP_BUFFER_HPP_
#define CLA3P_HEAP_BUFFER_HPP_

/** 
 * @file
 */

#include "cla3p/support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T_Scalar>
class HeapBuffer {

	public:
		HeapBuffer()
		{
			defaults();
		}

		HeapBuffer(std::size_t nmemb)
		{
			resize(nmemb);
		}

		~HeapBuffer()
		{
			clear();
		}

		void resize(std::size_t nmemb)
		{
			if(nmemb > m_capacity) {
				try {
					m_capacity = nmemb;
					if(m_buffer)
						m_buffer = i_realloc<T_Scalar>(m_buffer, nmemb);
					else
						m_buffer = i_malloc<T_Scalar>(nmemb);
				} catch (...) {
					clear();
					throw;
				} // try
			} // needs expansion
		}

		T_Scalar* request(std::size_t nmemb)
		{
			T_Scalar *ret = nullptr;
			if(nmemb + m_offset <= m_capacity) {
				ret = m_buffer + m_offset;
				m_offset += nmemb;
			}
			return ret;
		}

		void rewind()
		{
			m_offset = 0;
		}

		void clear()
		{
			i_free(m_buffer);
			defaults();
		}

		const T_Scalar* data() const { return m_buffer; }
		T_Scalar* data() { return m_buffer; }

	private:
		std::size_t m_offset;
		std::size_t m_capacity;
		T_Scalar* m_buffer;

		void defaults()
		{
			m_offset = 0;
			m_capacity = 0;
			m_buffer = nullptr;
		}
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_HEAP_BUFFER_HPP_
