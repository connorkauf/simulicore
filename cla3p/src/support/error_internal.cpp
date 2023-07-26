// this file inc
#include "error_internal.hpp"

// system
#include <iostream>

// 3rd

// cla3p
#include "utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static bool show_dbg_messages_ = false;
/*-------------------------------------------------*/
void enable_dbg_messages()
{
	show_dbg_messages_ = true;
}
/*-------------------------------------------------*/
void disable_dbg_messages()
{
	show_dbg_messages_ = false;
}
/*-------------------------------------------------*/
bool show_dbg_messages()
{
	return show_dbg_messages_;
}
/*-------------------------------------------------*/
void Warning_with_args(const std::string& msg, const char *file, const char *fun, nint_t line)
{
	if(show_dbg_messages()) {
		std::cout << "Warning: in file '" << extract_filename(file) << ":" << line << "' function '" << fun << "' -> " << msg << std::endl;
	} // show_dbg_messages
}
/*-------------------------------------------------*/
void Error_with_args(const std::string& msg, const char *file, const char *fun, nint_t line)
{
	if(show_dbg_messages()) {
		std::cout << "Error: in file '" << extract_filename(file) << ":" << line << "' function '" << fun << "' -> " << msg << std::endl;
	} // show_dbg_messages
}
/*-------------------------------------------------*/
namespace msg {
/*-------------------------------------------------*/
std::string out_of_bounds(uint_t m, uint_t n, uint_t i, uint_t j)
{
	std::string ret1 = "requested index (" + std::to_string(i) + "," + std::to_string(j) + ")";
	std::string ret2 = " of matrix with dimensions (" + std::to_string(m) + " x " + std::to_string(n) + ")";

	return (ret1 + ret2);
}
/*-------------------------------------------------*/
std::string out_of_bounds(uint_t n, uint_t i)
{
	std::string ret1 = "requested index " + std::to_string(i);
	std::string ret2 = " of vector with size " + std::to_string(n);

	return (ret1 + ret2);
}
/*-------------------------------------------------*/
static const std::string const_msg_unknown                     = "Unknown status";
static const std::string const_msg_success                     = "Success";
static const std::string const_msg_invalid_dimensions          = "Invalid/mismatching dimension(s)";
static const std::string const_msg_invalid_pointer             = "Invalid pointer(s)";
static const std::string const_msg_invalid_leading_dimension   = "Invalid leading dimension";
static const std::string const_msg_invalid_property            = "Invalid/mismatching property(/ies)";
static const std::string const_msg_invalid_property_for_square = "Property requires square matrix";
static const std::string const_msg_empty_object                = "Empty object(s) detected";
static const std::string const_msg_op_not_allowed              = "This operation is not allowed";
static const std::string const_msg_lapack_error                = "Lapack error";
static const std::string const_division_by_zero                = "Division by zero detected";
/*-------------------------------------------------*/
const std::string& unknown()                     { return const_msg_unknown                    ; }
const std::string& success()                     { return const_msg_success                    ; }
const std::string& invalid_dimensions()          { return const_msg_invalid_dimensions         ; }
const std::string& invalid_pointer()             { return const_msg_invalid_pointer            ; }
const std::string& invalid_leading_dimension()   { return const_msg_invalid_leading_dimension  ; }
const std::string& invalid_property()            { return const_msg_invalid_property           ; }
const std::string& invalid_property_for_square() { return const_msg_invalid_property_for_square; }
const std::string& empty_object()                { return const_msg_empty_object               ; }
const std::string& op_not_allowed()              { return const_msg_op_not_allowed             ; }
const std::string& lapack_error()                { return const_msg_lapack_error               ; }
const std::string& division_by_zero()            { return const_division_by_zero               ; }
/*-------------------------------------------------*/
} // namespace msg
/*-------------------------------------------------*/
#if 0
Status::Status()
	: m_type(status_t::SUCCESS)
{
}
/*-------------------------------------------------*/
Status::Status(status_t type)
	: m_type(type)
{
}
/*-------------------------------------------------*/
Status::Status(const Status& src)
	: m_type(src.type())
{
}
/*-------------------------------------------------*/
Status& Status::operator=(const Status& src)
{
	m_type = src.type();
	return *this;
}
/*-------------------------------------------------*/
Status::~Status()
{
}
/*-------------------------------------------------*/
status_t Status::type() const
{
	return m_type;
}
/*-------------------------------------------------*/
bool Status::success() const
{
	return (type() == status_t::SUCCESS);
}
/*-------------------------------------------------*/
const std::string& Status::message() const
{
	/**/ if(type() == status_t::SUCCESS    ) return msg_success()                    ;
	else if(type() == status_t::ERROR_DIM  ) return msg_invalid_dimensions()         ;
	else if(type() == status_t::ERROR_PTR  ) return msg_invalid_pointer()            ;
	else if(type() == status_t::ERROR_LD   ) return msg_invalid_leading_dimension()  ;
	else if(type() == status_t::ERROR_PROP ) return msg_invalid_property()           ;
	else if(type() == status_t::ERROR_PRSQ ) return msg_invalid_property_for_square();
	else if(type() == status_t::ERROR_EMPTY) return msg_empty_object()               ;

	return msg_unknown();
}
#endif
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
