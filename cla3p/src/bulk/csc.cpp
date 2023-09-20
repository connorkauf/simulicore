// this file inc
#include "csc.hpp"

// system
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

// 3rd

// cla3p
#include "../support/utils.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../proxies/blas_proxy.hpp"

#include "../types/integer_internal.hpp"
#include "../types/scalar_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace csc {
/*-------------------------------------------------*/
void roll(uint_t n, uint_t *colptr)
{
	for(uint_t j = 0; j < n; j++) {
		colptr[j+1] += colptr[j];
	} // j
}
/*-------------------------------------------------*/
void unroll(uint_t n, uint_t *colptr)
{
	for(int_t j = n-1; j > 0; j--) {
		colptr[j] = colptr[j-1];
	} // j
	colptr[0] = 0;
}
/*-------------------------------------------------*/
uint_t maxrlen(uint_t n, const uint_t *colptr)
{
	uint_t ret = 0;

	for(uint_t j = 0; j < n; j++) {
		ret = std::max(ret, colptr[j+1] - colptr[j]);
	} // j

	return ret;
}
/*-------------------------------------------------*/
template <typename T>
struct rvPair {
	uint_t i;
	T      v;
};
/*-------------------------------------------------*/
template <typename T>
static bool pair_compare(const rvPair<T>& rv1, const rvPair<T>& rv2)
{
	return (rv1.i < rv2.i);
}
/*-------------------------------------------------*/
template <typename T>
static void sort_by_ridx_tmpl(uint_t n, const uint_t *colptr, uint_t *rowidx, T *values)
{
	if(!n) return;

	uint_t milen = maxrlen(n, colptr);

	if(!milen) return;

	std::vector< struct rvPair<T> > row_pairs;
	row_pairs.reserve(milen);

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];
		uint_t ilen = iend - ibgn;

		if(!ilen) continue;

		row_pairs.resize(ilen);

		for(uint_t irow = ibgn; irow < iend; irow++) {
			row_pairs[irow - ibgn].i = rowidx[irow];
			row_pairs[irow - ibgn].v = values[irow];
		} // irow

		std::sort(row_pairs.begin(), row_pairs.end(), pair_compare<T>);

		for(uint_t irow = ibgn; irow < iend; irow++) {
			rowidx[irow] = row_pairs[irow - ibgn].i;
			values[irow] = row_pairs[irow - ibgn].v;
		} // irow

	} // j
}
/*-------------------------------------------------*/
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx)
{
	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];
		uint_t ilen = iend - ibgn;

		if(ilen) {
			std::sort(rowidx + ibgn, rowidx + iend);
		} // ilen

	} // j
}
/*-------------------------------------------------*/
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, int_t      *values) { sort_by_ridx_tmpl(n, colptr, rowidx, values); }
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, uint_t     *values) { sort_by_ridx_tmpl(n, colptr, rowidx, values); }
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, real_t     *values) { sort_by_ridx_tmpl(n, colptr, rowidx, values); }
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, real4_t    *values) { sort_by_ridx_tmpl(n, colptr, rowidx, values); }
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, complex_t  *values) { sort_by_ridx_tmpl(n, colptr, rowidx, values); }
void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, complex8_t *values) { sort_by_ridx_tmpl(n, colptr, rowidx, values); }
/*-------------------------------------------------*/
template <typename T>
static std::string print_to_string_tmpl(uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values, uint_t nsd)
{
#define BUFFER_LEN 1024

	std::string ret;
	ret.reserve(colptr[n] * 128);
	char cbuff[BUFFER_LEN];

	std::snprintf(cbuff, BUFFER_LEN, "       #nz        row     column  value          \n"); ret.append(cbuff);
	std::snprintf(cbuff, BUFFER_LEN, "-------------------------------------------------\n"); ret.append(cbuff);

	uint_t icnt = 0;
	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			T      v = values[irow];

			val2char(cbuff, BUFFER_LEN,  10, icnt++); ret.append(cbuff); ret.append(" ");
			val2char(cbuff, BUFFER_LEN,  10, i     ); ret.append(cbuff); ret.append(" ");
			val2char(cbuff, BUFFER_LEN,  10, j     ); ret.append(cbuff); ret.append(" ");
			val2char(cbuff, BUFFER_LEN, nsd, v     ); ret.append(cbuff); ret.append("\n");

		} // irow

	} // j

	return ret;

