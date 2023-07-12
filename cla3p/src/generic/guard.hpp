#ifndef CLA3P_GUARD_HPP_
#define CLA3P_GUARD_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/
template <typename T>
class Guard {

	public:
		Guard();
		~Guard();

		Guard(const Guard<T>&);
		Guard<T>& operator=(const Guard<T>&);

		Guard(const T&);
		Guard<T>& operator=(const T&);

		const T& get() const;

	protected:
		T m_obj;
};
/*-------------------------------------------------*/
template <typename T>
Guard<T>::Guard()
{
}
/*-------------------------------------------------*/
template <typename T>
Guard<T>::~Guard()
{
	m_obj.clear();
}
/*-------------------------------------------------*/
template <typename T>
Guard<T>::Guard(const Guard<T>& src)
{
	*this = src.get();
}
/*-------------------------------------------------*/
template <typename T>
Guard<T>& Guard<T>::operator=(const Guard<T>& other)
{
	*this = other.get();
	return *this;
}
/*-------------------------------------------------*/
template <typename T>
Guard<T>::Guard(const T& obj)
{
	m_obj = const_cast<T&>(obj).rcopy();
}
/*-------------------------------------------------*/
template <typename T>
Guard<T>& Guard<T>::operator=(const T& obj)
{
	m_obj = const_cast<T&>(obj).rcopy();
	return *this;
}
/*-------------------------------------------------*/
template <typename T>
const T& Guard<T>::get() const
{
	return m_obj;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GUARD_HPP_
