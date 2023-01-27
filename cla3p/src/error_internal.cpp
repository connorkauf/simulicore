// this file inc
#include "error_internal.hpp"

// system
#include <iostream>
#include <mutex>

// 3rd

// cla3p

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
		std::cout << "Warning: in file '" << file << "' line " << line << "function '" << fun << "' -> " << msg << std::endl;
		messaging_mutex().unlock();
	} // show_dbg_messages
}
/*-------------------------------------------------*/
void Error_with_args(const std::string& msg, const char *file, const char *fun, nint_t line)
{
	if(show_dbg_messages()) {
		messaging_mutex().lock();
		std::cout << "Error: in file '" << file << "' line " << line << "function '" << fun << "' -> " << msg << std::endl;
		messaging_mutex().unlock();
	} // show_dbg_messages
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
