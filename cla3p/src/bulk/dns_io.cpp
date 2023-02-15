// this file inc
#include "dns_io.hpp"

// system
#include <cstdio>
#include <algorithm>

// 3rd

// cla3p
#include "../checks/all_checks.hpp"
#include "../support/utils.hpp"
#include "dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
class Printer {

	public:
		Printer(uint_t nsd, uint_t line_maxlen);
		~Printer();

		std::string printToString(uint_t m, uint_t n, const int_t *a, uint_t lda, bool lower);
		std::string printToString(uint_t m, uint_t n, const uint_t *a, uint_t lda, bool lower);
		std::string printToString(uint_t m, uint_t n, const real_t *a, uint_t lda, bool lower);
		std::string printToString(uint_t m, uint_t n, const real4_t *a, uint_t lda, bool lower);
		std::string printToString(uint_t m, uint_t n, const complex_t *a, uint_t lda, bool lower);
		std::string printToString(uint_t m, uint_t n, const complex8_t *a, uint_t lda, bool lower);

		template <typename T>
		void print(uint_t m, uint_t n, T *a, uint_t lda, bool lower);

	private:
		void reset();
		void reserveStringSpace(uint_t m, uint_t n);

		template <typename T>
		std::string printToStringInt(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		std::string printToStringReal(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		std::string printToStringComplex(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		void fillString(uint_t m, uint_t n, T *a, uint_t lda, bool lower);
		template <typename T>
		void appendPage(uint_t m, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower);
		template <typename T>
		void appendIthRowOfPage(uint_t i, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower);

		uint_t countColumnsPerPage(uint_t n);
		void appendPageHeader(uint_t jbgn, uint_t jend);
		void appendExtraSpaces();
		void appendElement(int_t a);
		void appendElement(uint_t a);
		void appendElement(real_t a);
		void appendElement(real4_t a);
		void appendElement(complex_t a);
		void appendElement(complex8_t a);

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
Printer::Printer(uint_t nsd, uint_t line_maxlen)
	: 
		m_nsd(sanitized_nsd(nsd)), 
		m_line_maxlen(line_maxlen)
{
	reset();
}
/*-------------------------------------------------*/
Printer::~Printer()
{
	reset();
}
/*-------------------------------------------------*/
void Printer::reset()
{
	m_row_numdigits      = 0;
	m_col_numdigits      = 0;
	m_element_length     = 0;
	m_element_length_max = 0;

	m_str.clear();
}
/*-------------------------------------------------*/
uint_t Printer::countColumnsPerPage(uint_t n)
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
void Printer::appendPageHeader(uint_t jbgn, uint_t jend)
{
	nint_t nd = m_row_numdigits;
	std::sprintf(m_cbuff, "%*s  ", nd, "");
	m_str.append(m_cbuff);

	nd = m_element_length_max;
	for(uint_t j = jbgn; j < jend; j++) {
		std::sprintf(m_cbuff, "%*" _UFMT_ , nd, j);
		m_str.append(m_cbuff);
	} // j

	m_str.append("\n");
}
/*-------------------------------------------------*/
void Printer::appendExtraSpaces()
{
	nint_t extra_spaces = m_element_length_max - m_element_length;

	if(extra_spaces) {
		std::sprintf(m_cbuff, "%*s", extra_spaces, "");
		m_str.append(m_cbuff);
	} // extra_spaces
}
/*-------------------------------------------------*/
void Printer::appendElement(int_t a)
{
	nint_t nd = m_element_length_max;
	std::sprintf(m_cbuff, "%*" _DFMT_ , nd, a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(uint_t a)
{
	nint_t nd = m_element_length_max;
	std::sprintf(m_cbuff, "%*" _UFMT_ , nd, a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(real_t a)
{
	appendExtraSpaces();
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " % .*le", nd, a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(real4_t a)
{
	appendExtraSpaces();
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " % .*e", nd, a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(complex_t a)
{
	appendExtraSpaces();
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " (% .*le,% .*le)", nd, a.real(), nd, a.imag());
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(complex8_t a)
{
	appendExtraSpaces();
	nint_t nd = m_nsd;
	std::sprintf(m_cbuff, " (% .*e,% .*e)", nd, a.real(), nd, a.imag());
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
template <typename T>
void Printer::appendIthRowOfPage(uint_t i, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower)
{
	nint_t nd = m_row_numdigits;
	std::sprintf(m_cbuff, "%*" _UFMT_ " |", nd, i);
	m_str.append(m_cbuff);

	nd = m_nsd;
	for(uint_t j = jbgn; j < jend; j++) {
		if(lower && j > i) break;
		appendElement(entry(lda,a,i,j));
	} // j

	m_str.append("\n");
}
/*-------------------------------------------------*/
template <typename T>
void Printer::appendPage(uint_t m, uint_t jbgn, uint_t jend, T *a, uint_t lda, bool lower)
{
	appendPageHeader(jbgn, jend);
	
	for(uint_t i = 0; i < m; i++) {
		appendIthRowOfPage(i, jbgn, jend, a, lda, lower);
	} // i

	m_str.append("\n");
}
/*-------------------------------------------------*/
void Printer::reserveStringSpace(uint_t m, uint_t n)
{
	m_str.reserve(m * n * m_element_length_max); // rough estimation
}
/*-------------------------------------------------*/
template <typename T>
void Printer::fillString(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	uint_t columns_per_page = countColumnsPerPage(n);

	uint_t num_pages = n / columns_per_page;
	uint_t rem_cols = n % columns_per_page;

	for(uint_t ipage = 0; ipage < num_pages; ipage++) {
		uint_t jbgn = ipage * columns_per_page;
		uint_t jend = jbgn + columns_per_page;
		appendPage(m, jbgn, jend, a, lda, lower);
	} // ipage

	if(rem_cols) {
		uint_t jbgn = num_pages * columns_per_page;
		uint_t jend = n;
		appendPage(m, jbgn, jend, a, lda, lower);
	} // rem_cols
}
/*-------------------------------------------------*/
template <typename T>
static uint_t calc_max_ilen(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	uint_t maxlen = 0;

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			if(lower && j > i) break;
			maxlen = std::max(maxlen, inumlen(entry(lda,a,i,j)));
		} // i
	} // j

	return maxlen;
}
/*-------------------------------------------------*/
template <typename T>
std::string Printer::printToStringInt(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = calc_max_ilen(m,n,a,lda,lower) + 2;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserveStringSpace(m, n);
	fillString(m, n, a, lda, lower);

	return m_str;
}
/*-------------------------------------------------*/
std::string Printer::printToString(uint_t m, uint_t n, const int_t  *a, uint_t lda, bool lower) { return printToStringInt(m, n, a, lda, lower); }
std::string Printer::printToString(uint_t m, uint_t n, const uint_t *a, uint_t lda, bool lower) { return printToStringInt(m, n, a, lda, lower); }
/*-------------------------------------------------*/
template <typename T>
std::string Printer::printToStringReal(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = m_nsd + 8;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserveStringSpace(m, n);
	fillString(m, n, a, lda, lower);

	return m_str;
}
/*-------------------------------------------------*/
std::string Printer::printToString(uint_t m, uint_t n, const real_t  *a, uint_t lda, bool lower) { return printToStringReal(m, n, a, lda, lower); }
std::string Printer::printToString(uint_t m, uint_t n, const real4_t *a, uint_t lda, bool lower) { return printToStringReal(m, n, a, lda, lower); }
/*-------------------------------------------------*/
template <typename T>
std::string Printer::printToStringComplex(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = 2 * m_nsd + 18;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserveStringSpace(m, n);
	fillString(m, n, a, lda, lower);

	return m_str;
}
/*-------------------------------------------------*/
std::string Printer::printToString(uint_t m, uint_t n, const complex_t  *a, uint_t lda, bool lower) { return printToStringComplex(m, n, a, lda, lower); }
std::string Printer::printToString(uint_t m, uint_t n, const complex8_t *a, uint_t lda, bool lower) { return printToStringComplex(m, n, a, lda, lower); }
/*-------------------------------------------------*/
template <typename T>
void Printer::print(uint_t m, uint_t n, T *a, uint_t lda, bool lower)
{
	std::string str = printToString(m, n, a, lda, lower);
	std::printf("%s", str.c_str());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
std::string print_to_string_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	if(!m || !n) return "";

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	Printer printer(nsd, line_maxlen);
	return printer.printToString(m, n, a, lda, lower);
}
/*-------------------------------------------------*/
std::string print_to_string(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/

std::string print_to_string(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
template <typename T>
void print_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	Printer printer(nsd, line_maxlen);
	printer.print(m, n, a, lda, lower);
}
/*-------------------------------------------------*/
void print(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(ptype, m, n, a, lda, nsd, line_maxlen);
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
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
