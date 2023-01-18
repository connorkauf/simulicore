// this file inc
#include "dns_io.hpp"

// system
#include <cstdio>
#include <algorithm>

// 3rd

// cla3p
#include "utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
class Dns_printer {

	public:
		Dns_printer(uint_t nsd, uint_t line_maxlen);
		~Dns_printer();

		void print(uint_t m, uint_t n, const real_t *a, uint_t lda, bool lower);

	private:
		void reset();
		uint_t count_columns_per_page(uint_t m, uint_t n);
		void print_page(uint_t m, uint_t jbgn, uint_t jend, 
				const real_t *a, uint_t lda, bool lower) const;
		void print_page_header(uint_t jbgn, uint_t jend) const;
		void print_ith_page_row(uint_t irow, uint_t jbgn, uint_t jend, 
				const real_t *a, uint_t lda) const;

		const uint_t m_nsd;
		const uint_t m_line_maxlen;

		uint_t m_row_numdigits;
		uint_t m_col_numdigits;
		uint_t m_element_length;
		uint_t m_element_length_max;
};
/*-------------------------------------------------*/
static uint_t sanitized_nsd(uint_t nsd)
{
	const uint_t nsd_min =  1;
	const uint_t nsd_max = 16;
	nsd = std::max(nsd, nsd_min); // sanitize
	nsd = std::min(nsd, nsd_max); // sanitize

	return nsd;
}
/*-------------------------------------------------*/
Dns_printer::Dns_printer(uint_t nsd, uint_t line_maxlen)
	: 
		m_nsd(sanitized_nsd(nsd)), 
		m_line_maxlen(line_maxlen)
{
	reset();
}
/*-------------------------------------------------*/
Dns_printer::~Dns_printer()
{
	reset();
}
/*-------------------------------------------------*/
void Dns_printer::reset()
{
	m_row_numdigits      = 0;
	m_col_numdigits      = 0;
	m_element_length     = 0;
	m_element_length_max = 0;
}
/*-------------------------------------------------*/
uint_t Dns_printer::count_columns_per_page(uint_t m, uint_t n)
{
	m_element_length = m_nsd + 8; // space + sign + digit + dot + nsd + 4xexp
	m_element_length_max = std::max(m_element_length, m_col_numdigits + 1);

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
void Dns_printer::print_page_header(uint_t jbgn, uint_t jend) const
{
	nint_t nd = m_row_numdigits;
	std::printf("%*s |", nd, "");

	nd = m_element_length_max;
	for(uint_t j = jbgn; j < jend; j++) {
		std::printf("%*" _UFMT_ , nd, j);
	} // j

	std::printf("\n");
}
/*-------------------------------------------------*/
void Dns_printer::print_ith_page_row(uint_t irow, uint_t jbgn, uint_t jend, 
		const real_t *a, uint_t lda) const
{
	nint_t extra_spaces = m_element_length_max - m_element_length;

	nint_t nd = m_row_numdigits;
	std::printf("%*" _UFMT_ " |", nd, irow);

	nd = m_nsd;
	for(uint_t j = jbgn; j < jend; j++) {
		if(extra_spaces) {
			std::printf("%*s", extra_spaces, "");
		} // extra_spaces
		std::printf(" % .*le", nd, a[0]);
	} // j

	std::printf("\n");
}
/*-------------------------------------------------*/
void Dns_printer::print_page(uint_t m, uint_t jbgn, uint_t jend, 
		const real_t *a, uint_t lda, bool lower) const
{
	print_page_header(jbgn, jend);
	
	for(uint_t i = 0; i < m; i++) {
		print_ith_page_row(i, jbgn, jend, a, lda);
	} // i

	std::printf("\n");
}
/*-------------------------------------------------*/
void Dns_printer::print(uint_t m, uint_t n, const real_t *a, uint_t lda, bool lower)
{
	m_row_numdigits = inumlen(m);
	m_col_numdigits = inumlen(n);

	uint_t columns_per_page = count_columns_per_page(m, n);

	uint_t num_pages = n / columns_per_page;
	uint_t rem_cols = n % columns_per_page;

	for(uint_t ipage = 0; ipage < num_pages; ipage++) {
		uint_t jbgn = ipage * columns_per_page;
		uint_t jend = jbgn + columns_per_page;
		print_page(m, jbgn, jend, a, lda, lower);
	} // ipage

	if(rem_cols) {
		uint_t jbgn = num_pages * columns_per_page;
		uint_t jend = n;
		print_page(m, jbgn, jend, a, lda, lower);
	} // rem_cols

	reset();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
void dns_print(uint_t m, uint_t n, const real_t *a, uint_t lda, 
		bool lower, uint_t nsd, uint_t line_maxlen)
{
	Dns_printer printer(nsd, line_maxlen);
	printer.print(m, n, a, lda, lower);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
