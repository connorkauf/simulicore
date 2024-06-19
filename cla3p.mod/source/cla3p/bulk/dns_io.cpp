/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/bulk/dns_io.hpp"

// system
#include <cstdio>
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/bulk/dns.hpp"
#include "cla3p/support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace blk {
namespace dns {
/*-------------------------------------------------*/
#define PRINTER_BUFFER_SIZE 128
/*-------------------------------------------------*/
class Printer {

	public:
		Printer(uint_t nsd, uint_t line_maxlen);
		~Printer();

		std::string printToString(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda);
		std::string printToString(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda);
		std::string printToString(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda);
		std::string printToString(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda);
		std::string printToString(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda);
		std::string printToString(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda);

		template <typename T_Scalar>
		void print(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda);

	private:
		void reset();
		void reserveStringSpace(uint_t m, uint_t n);

		template <typename T_Scalar>
		std::string printToStringInt(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda);
		template <typename T_Scalar>
		std::string printToStringReal(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda);
		template <typename T_Scalar>
		std::string printToStringComplex(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda);
		template <typename T_Scalar>
		void fillString(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda);
		template <typename T_Scalar>
		void appendPage(uplo_t uplo, uint_t m, uint_t jbgn, uint_t jend, T_Scalar *a, uint_t lda);
		template <typename T_Scalar>
		void appendIthRowOfPage(uplo_t uplo, uint_t i, uint_t jbgn, uint_t jend, T_Scalar *a, uint_t lda);

		uint_t countColumnsPerPage(uint_t n);
		void appendPageHeader(uint_t jbgn, uint_t jend);
		void appendExtraSpaces();
		void appendEmpty();
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

		char m_cbuff[PRINTER_BUFFER_SIZE];
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
	nint_t nd = static_cast<nint_t>(m_row_numdigits);
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*s  ", nd, "");
	m_str.append(m_cbuff);

	nd = static_cast<nint_t>(m_element_length_max);
	for(uint_t j = jbgn; j < jend; j++) {
		std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*" _UFMT_ , nd, j);
		m_str.append(m_cbuff);
	} // j

