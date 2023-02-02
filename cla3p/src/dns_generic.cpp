// this file inc
#include "dns_generic.hpp"

// system

// 3rd

// cla3p
#include "error.hpp"
#include "error_internal.hpp"
#include "utils.hpp"
#include "imalloc.hpp"
#include "bulk/dns.hpp"
#include "bulk/dns_io.hpp"
#include "bulk/dns_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template<typename T>
GenericObject<T>::GenericObject()
{
	defaults();
}
/*-------------------------------------------------*/
template<typename T>
GenericObject<T>::~GenericObject()
{
	clear();
}
/*-------------------------------------------------*/
template<typename T>
GenericObject<T>::GenericObject(GenericObject<T>&& src)
{
	clear();

	if(!src.empty()) {
		creator(src.nrows(), src.ncols(), src.values(), src.ld(), src.prop(), src.owner());
	} // !empty

	src.unbind();
	src.clear();
}
/*-------------------------------------------------*/
template<typename T>
GenericObject<T>& GenericObject<T>::operator=(GenericObject<T>&& src)
{
	clear();

	if(!src.empty()) {
		creator(src.nrows(), src.ncols(), src.values(), src.ld(), src.prop(), src.owner());
	} // !empty

	src.unbind();
	src.clear();

	return *this;
}
/*-------------------------------------------------*/
template<typename T>
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
template<typename T>
void GenericObject<T>::creator(uint_t nrows, uint_t ncols, T *values, uint_t ld, const Property& prop, bool owner)
{
	clear();

	if(!nrows || !ncols) return; // policy is on zero dimensions, return empty object

	status_t stype = bulk::input_consistency_status(prop.type(), nrows, ncols, values, ld);
	Status status(stype); 

	if(status.success()) {

		set_nrows (nrows );
		set_ncols (ncols );
		set_values(values);
		set_ld    (ld    );
		set_prop  (prop  );
		set_owner (owner );

	} else {

		throw NoConsistency(status.message());

	} // consistency check
}
/*-------------------------------------------------*/
template<typename T> void GenericObject<T>::set_nrows (uint_t          nrows ) { m_nrows  = nrows ; }
template<typename T> void GenericObject<T>::set_ncols (uint_t          ncols ) { m_ncols  = ncols ; }
template<typename T> void GenericObject<T>::set_ld    (uint_t          ld    ) { m_ld     = ld    ; }
template<typename T> void GenericObject<T>::set_values(T*              values) { m_values = values; }
template<typename T> void GenericObject<T>::set_prop  (const Property& prop  ) { m_prop   = prop  ; }
template<typename T> void GenericObject<T>::set_owner (bool            owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
template<typename T> uint_t          GenericObject<T>::nrows () const { return m_nrows ; }
template<typename T> uint_t          GenericObject<T>::ncols () const { return m_ncols ; }
template<typename T> uint_t          GenericObject<T>::ld    () const { return m_ld    ; }
template<typename T> T*              GenericObject<T>::values()       { return m_values; }
template<typename T> const T*        GenericObject<T>::values() const { return m_values; }
template<typename T> const Property& GenericObject<T>::prop  () const { return m_prop  ; }
template<typename T> bool            GenericObject<T>::owner () const { return m_owner ; }
/*-------------------------------------------------*/
template<typename T>
bool GenericObject<T>::empty() const
{
	if(nrows() && ncols() && values()) 
		return false;

	return true;
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::clear()
{
	if(owner()) {
		i_free(values());
	} // owner

	defaults();
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::unbind()
{
	set_owner(false);
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::copy_to(GenericObject<T>& trg) const
{
	trg.clear();

	if(!empty()) {
		T *vnew = bulk::alloc<T>(nrows(), ncols(), nrows());
		bulk::copy(prop().type(), nrows(), ncols(), values(), ld(), vnew, nrows());
		trg.creator(nrows(), ncols(), vnew, nrows(), prop(), true);
	} // !empty
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::move_to(GenericObject<T>& trg)
{
	trg.clear();

	if(!empty()) {
		trg.creator(nrows(), ncols(), values(), ld(), prop(), owner());
	} // !empty

	unbind();
	clear();
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::clone_to(GenericObject<T>& trg)
{
	trg.clear();

	if(!empty()) {
		trg.creator(nrows(), ncols(), values(), ld(), prop(), false);
	} // !empty
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::info(
		const std::string& msg, 
		const std::string& otype, 
		const std::string& dtype, 
		const std::string& dprec) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::cout << top << "\n";

	std::cout << "  Object type.......... " << otype << "\n";
	std::cout << "  Datatype............. " << dtype << "\n";
	std::cout << "  Precision............ " << dprec << "\n";

	bool is_vector = (otype == "Vector");
	bool is_matrix = (otype == "Matrix");

	if(is_vector) {
		std::cout << "  size................. " <<         nrows () << "\n";
		std::cout << "  values............... " <<         values() << "\n";
		std::cout << "  owner................ " << bool2yn(owner ()) << "\n";
	} // vector

	if(is_matrix) {
		std::cout << "  nrows................ " <<         nrows () << "\n";
		std::cout << "  ncols................ " <<         ncols () << "\n";
		std::cout << "  ld................... " <<         ld    () << "\n";
		std::cout << "  values............... " <<         values() << "\n";
		std::cout << "  prop................. " <<         prop  () << "\n";
		std::cout << "  owner................ " << bool2yn(owner ()) << "\n";
	} // matrix

	std::cout << bottom << "\n";
}
/*-------------------------------------------------*/
template<typename T>
void GenericObject<T>::print(uint_t nsd) const
{
	bulk::print(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template<typename T>
T& GenericObject<T>::operator()(uint_t i, uint_t j)
{
	return dns::bulk::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template<typename T>
const T& GenericObject<T>::operator()(uint_t i, uint_t j) const
{
	return dns::bulk::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template <typename T>
void GenericObject<T>::empty_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	T *values = bulk::alloc<T>(nrows, ncols, ld);
	creator(nrows, ncols, values, ld, prop, true);
}
/*-------------------------------------------------*/
template <typename T>
void GenericObject<T>::zero_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	empty_creator(prop, nrows, ncols, ld);
	bulk::zero(
			this->prop().type(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
template <typename T>
void GenericObject<T>::random_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	empty_creator(prop, nrows, ncols, ld);
	bulk::rand(
			this->prop().type(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
template <typename T>
void GenericObject<T>::map_creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind)
{
	creator(nrows, ncols, values, ld, prop, bind);
}
/*-------------------------------------------------*/
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
