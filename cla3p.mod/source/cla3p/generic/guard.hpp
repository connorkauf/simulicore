#ifndef CLA3P_GUARD_HPP_
#define CLA3P_GUARD_HPP_

/**
 * @file
 * The Guard class
 */

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/
/**
* @ingroup guard
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
		Guard();

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
		Guard(const T_Object& obj);

		/**
		 * @brief The input assignment operator.
		 *
		 * Constructs guard with a referenced copy of obj.
		 */
		Guard<T_Object>& operator=(const T_Object& obj);

		/**
		 * @brief The object being guarded.
		 * @return A constant reference to the object being guarded.
		 */
		const T_Object& get() const;

	protected:
		T_Object m_obj;
};
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::Guard()
{
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::~Guard()
{
	m_obj.clear();
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::Guard(const Guard<T_Object>& other)
{
	*this = other.get();
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>& Guard<T_Object>::operator=(const Guard<T_Object>& other)
{
	*this = other.get();
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::Guard(const T_Object& obj)
{
	m_obj = const_cast<T_Object&>(obj).rcopy();
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>& Guard<T_Object>::operator=(const T_Object& obj)
{
	m_obj = const_cast<T_Object&>(obj).rcopy();
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Object>
const T_Object& Guard<T_Object>::get() const
{
	return m_obj;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GUARD_HPP_
