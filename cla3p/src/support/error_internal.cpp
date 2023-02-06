// this file inc
#include "error_internal.hpp"

// system
#include <iostream>
#include <mutex>

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
static std::mutex messaging_mutex_;
/*-------------------------------------------------*/
std::mutex& messaging_mutex()
{
	return messaging_mutex_;
}
/*-------------------------------------------------*/
void Warning_with_args(const std::string& msg, const char *file, const char *fun, nint_t line)
{
	if(show_dbg_messages()) {
		messaging_mutex().lock();
		std::cout << "Warning: in file '" << extract_filename(file) << ":" << line << "' function '" << fun << "' -> " << msg << std::endl;
		messaging_mutex().unlock();
	} // show_dbg_messages
}
/*-------------------------------------------------*/
void Error_with_args(const std::string& msg, const char *file, const char *fun, nint_t line)
{
	if(show_dbg_messages()) {
		messaging_mutex().lock();
		std::cout << "Error: in file '" << extract_filename(file) << ":" << line << "' function '" << fun << "' -> " << msg << std::endl;
		messaging_mutex().unlock();
	} // show_dbg_messages
}
/*-------------------------------------------------*/
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
static const std::string const_msg_unknown                     = "Unknown status";
static const std::string const_msg_success                     = "Success";
static const std::string const_msg_invalid_dimensions          = "Invalid/mismatching dimensions";
static const std::string const_msg_invald_pointer              = "Invalid pointer";
static const std::string const_msg_invalid_leading_dimension   = "Invalid leading dimension";
static const std::string const_msg_invalid_property            = "Invalid property";
static const std::string const_msg_invalid_property_for_square = "Property requires square matrix";
static const std::string const_msg_empty_object                = "Empty object(s) detected";
/*-------------------------------------------------*/
const std::string& msg_unknown()                      { return const_msg_unknown                    ; }
const std::string& msg_success()                      { return const_msg_success                    ; }
const std::string& msg_invalid_dimensions()           { return const_msg_invalid_dimensions         ; }
const std::string& msg_invald_pointer()               { return const_msg_invald_pointer             ; }
const std::string& msg_invalid_leading_dimension()    { return const_msg_invalid_leading_dimension  ; }
const std::string& msg_invalid_property()             { return const_msg_invalid_property           ; }
const std::string& msg_invalid_property_for_square()  { return const_msg_invalid_property_for_square; }
const std::string& msg_empty_object()                 { return const_msg_empty_object               ; }
/*-------------------------------------------------*/
const std::string& Status::message() const
{
	/**/ if(type() == status_t::SUCCESS    ) return msg_success()                    ;
	else if(type() == status_t::ERROR_DIM  ) return msg_invalid_dimensions()         ;
	else if(type() == status_t::ERROR_PTR  ) return msg_invald_pointer()             ;
	else if(type() == status_t::ERROR_LD   ) return msg_invalid_leading_dimension()  ;
	else if(type() == status_t::ERROR_PROP ) return msg_invalid_property()           ;
	else if(type() == status_t::ERROR_PRSQ ) return msg_invalid_property_for_square();
	else if(type() == status_t::ERROR_EMPTY) return msg_empty_object()               ;

	return msg_unknown();
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
