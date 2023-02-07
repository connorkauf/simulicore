#ifndef CLA3P_DNS_GENERIC_HPP_
#define CLA3P_DNS_GENERIC_HPP_

#include <string>
#include <iostream>

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace prm { class pMat; }
namespace dns {
/*-------------------------------------------------*/
/**
 * @brief The basic dense object generic class
 *
 * All dense objects inherit from this base class
 */
template <typename T, typename Tr>
class GenericObject {

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

		/**
		 * @brief The ownership status
		 * @return The ownership status
		 */
		bool owner() const;

		// 
		// inherited methods - callable from empty
		//

		/**
		 * @brief Checks object for entries
		 * @return If object is empty
		 */
		bool empty() const;

		/**
		 * @brief Clears the object
		 */
		void clear();

		/**
		 * @brief Unbinds associated data from the object
		 */
		void unbind();

		/**
		 * @brief Scales object by coeff
		 * @param[in] coeff The scaling coefficient
		 */
		void scale(T coeff);

	protected:
		GenericObject();
		GenericObject(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld, bool wipe);
		~GenericObject();

		// no copy
		GenericObject(const GenericObject<T,Tr>&) = delete;
		GenericObject<T,Tr>& operator=(const GenericObject<T,Tr>&) = delete;

		// move
		GenericObject(GenericObject<T,Tr>&&);
		GenericObject<T,Tr>& operator=(GenericObject<T,Tr>&&);

		// args
		void set_nrows (uint_t          nrows );
		void set_ncols (uint_t          ncols );
		void set_ld    (uint_t          ld    );
		void set_values(T*              values);
		void set_prop  (const Property& prop  );
		void set_owner (bool            owner );

		uint_t          nrows () const;
		uint_t          ncols () const;
		uint_t          ld    () const;
		const Property& prop  () const;

		// callable from empty
		void copy_to(GenericObject<T,Tr>&) const;
		void move_to(GenericObject<T,Tr>&);
		void clone_to(GenericObject<T,Tr>&);

		void info(
				const std::string&,
				const std::string&,
				const std::string&,
				const std::string&) const;
		void print(uint_t) const;
		std::string print2str(uint_t) const;

		Tr norm_one() const;
		Tr norm_inf() const;
		Tr norm_max() const;
		Tr norm_fro() const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

		// not callcable from empty
		void transpose_to(GenericObject<T,Tr>&) const;
		void ctranspose_to(GenericObject<T,Tr>&) const;

		void ge_permute_to(GenericObject<T,Tr>&, const prm::pMat& P, const prm::pMat& Q) const;
		void ge_permute_to_left(GenericObject<T,Tr>&, const prm::pMat& P) const;
		void ge_permute_to_right(GenericObject<T,Tr>&, const prm::pMat& Q) const;
		void sh_permute_to(GenericObject<T,Tr>&, const prm::pMat& P) const;

		void ge_permute_ip(const prm::pMat& P, const prm::pMat& Q);
		void ge_permute_ip_left(const prm::pMat& P);
		void ge_permute_ip_right(const prm::pMat& Q);
		void sh_permute_ip(const prm::pMat& P);

		void get_block(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void get_block_reference(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		void set_block(const GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn);

		// creators
		void  blank_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		void   zero_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		void random_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		void    map_creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind);

	private:
		uint_t   m_nrows ;
		uint_t   m_ncols ;
		uint_t   m_ld    ;
		T*       m_values;
		Property m_prop  ;
		bool     m_owner ;

		void defaults();
		void creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool owner);
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

#endif // CLA3P_DNS_GENERIC_HPP_
