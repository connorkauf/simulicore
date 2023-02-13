#ifndef CLA3P_GENERIC_DNS_HPP_
#define CLA3P_GENERIC_DNS_HPP_

#include <string>
#include <iostream>

#include "../types.hpp"
#include "universal.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace prm { class pMat; }
namespace dns {
/*-------------------------------------------------*/

/**
 * @brief The basic dense object generic class
 *
 * All dense objects inherit from this class
 */
template <typename T, typename Tr>
class GenericObject : public UniversalMetaData {

	public:

		// 
		// inherited args
		//

		/**
		 * @brief The values array
		 * @return The pointer to the numerical values of the object
		 */
		T* values();

		/**
		 * @brief The values array
		 * @return The pointer to the numerical values
		 */
		const T* values() const;

		// 
		// inherited methods - callable from empty
		//

		/**
		 * @brief Clears the object
		 */
		void clear();

		/**
		 * @brief Scales object by coeff
		 * @param[in] coeff The scaling coefficient
		 */
		void scale(T coeff);

		/**
		 * @brief Prints the contents of the object
		 * @param[in] nsd The number of significant digits
		 */
		void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the object
		 * @param[in] nsd The number of significant digits
		 */
		std::string printToString(uint_t nsd = 3) const;

	protected:
		GenericObject();
		GenericObject(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe);
		~GenericObject();

		// no copy
		GenericObject(const GenericObject<T,Tr>&) = delete;
		GenericObject<T,Tr>& operator=(const GenericObject<T,Tr>&) = delete;

		// move
		GenericObject(GenericObject<T,Tr>&&);
		GenericObject<T,Tr>& operator=(GenericObject<T,Tr>&&);

		// args
		void setLd    (uint_t          ld    );
		void setValues(T*              values);
		void setProp  (const Property& prop  );

		uint_t          ld  () const;
		const Property& prop() const;

		// callable from empty
		void copyTo(GenericObject<T,Tr>&) const;
		void moveTo(GenericObject<T,Tr>&);
		void cloneTo(GenericObject<T,Tr>&);

		void info(bool is2D,
				const std::string&,
				const std::string&,
				const std::string&,
				const std::string&) const;

		Tr normOne() const;
		Tr normInf() const;
		Tr normMax() const;
		Tr normFro() const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

		// not callcable from empty
		void transposeTo(GenericObject<T,Tr>&) const;
		void ctransposeTo(GenericObject<T,Tr>&) const;

		void gePermuteTo(GenericObject<T,Tr>&, const prm::pMat& P, const prm::pMat& Q) const;
		void gePermuteToLeft(GenericObject<T,Tr>&, const prm::pMat& P) const;
		void gePermuteToRight(GenericObject<T,Tr>&, const prm::pMat& Q) const;
		void shPermuteTo(GenericObject<T,Tr>&, const prm::pMat& P) const;

		void gePermuteIp(const prm::pMat& P, const prm::pMat& Q);
		void gePermuteIpLeft(const prm::pMat& P);
		void gePermuteIpRight(const prm::pMat& Q);
		void shPermuteIp(const prm::pMat& P);

		void getBlock(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void getBlockReference(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		void setBlock(const GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn);

		// creators
		void  blankCreator(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);
		void   zeroCreator(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);
		void randomCreator(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);
		void   wrapCreator(prop_t ptype, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind);

	private:
		uint_t   m_ld    ;
		T*       m_values;
		Property m_prop  ;

		void defaults();
		void creator(prop_t ptype, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool owner);
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
class GenericMap {

	public:
		GenericMap();
		~GenericMap();
		GenericMap(const GenericMap<T>&);
		GenericMap<T>& operator=(const GenericMap<T>&);
		GenericMap(const T&);
		GenericMap<T>& operator=(const T&);

	protected:
		const T& obj() const;

	protected:
		T m_obj;
};
/*-------------------------------------------------*/
template <typename T>
GenericMap<T>::GenericMap()
{
}
/*-------------------------------------------------*/
template <typename T>
GenericMap<T>::~GenericMap()
{
	m_obj.clear();
}
/*-------------------------------------------------*/
template <typename T>
GenericMap<T>::GenericMap(const GenericMap<T>& src)
{
	*this = src.obj();
}
/*-------------------------------------------------*/
template <typename T>
GenericMap<T>& GenericMap<T>::operator=(const GenericMap<T>& src)
{
	*this = src.obj();
	return *this;
}
/*-------------------------------------------------*/
template <typename T>
GenericMap<T>::GenericMap(const T& mat)
{
	m_obj = const_cast<T&>(mat).clone();
}
/*-------------------------------------------------*/
template <typename T>
GenericMap<T>& GenericMap<T>::operator=(const T& mat)
{
	m_obj = const_cast<T&>(mat).clone();
	return *this;
}
/*-------------------------------------------------*/
template <typename T>
const T& GenericMap<T>::GenericMap::obj() const
{
	return m_obj;
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_DNS_HPP_
