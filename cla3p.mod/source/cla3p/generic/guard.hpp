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

#ifndef CLA3P_GUARD_HPP_
#define CLA3P_GUARD_HPP_

/**
 * @file
 */

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/
/**
* @brief Encloses an object and prevents its contents from being changed.
*
* Some functions need to return objects that contain immutable data.
* The contents of these objects must be protected.
* The Guard class is used for preventing those data from being exposed to change.
*
* @include ex04a_guard_const_vector.cpp
*/

template <typename T_Object>
class Guard {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty guard.
		 */
		explicit Guard();

		/**
		 * @brief Destroys the guard.
		 */
		~Guard();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a guard with a referenced copy of the contents of other.
		 */
		Guard(const Guard<T_Object>& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of guard with a referenced copy of the contents of other.
		 */
		Guard<T_Object>& operator=(const Guard<T_Object>& other);

		/**
		 * @brief The input constructor.
		 *
		 * Constructs guard with a referenced copy of obj.
		 */
		explicit Guard(const T_Object& obj);

		/**
		 * @brief Clears the guard.
		 *
		 * Detaches contents and resets guard.
		 */
		void clear();

		/**
		 * @brief The object being guarded.
		 * @return A constant reference to the object being guarded.
		 */
		const T_Object& get() const;

	protected:
		T_Object m_obj;
};
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GUARD_HPP_
