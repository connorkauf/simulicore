// this file inc
#include "dns_generic.hpp"

// system

// 3rd

// cla3p
#include "imalloc.hpp"
#include "dns_io.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::GenericObject()
{
	defaults();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::~GenericObject()
{
	clear();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::GenericObject(GenericObject&& /*src*/)
{
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>& GenericObject<T>::operator=(GenericObject&& /*src*/)
{
	return *this;
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::defaults()
{
	set_nrows (0);
	set_ncols (0);
	set_ld    (0);
	set_values(nullptr);
	set_prop  (prop_t::NONE);
	set_owner (false);
}
/*-------------------------------------------------*/
template<class T> void GenericObject<T>::set_nrows (uint_t   nrows ) { m_nrows  = nrows ; }
template<class T> void GenericObject<T>::set_ncols (uint_t   ncols ) { m_ncols  = ncols ; }
template<class T> void GenericObject<T>::set_ld    (uint_t   ld    ) { m_ld     = ld    ; }
template<class T> void GenericObject<T>::set_values(T       *values) { m_values = values; }
template<class T> void GenericObject<T>::set_prop  (Property prop  ) { m_prop   = prop  ; }
template<class T> void GenericObject<T>::set_owner (bool     owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
template<class T> uint_t    GenericObject<T>::nrows () const { return m_nrows ; }
template<class T> uint_t    GenericObject<T>::ncols () const { return m_ncols ; }
template<class T> uint_t    GenericObject<T>::ld    () const { return m_ld    ; }
template<class T> T       * GenericObject<T>::values()       { return m_values; }
template<class T> const T * GenericObject<T>::values() const { return m_values; }
template<class T> Property  GenericObject<T>::prop  () const { return m_prop  ; }
template<class T> bool      GenericObject<T>::owner () const { return m_owner ; }
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::clear()
{
	if(owner()) {
		i_free(values());
	} // owner

	defaults();
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::info() const
{
	std::cout << "nrows....... " << nrows()  << "\n";
	std::cout << "ncols....... " << ncols()  << "\n";
	std::cout << "ld.......... " << ld()     << "\n";
	std::cout << "values...... " << values() << "\n";
	std::cout << "prop........ " << prop()   << "\n";
	std::cout << "owner....... " << owner()  << std::endl;
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::data(uint_t nsd) const
{
  print(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/







/*-------------------------------------------------*/
template class GenericObject<real_t>;
template class GenericObject<real4_t>;
template class GenericObject<complex_t>;
template class GenericObject<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