	m_str.append("\n");
}
/*-------------------------------------------------*/
void Printer::appendExtraSpaces()
{
	uint_t extra_spaces = m_element_length_max - m_element_length;

	if(extra_spaces) {
		std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*s", static_cast<nint_t>(extra_spaces), "");
		m_str.append(m_cbuff);
	} // extra_spaces
}
/*-------------------------------------------------*/
void Printer::appendEmpty()
{
	uint_t nd = m_element_length_max;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*s", static_cast<nint_t>(nd), "");
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(int_t a)
{
	uint_t nd = m_element_length_max;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*" _DFMT_ , static_cast<nint_t>(nd), a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(uint_t a)
{
	uint_t nd = m_element_length_max;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*" _UFMT_ , static_cast<nint_t>(nd), a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(real_t a)
{
	appendExtraSpaces();
	uint_t nd = m_nsd;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, " % .*le", static_cast<nint_t>(nd), a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(real4_t a)
{
	appendExtraSpaces();
	uint_t nd = m_nsd;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, " % .*e", static_cast<nint_t>(nd), a);
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(complex_t a)
{
	appendExtraSpaces();
	uint_t nd = m_nsd;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, " (% .*le,% .*le)", 
		static_cast<nint_t>(nd), a.real(), 
		static_cast<nint_t>(nd), a.imag());
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
void Printer::appendElement(complex8_t a)
{
	appendExtraSpaces();
	uint_t nd = m_nsd;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, " (% .*e,% .*e)", 
		static_cast<nint_t>(nd), a.real(), 
		static_cast<nint_t>(nd), a.imag());
	m_str.append(m_cbuff);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Printer::appendIthRowOfPage(uplo_t uplo, uint_t i, uint_t jbgn, uint_t jend, T_Scalar *a, uint_t lda)
{
	uint_t nd = m_row_numdigits;
	std::snprintf(m_cbuff, PRINTER_BUFFER_SIZE, "%*" _UFMT_ " |", static_cast<nint_t>(nd), i);
	m_str.append(m_cbuff);

	nd = m_nsd;
	for(uint_t j = jbgn; j < jend; j++) {
		if(uplo == uplo_t::Upper && j < i) appendEmpty();
		else if(uplo == uplo_t::Lower && j > i) break;
		else appendElement(entry(lda,a,i,j));
	} // j

	m_str.append("\n");
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Printer::appendPage(uplo_t uplo, uint_t m, uint_t jbgn, uint_t jend, T_Scalar *a, uint_t lda)
{
	appendPageHeader(jbgn, jend);
	
	for(uint_t i = 0; i < m; i++) {
		appendIthRowOfPage(uplo, i, jbgn, jend, a, lda);
	} // i

	m_str.append("\n");
}
/*-------------------------------------------------*/
void Printer::reserveStringSpace(uint_t m, uint_t n)
{
	m_str.reserve(m * n * m_element_length_max); // rough estimation
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Printer::fillString(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	uint_t columns_per_page = countColumnsPerPage(n);

	uint_t num_pages = n / columns_per_page;
	uint_t rem_cols = n % columns_per_page;

	for(uint_t ipage = 0; ipage < num_pages; ipage++) {
		uint_t jbgn = ipage * columns_per_page;
		uint_t jend = jbgn + columns_per_page;
		appendPage(uplo, m, jbgn, jend, a, lda);
	} // ipage

	if(rem_cols) {
		uint_t jbgn = num_pages * columns_per_page;
		uint_t jend = n;
		appendPage(uplo, m, jbgn, jend, a, lda);
	} // rem_cols
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static uint_t calc_max_ilen(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	uint_t maxlen = 0;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			maxlen = std::max(maxlen, inumlen(entry(lda,a,i,j)));
		} // i
	} // j

	return maxlen;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string Printer::printToStringInt(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = calc_max_ilen(uplo,m,n,a,lda) + 2;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserveStringSpace(m, n);
	fillString(uplo, m, n, a, lda);

	return m_str;
}
/*-------------------------------------------------*/
std::string Printer::printToString(uplo_t uplo, uint_t m, uint_t n, const int_t  *a, uint_t lda) { return printToStringInt(uplo, m, n, a, lda); }
std::string Printer::printToString(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda) { return printToStringInt(uplo, m, n, a, lda); }
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string Printer::printToStringReal(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = m_nsd + 8;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserveStringSpace(m, n);
	fillString(uplo, m, n, a, lda);

	return m_str;
}
/*-------------------------------------------------*/
std::string Printer::printToString(uplo_t uplo, uint_t m, uint_t n, const real_t  *a, uint_t lda) { return printToStringReal(uplo, m, n, a, lda); }
std::string Printer::printToString(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda) { return printToStringReal(uplo, m, n, a, lda); }
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string Printer::printToStringComplex(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);
	m_element_length = 2 * m_nsd + 18;
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

	reserveStringSpace(m, n);
	fillString(uplo, m, n, a, lda);

	return m_str;
}
/*-------------------------------------------------*/
std::string Printer::printToString(uplo_t uplo, uint_t m, uint_t n, const complex_t  *a, uint_t lda) { return printToStringComplex(uplo, m, n, a, lda); }
std::string Printer::printToString(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda) { return printToStringComplex(uplo, m, n, a, lda); }
/*-------------------------------------------------*/
template <typename T_Scalar>
void Printer::print(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	std::string str = printToString(uplo, m, n, a, lda);
	std::printf("%s", str.c_str());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string print_to_string_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	if(!m || !n) return "";

	Printer printer(nsd, line_maxlen);
	return printer.printToString(uplo, m, n, a, lda);
}
/*-------------------------------------------------*/
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/

std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	return print_to_string_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void print_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	if(!m || !n) return;

	Printer printer(nsd, line_maxlen);
	printer.print(uplo, m, n, a, lda);
}
/*-------------------------------------------------*/
void print(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
void print(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd, uint_t line_maxlen)
{
	print_tmpl(uplo, m, n, a, lda, nsd, line_maxlen);
}
/*-------------------------------------------------*/
#undef PRINTER_BUFFER_SIZE
/*-------------------------------------------------*/
} // namespace dns
} // namespace blk
} // namespace cla3p
/*-------------------------------------------------*/