#undef BUFFER_LEN
}
/*-------------------------------------------------*/
std::string print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const int_t      *values, uint_t nsd) { return print_to_string_tmpl(n, colptr, rowidx, values, nsd); }
std::string print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const uint_t     *values, uint_t nsd) { return print_to_string_tmpl(n, colptr, rowidx, values, nsd); }
std::string print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const real_t     *values, uint_t nsd) { return print_to_string_tmpl(n, colptr, rowidx, values, nsd); }
std::string print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const real4_t    *values, uint_t nsd) { return print_to_string_tmpl(n, colptr, rowidx, values, nsd); }
std::string print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex_t  *values, uint_t nsd) { return print_to_string_tmpl(n, colptr, rowidx, values, nsd); }
std::string print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex8_t *values, uint_t nsd) { return print_to_string_tmpl(n, colptr, rowidx, values, nsd); }
/*-------------------------------------------------*/
template <typename T>
static void print_tmpl(uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values, uint_t nsd)
{
	std::string tmp = print_to_string(n, colptr, rowidx, values, nsd);
	std::cout << tmp;
}
/*-------------------------------------------------*/
void print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const int_t      *values, uint_t nsd) { print_tmpl(n, colptr, rowidx, values, nsd); }
void print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const uint_t     *values, uint_t nsd) { print_tmpl(n, colptr, rowidx, values, nsd); }
void print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const real_t     *values, uint_t nsd) { print_tmpl(n, colptr, rowidx, values, nsd); }
void print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const real4_t    *values, uint_t nsd) { print_tmpl(n, colptr, rowidx, values, nsd); }
void print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex_t  *values, uint_t nsd) { print_tmpl(n, colptr, rowidx, values, nsd); }
void print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex8_t *values, uint_t nsd) { print_tmpl(n, colptr, rowidx, values, nsd); }
/*-------------------------------------------------*/
static void transpose_colptr(uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, uint_t *colptr_out)
{
	for(uint_t j = 0; j < m+1; j++) {
		colptr_out[j] = 0;
	} // j

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {
			colptr_out[rowidx[irow] + 1]++;
		} // irow

	} // j

	unroll(m, colptr_out);
}
/*-------------------------------------------------*/
template <typename T>
static void hybrid_transpose_tmpl(uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values, 
		uint_t *colptr_out, uint_t *rowidx_out, T *values_out, T coeff, bool conjop) 
{
	transpose_colptr(m, n, colptr, rowidx, colptr_out);

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			T      v = values[irow];

			rowidx_out[colptr_out[i]] = j;
			values_out[colptr_out[i]] = coeff * (conjop ? conj(v) : v);

			colptr_out[i]++;

		} // irow

	} // j

	unroll(m, colptr_out);
}
/*-------------------------------------------------*/
#define transpose_macro(typeout, typein) \
typeout transpose(uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
		uint_t *colptr_out, uint_t *rowidx_out, typein *values_out, typein coeff) \
{ \
	hybrid_transpose_tmpl(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, coeff, false); \
}
transpose_macro(void, int_t)
transpose_macro(void, uint_t)
transpose_macro(void, real_t)
transpose_macro(void, real4_t)
transpose_macro(void, complex_t)
transpose_macro(void, complex8_t)
#undef transpose_macro
/*-------------------------------------------------*/
void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const int_t  *, uint_t*, uint_t*, int_t  *, int_t  ) { throw Exception(msg::op_not_allowed()); }
void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const uint_t *, uint_t*, uint_t*, uint_t *, uint_t ) { throw Exception(msg::op_not_allowed()); }
void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const real_t *, uint_t*, uint_t*, real_t *, real_t ) { throw Exception(msg::op_not_allowed()); }
void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const real4_t*, uint_t*, uint_t*, real4_t*, real4_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
#define conjugate_transpose_macro(typeout, typein) \
typeout conjugate_transpose(uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
		uint_t *colptr_out, uint_t *rowidx_out, typein *values_out, typein coeff) \
{ \
	hybrid_transpose_tmpl(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, coeff, true); \
}
conjugate_transpose_macro(void, complex_t)
conjugate_transpose_macro(void, complex8_t)
#undef conjugate_transpose_macro
/*-------------------------------------------------*/
void uplo2ge_colptr(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, uint_t *colptr_out)
{
	for(uint_t j = 0; j < n+1; j++) {
		colptr_out[j] = 0;
	} // j

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];

			if(uplo == uplo_t::L && i >= j) {
				/*      */ colptr_out[j+1]++;
				if(i != j) colptr_out[i+1]++;
			} // lower

			if(uplo == uplo_t::U && i <= j) {
				/*      */ colptr_out[j+1]++;
				if(i != j) colptr_out[i+1]++;
			} // lower

		} // irow

	} // j

	roll(n, colptr_out);
}
/*-------------------------------------------------*/
template <typename T>
static inline void append_to_selected_part(uint_t i, uint_t j, T v, uint_t *colptr_out, uint_t *rowidx_out, T *values_out, bool conjop)
{
	// original part
	rowidx_out[colptr_out[j]  ] = i;
	values_out[colptr_out[j]++] = v;

	// opposite part
	if(i != j) {
		rowidx_out[colptr_out[i]  ] = j;
		values_out[colptr_out[i]++] = (conjop ? conj(v) : v);
	} // strict part
}
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_tmpl(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values, 
		uint_t *colptr_out, uint_t *rowidx_out, T *values_out, bool conjop) 
{
	uplo2ge_colptr(uplo, n, colptr, rowidx, colptr_out);

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			T      v = values[irow];

			if(uplo == uplo_t::L && i >= j) {
				append_to_selected_part(i, j, v, colptr_out, rowidx_out, values_out, conjop);
			} // lower

			if(uplo == uplo_t::U && i <= j) {
				append_to_selected_part(i, j, v, colptr_out, rowidx_out, values_out, conjop);
			} // lower

		} // irow

	} // j

	unroll(n, colptr_out);
}
/*-------------------------------------------------*/
#define sy2ge_macro(typeout, typein) \
typeout sy2ge(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
    uint_t *colptr_out, uint_t *rowidx_out, typein *values_out) \
{ \
	syhe2ge_tmpl(uplo, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, false); \
}
sy2ge_macro(void, int_t)
sy2ge_macro(void, uint_t)
sy2ge_macro(void, real_t)
sy2ge_macro(void, real4_t)
sy2ge_macro(void, complex_t)
sy2ge_macro(void, complex8_t)
#undef sy2ge_macro
/*-------------------------------------------------*/
void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const int_t  *, uint_t*, uint_t*, int_t  *) { throw Exception(msg::op_not_allowed()); }
void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const uint_t *, uint_t*, uint_t*, uint_t *) { throw Exception(msg::op_not_allowed()); }
void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const real_t *, uint_t*, uint_t*, real_t *) { throw Exception(msg::op_not_allowed()); }
void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const real4_t*, uint_t*, uint_t*, real4_t*) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
#define he2ge_macro(typeout, typein) \
typeout he2ge(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
    uint_t *colptr_out, uint_t *rowidx_out, typein *values_out) \
{ \
	syhe2ge_tmpl(uplo, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, true); \
}
he2ge_macro(void, complex_t)
he2ge_macro(void, complex8_t)
#undef he2ge_macro
/*-------------------------------------------------*/
template <typename T>
static inline void apply_op(T& v, const T& u, dup_t op)
{
	/**/ if(op == dup_t::SUM ) v += u;
	else if(op == dup_t::PROD) v *= u;
	else if(op == dup_t::AMAX) v = std::max(std::abs(v), std::abs(u));
	else if(op == dup_t::AMIN) v = std::max(std::abs(v), std::abs(u));
}
/*-------------------------------------------------*/
template <typename T>
void remove_duplicates_tmpl(uint_t n, uint_t *colptr, uint_t *rowidx, T *values, dup_t op)
{
	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		colptr[j] = (j > 0 ? colptr[j-1] : 0);

		uint_t ilen = iend - ibgn;

		if(!ilen) continue;

		uint_t iref = rowidx[ibgn];

		rowidx[colptr[j]] = rowidx[ibgn];
		values[colptr[j]] = values[ibgn];
		colptr[j]++;

		for(uint_t irow = ibgn + 1; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			T      v = values[irow];

			if(i == iref) {
				apply_op<T>(values[colptr[j]-1], v, op);
			} else {
				rowidx[colptr[j]] = i;
				values[colptr[j]] = v;
				colptr[j]++;
				iref = i;
			} // dup check

		} // irow

	} // j

	colptr[n] = colptr[n-1];

	unroll(n, colptr);
}
/*-------------------------------------------------*/
void remove_duplicates(uint_t n, uint_t *colptr, uint_t *rowidx, int_t      *values, dup_t op) { return remove_duplicates_tmpl(n, colptr, rowidx, values, op); }
void remove_duplicates(uint_t n, uint_t *colptr, uint_t *rowidx, real_t     *values, dup_t op) { return remove_duplicates_tmpl(n, colptr, rowidx, values, op); }
void remove_duplicates(uint_t n, uint_t *colptr, uint_t *rowidx, real4_t    *values, dup_t op) { return remove_duplicates_tmpl(n, colptr, rowidx, values, op); }
void remove_duplicates(uint_t n, uint_t *colptr, uint_t *rowidx, complex_t  *values, dup_t op) { return remove_duplicates_tmpl(n, colptr, rowidx, values, op); }
void remove_duplicates(uint_t n, uint_t *colptr, uint_t *rowidx, complex8_t *values, dup_t op) { return remove_duplicates_tmpl(n, colptr, rowidx, values, op); }
/*-------------------------------------------------*/
template <typename T, typename Tr>
static Tr norm_one_tmpl(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values)
{
  if(!n) return 0;

	std::vector<Tr> col_norms(n, 0);

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			Tr av = std::abs(values[irow]);

			col_norms[j] += av;

			if(ptype == prop_t::SYMMETRIC || ptype == prop_t::HERMITIAN || ptype == prop_t::SKEW) {
				if(i != j) {
					col_norms[i] += av;
				} // off diag
			} // ptype

		} // irow

	} // j

	return col_norms[blas::iamax(n,col_norms.data(),1)];
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
static Tr norm_inf_tmpl(prop_t ptype, uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values)
{
  if(!m || !n) return 0;

	std::vector<Tr> row_norms(m, 0);

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			Tr av = std::abs(values[irow]);

			row_norms[i] += av;

			if(ptype == prop_t::SYMMETRIC || ptype == prop_t::HERMITIAN || ptype == prop_t::SKEW) {
				if(i != j) {
					row_norms[j] += av;
				} // off diag
			} // ptype

		} // irow

	} // j

	return row_norms[blas::iamax(m,row_norms.data(),1)];
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
static Tr norm_max_tmpl(uint_t n, const uint_t *colptr, const T *values)
{
  if(!n) return 0;

	T vamax = values[blas::iamax(colptr[n],values,1)];

	return std::abs(vamax);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
static Tr norm_fro_tmpl(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const T *values)
{
  if(!n) return 0;

	Tr ret = 0;

	for(uint_t j = 0; j < n; j++) {

		uint_t ibgn = colptr[j];
		uint_t iend = colptr[j+1];

		for(uint_t irow = ibgn; irow < iend; irow++) {

			uint_t i = rowidx[irow];
			Tr av = std::abs(values[irow]);
			Tr av2 = av * av;

			if(ptype == prop_t::GENERAL || ptype == prop_t::TRIANGULAR) {

				ret += av2;

			} else if(ptype == prop_t::SYMMETRIC || ptype == prop_t::HERMITIAN || ptype == prop_t::SKEW) {

				ret += (i == j ? av2 : 2 * av2);

			} else {

				throw Exception("Invalid property");

			} // ptype


		} // irow

	} // j

	return std::sqrt(ret);
}
/*-------------------------------------------------*/
int_t  norm_one(prop_t, uint_t, const uint_t*, const uint_t*, const int_t *){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_one(prop_t, uint_t, const uint_t*, const uint_t*, const uint_t*){ throw Exception(msg::op_not_allowed()); return 0; }
/*-------------------------------------------------*/
int_t  norm_inf(prop_t, uint_t, uint_t, const uint_t*, const uint_t*, const int_t *){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_inf(prop_t, uint_t, uint_t, const uint_t*, const uint_t*, const uint_t*){ throw Exception(msg::op_not_allowed()); return 0; }
/*-------------------------------------------------*/
int_t  norm_max(uint_t, const uint_t*, const int_t *){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_max(uint_t, const uint_t*, const uint_t*){ throw Exception(msg::op_not_allowed()); return 0; }
/*-------------------------------------------------*/
int_t  norm_fro(prop_t, uint_t, const uint_t*, const uint_t*, const int_t *){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_fro(prop_t, uint_t, const uint_t*, const uint_t*, const uint_t*){ throw Exception(msg::op_not_allowed()); return 0; }
/*-------------------------------------------------*/
real_t norm_one(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const real_t *values)
{ 
	return norm_one_tmpl<real_t,real_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real_t norm_inf(prop_t ptype, uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const real_t *values)
{ 
	return norm_inf_tmpl<real_t,real_t>(ptype, m, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real_t norm_max(uint_t n, const uint_t *colptr, const real_t *values)
{ 
	return norm_max_tmpl<real_t,real_t>(n, colptr, values); 
}
/*-------------------------------------------------*/
real_t norm_fro(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const real_t *values)
{ 
	return norm_fro_tmpl<real_t,real_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real4_t norm_one(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const real4_t *values)
{ 
	return norm_one_tmpl<real4_t,real4_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real4_t norm_inf(prop_t ptype, uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const real4_t *values)
{ 
	return norm_inf_tmpl<real4_t,real4_t>(ptype, m, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real4_t norm_max(uint_t n, const uint_t *colptr, const real4_t *values)
{ 
	return norm_max_tmpl<real4_t,real4_t>(n, colptr, values); 
}
/*-------------------------------------------------*/
real4_t norm_fro(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const real4_t *values)
{ 
	return norm_fro_tmpl<real4_t,real4_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real_t norm_one(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex_t *values)
{ 
	return norm_one_tmpl<complex_t,real_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real_t norm_inf(prop_t ptype, uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex_t *values)
{ 
	return norm_inf_tmpl<complex_t,real_t>(ptype, m, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real_t norm_max(uint_t n, const uint_t *colptr, const complex_t *values)
{ 
	return norm_max_tmpl<complex_t,real_t>(n, colptr, values); 
}
/*-------------------------------------------------*/
real_t norm_fro(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex_t *values)
{ 
	return norm_fro_tmpl<complex_t,real_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real4_t norm_one(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex8_t *values)
{ 
	return norm_one_tmpl<complex8_t,real4_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real4_t norm_inf(prop_t ptype, uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex8_t *values)
{ 
	return norm_inf_tmpl<complex8_t,real4_t>(ptype, m, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
real4_t norm_max(uint_t n, const uint_t *colptr, const complex8_t *values)
{ 
	return norm_max_tmpl<complex8_t,real4_t>(n, colptr, values); 
}
/*-------------------------------------------------*/
real4_t norm_fro(prop_t ptype, uint_t n, const uint_t *colptr, const uint_t *rowidx, const complex8_t *values)
{ 
	return norm_fro_tmpl<complex8_t,real4_t>(ptype, n, colptr, rowidx, values); 
}
/*-------------------------------------------------*/
} // namespace csc
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
