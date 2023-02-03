#ifndef CLA3P_DNS_GENERIC_HPP_
#define CLA3P_DNS_GENERIC_HPP_

#include <iostream>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p { namespace prm {
class pMat;
}}
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template <typename T, typename Tr>
class GenericObject {

	public:
		void  blank_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		void   zero_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		void random_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		void    map_creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind);

	protected:
		GenericObject();
		GenericObject(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld, bool wipe);
		~GenericObject();
		GenericObject(const GenericObject<T,Tr>&) = delete;
		GenericObject<T,Tr>& operator=(const GenericObject<T,Tr>&) = delete;
		GenericObject(GenericObject<T,Tr>&&);
		GenericObject<T,Tr>& operator=(GenericObject<T,Tr>&&);

		void set_nrows (uint_t          nrows );
		void set_ncols (uint_t          ncols );
		void set_ld    (uint_t          ld    );
		void set_values(T*              values);
		void set_prop  (const Property& prop  );
		void set_owner (bool            owner );

		uint_t          nrows () const;
		uint_t          ncols () const;
		uint_t          ld    () const;
		T*              values()      ;
		const T*        values() const;
		const Property& prop  () const;
		bool            owner () const;

		bool empty() const;
		void clear();
		void unbind();
		void scale(T coeff);

		void copy_to(GenericObject<T,Tr>&) const;
		void move_to(GenericObject<T,Tr>&);
		void clone_to(GenericObject<T,Tr>&);
		void transpose_to(GenericObject<T,Tr>&) const;
		void ctranspose_to(GenericObject<T,Tr>&) const;
		void permute_to(GenericObject<T,Tr>&, const cla3p::prm::pMat& P, const cla3p::prm::pMat& Q) const;

		void info(
				const std::string&,
				const std::string&,
				const std::string&,
				const std::string&) const;
		void print(uint_t) const;

		Tr norm_one() const;
		Tr norm_inf() const;
		Tr norm_max() const;
		Tr norm_fro() const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

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
