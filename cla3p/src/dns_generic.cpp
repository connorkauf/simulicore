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
template <typename T, typename Tr>
GenericObject<T,Tr>::GenericObject()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::GenericObject(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
{
	if(wipe) {
		zero_creator(prop, nrows, ncols, ld);
	} else {
		empty_creator(prop, nrows, ncols, ld);
	} // wipe
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::~GenericObject()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::GenericObject(GenericObject<T,Tr>&& src)
{
	clear();

	if(!src.empty()) {
		creator(src.prop(), src.nrows(), src.ncols(), src.values(), src.ld(), src.owner());
	} // !empty

	src.unbind();
	src.clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>& GenericObject<T,Tr>::operator=(GenericObject<T,Tr>&& src)
{
	clear();

	if(!src.empty()) {
		creator(src.prop(), src.nrows(), src.ncols(), src.values(), src.ld(), src.owner());
	} // !empty

	src.unbind();
	src.clear();

	return *this;
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::defaults()
{
	set_nrows (0);
	set_ncols (0);
	set_ld    (0);
	set_values(nullptr);
	set_prop  (prop_t::NONE);
	set_owner (false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool owner)
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
template <typename T, typename Tr> void GenericObject<T,Tr>::set_nrows (uint_t          nrows ) { m_nrows  = nrows ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_ncols (uint_t          ncols ) { m_ncols  = ncols ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_ld    (uint_t          ld    ) { m_ld     = ld    ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_values(T*              values) { m_values = values; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_prop  (const Property& prop  ) { m_prop   = prop  ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_owner (bool            owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::nrows () const { return m_nrows ; }
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::ncols () const { return m_ncols ; }
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::ld    () const { return m_ld    ; }
template <typename T, typename Tr> T*              GenericObject<T,Tr>::values()       { return m_values; }
template <typename T, typename Tr> const T*        GenericObject<T,Tr>::values() const { return m_values; }
template <typename T, typename Tr> const Property& GenericObject<T,Tr>::prop  () const { return m_prop  ; }
template <typename T, typename Tr> bool            GenericObject<T,Tr>::owner () const { return m_owner ; }
/*-------------------------------------------------*/
template <typename T, typename Tr>
bool GenericObject<T,Tr>::empty() const
{
	if(nrows() && ncols() && values()) 
		return false;

	return true;
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::clear()
{
	if(owner()) {
		i_free(values());
	} // owner

	defaults();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::unbind()
{
	set_owner(false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::copy_to(GenericObject<T,Tr>& trg) const
{
	trg.clear();

	if(!empty()) {
		trg.empty_creator(prop(), nrows(), ncols(), ld());
		bulk::copy(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::move_to(GenericObject<T,Tr>& trg)
{
	trg.clear();

	if(!empty()) {
		trg.creator(prop(), nrows(), ncols(), values(), ld(), owner());
	} // !empty

	unbind();
	clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::clone_to(GenericObject<T,Tr>& trg)
{
	trg.clear();

	if(!empty()) {
		trg.creator(prop(), nrows(), ncols(), values(), ld(), false);
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::transpose_to(GenericObject<T,Tr>& trg) const
{
	trg.clear();

	if(!empty()) {
		if(!prop().is_general()) 
			throw InvalidOp("Transpositions are applied on general matrices");
		trg.empty_creator(prop(), ncols(), nrows(), ncols());
		bulk::transpose(nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::ctranspose_to(GenericObject<T,Tr>& trg) const
{
	trg.clear();

	if(!empty()) {
		if(!prop().is_general()) 
			throw InvalidOp("Transpositions are applied on general matrices");
		trg.empty_creator(prop(), ncols(), nrows(), ncols());
		bulk::conjugate_transpose(nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::permute_to(GenericObject<T,Tr>& trg, const uint_t *P, const uint_t *Q) const
{
	trg.clear();

	if(!empty()) {
		trg.empty_creator(prop(), nrows(), ncols(), nrows());
		bulk::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P, Q);
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::scale(T coeff)
{
	if(!empty()) {
		bulk::scale(prop().type(), nrows(), ncols(), values(), ld(), coeff);
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::info(
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
template <typename T, typename Tr>
void GenericObject<T,Tr>::print(uint_t nsd) const
{
	bulk::print(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_one() const
{ 
	return bulk::norm_one(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_inf() const
{ 
	return bulk::norm_inf(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_max() const
{ 
	return bulk::norm_max(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_fro() const
{ 
	return bulk::norm_fro(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
T& GenericObject<T,Tr>::operator()(uint_t i, uint_t j)
{
	return dns::bulk::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
const T& GenericObject<T,Tr>::operator()(uint_t i, uint_t j) const
{
	return dns::bulk::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::empty_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	T *values = bulk::alloc<T>(nrows, ncols, ld);
	creator(prop, nrows, ncols, values, ld, true);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::zero_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
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
template <typename T, typename Tr>
void GenericObject<T,Tr>::random_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
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
template <typename T, typename Tr>
void GenericObject<T,Tr>::map_creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind)
{
	creator(prop, nrows, ncols, values, ld, bind);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class GenericObject<real_t,real_t>;
template class GenericObject<real4_t,real4_t>;
template class GenericObject<complex_t,real_t>;
template class GenericObject<complex8_t,real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
