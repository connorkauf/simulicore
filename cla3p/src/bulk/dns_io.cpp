// this file inc
#include "dns_io.hpp"

// system
#include <cstdio>
#include <algorithm>

// 3rd

// cla3p
#include "dns.hpp"
#include "dns_checks.hpp"
#include "../utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
namespace bulk {
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
class DnsPrinter {

	public:
		DnsPrinter(uint_t nsd, uint_t line_maxlen);
		~DnsPrinter();

		std::string print2str(uint_t m, uint_t n, const real_t *a, uint_t lda, bool lower);
		std::string print2str(uint_t m, uint_t n, const real4_t *a, uint_t lda, bool lower);
		std::string print2str(uint_t m, uint_t n, const complex_t *a, uint_t lda, bool lower);
		std::string print2str(uint_t m, uint_t n, const complex8_t *a, uint_t lda, bool lower);

		template <typename T>
		void print(uint_t m, uint_t n, T *a, uint_t lda, bool lower);

	private:
		void reset();
		void reserve(uint_t m, uint_t n);

		template <typename T>
		std::string print2str_real(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		std::string print2str_complex(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		void fill(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		void append_page(uint_t m, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower);
		template <typename T>
		void append_page_ith_row(uint_t i, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower);

		uint_t count_columns_per_page(uint_t n);
		void append_page_header(uint_t jbgn, uint_t jend);
		void appent_extra_spaces();
		void appent_element(real_t a);
		void appent_element(real4_t a);
		void appent_element(complex_t a);
		void appent_element(complex8_t a);

		const uint_t m_nsd;
		const uint_t m_line_maxlen;

		uint_t m_row_numdigits;
		uint_t m_col_numdigits;
		uint_t m_element_length;
		uint_t m_element_length_max;

		char m_cbuff[128];
		std::string m_str;
};
/*-------------------------------------------------*/
static uint_t sanitized_nsd(uint_t nsd)
{
	sanitize_nsd(nsd);
	return nsd;
}
/*-------------------------------------------------*/
DnsPrinter::DnsPrinter(uint_t nsd, uint_t line_maxlen)
	: 
		m_nsd(sanitized_nsd(nsd)), 
		m_line_maxlen(line_maxlen)
{
	reset();
}
/*-------------------------------------------------*/
DnsPrinter::~DnsPrinter()
{
	reset();
}
/*-------------------------------------------------*/
void DnsPrinter::reset()
{
	m_row_numdigits      = 0;
	m_col_numdigits      = 0;
	m_element_length     = 0;
	m_element_length_max = 0;

	m_str.clear();
}
/*-------------------------------------------------*/
uint_t DnsPrinter::count_columns_per_page(uint_t n)
{
	uint_t row_index_len = m_row_numdigits + 3; // rowidx + space + sep + space
	
	uint_t min_elements_per_page = 1;
	uint_t elements_per_page = m_line_maxlen >= row_index_len 
		? (m_line_maxlen - row_index_len) / m_element_length_max 
		: 0;

	elements_per_page = std::max(elements_per_page, min_elements_per_page);
	elements_per_page = std::min(elements_per_page, n);

	return elements_per_page;
}
/*-------------------------------------------------*/
void DnsPrinter::append_page_header(uint_t jbgn, uint_t jend)
{
	nint_t nd = m_row_numdigits;
	std::sprintf(m_cbuff, "%*s |", nd, "");
	m_str.append(m_cbuff);

	nd = m_element_length_max;
	for(uint_t j = jbgn; j < jend; j++) {
		std::sprintf(m_cbuff, "%*" _UFMT_ , nd, j);
		m_str.append(m_cbuff);
	} // j

	m_str.append("\n");
}
/*-------------------------------------------------*/
void DnsPrinter::appent_extra_spaces()
{
	nint_t extra_spaces = m_element_length_max - m_element_length;

	if(extra_spaces) {
		std::sprintf(m_cbuff, "%*s", extra_spaces, "");
		m_str.append(m_cbuff);
	} // extra_spaces
}
/*-------------------------------------------------*/
void DnsPrinter::appent_element(real_t a)
{
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " % .*le", nd, a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void DnsPrinter::appent_element(real4_t a)
{
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " % .*e", nd, a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void DnsPrinter::appent_element(complex_t a)
{
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " (% .*le,% .*le)", nd, a.real(), nd, a.imag());
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void DnsPrinter::appent_element(complex8_t a)
{
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " (% .*e,% .*e)", nd, a.real(), nd, a.imag());
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
template <typename T>
void DnsPrinter::append_page_ith_row(uint_t i, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower)
{
	nint_t nd = m_row_numdigits;
	std::sprintf(m_cbuff, "%*" _UFMT_ " |", nd, i);
	m_str.append(m_cbuff);

	nd = m_nsd;
	for(uint_t j = jbgn; j < jend; j++) {
		if(lower && j > i) break;
		appent_extra_spaces();
		appent_element(entry(lda,a,i,j));
	} // j

	m_str.append("\n");
}
/*-------------------------------------------------*/
template <typename T>
void DnsPrinter::append_page(uint_t m, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower)
{
	append_page_header(jbgn, jend);
	
	for(uint_t i = 0; i < m; i++) {
		append_page_ith_row(i, jbgn, jend, a, lda, lower);
	} // i

	m_str.append("\n");
}
/*-------------------------------------------------*/
void DnsPrinter::reserve(uint_t m, uint_t n)
{
	m_str.reserve(m * n * m_element_length_max); // rough estimation
}
/*-------------------------------------------------*/
template <typename T>
void DnsPrinter::fill(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	uint_t columns_per_page = count_columns_per_page(n);

	uint_t num_pages = n / columns_per_page;
	uint_t rem_cols = n % columns_per_page;

	for(uint_t ipage = 0; ipage < num_pages; ipage++) {
		uint_t jbgn = ipage * columns_per_page;
		uint_t jend = jbgn + columns_per_page;
		append_page(m, jbgn, jend, a, lda, lower);
	} // ipage

	if(rem_cols) {
		uint_t jbgn = num_pages * columns_per_page;
		uint_t jend = n;
		append_page(m, jbgn, jend, a, lda, lower);
	} // rem_cols
}
/*-------------------------------------------------*/
template <typename T>
std::string DnsPrinter::print2str_real(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = m_nsd + 8;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserve(m, n);
	fill(m, n, a, lda, lower);

	return m_str;
}
/*-------------------------------------------------*/
std::string DnsPrinter::print2str(uint_t m, uint_t n, const real_t  *a, uint_t lda, bool lower) { return print2str_real(m, n, a, lda, lower); }
std::string DnsPrinter::print2str(uint_t m, uint_t n, const real4_t *a, uint_t lda, bool lower) { return print2str_real(m, n, a, lda, lower); }
/*-------------------------------------------------*/
template <typename T>
std::string DnsPrinter::print2str_complex(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = 2 * m_nsd + 18;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserve(m, n);
	fill(m, n, a, lda, lower);

	return m_str;
}
/*-------------------------------------------------*/
std::string DnsPrinter::print2str(uint_t m, uint_t n, const complex_t  *a, uint_t lda, bool lower) { return print2str_complex(m, n, a, lda, lower); }
std::string DnsPrinter::print2str(uint_t m, uint_t n, const complex8_t *a, uint_t lda, bool lower) { return print2str_complex(m, n, a, lda, lower); }
/*-------------------------------------------------*/
template <typename T>
void DnsPrinter::print(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	std::string str = print2str(m, n, a, lda, lower);
	std::printf("%s", str.c_str());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
std::string print2str_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	if(!m || !n) return "";

	bool lower = check(ptype, m, n, a, lda);

	DnsPrinter printer(nsd, line_maxlen);
	return printer.print2str(m, n, a, lda, lower);
}
/*-------------------------------------------------*/
std::string print2str(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print2str_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print2str(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print2str_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print2str(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print2str_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print2str(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print2str_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
template <typename T>
void print_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	if(!m || !n) return;

	bool lower = check(ptype, m, n, a, lda);

	DnsPrinter printer(nsd, line_maxlen);
	printer.print(m, n, a, lda, lower);
}
/*-------------------------------------------------*/
void print(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
} // namespace bulk
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
