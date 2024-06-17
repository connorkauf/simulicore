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

#ifndef CLA3P_TIME_HPP_
#define CLA3P_TIME_HPP_

/** 
 * @file
 */

#include <chrono>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T_Rep>
class Timer {

	public:
		Timer()
		{
			reset();
		}

		~Timer()
		{
			stop();
		}

		void reset()
		{
			m_start = ClockType::now();
			m_end = m_start;
		}

		void stop()
		{
			m_end = ClockType::now();
		}

		T_Rep stoppedDiff() const
		{
			return timestampDiff(m_start, m_end);
		}

		T_Rep currentDiff() const
		{
			return timestampDiff(m_start, ClockType::now());
		}

	private:
		using ClockType = std::chrono::high_resolution_clock;
		using TimeStamp = std::chrono::time_point<ClockType>;
		using TimeDiffSeconds = std::chrono::duration<T_Rep, std::ratio<1>>;

		TimeStamp m_start;
		TimeStamp m_end;

		T_Rep timestampDiff(const TimeStamp& start, const TimeStamp& end) const
		{
			TimeDiffSeconds diff = end - start;
			return diff.count();
		}
};

/*-------------------------------------------------*/

class RealTimer : public Timer<real_t> {

	public:
		RealTimer();
		~RealTimer();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_TIME_HPP_
