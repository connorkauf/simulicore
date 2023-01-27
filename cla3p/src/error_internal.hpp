#ifndef CLA3P_ERROR_INTERNAL_HPP_
#define CLA3P_ERROR_INTERNAL_HPP_

#include <string>
#include <sstream>

#include "types.hpp"

#define Warning(msg) \
	do { \
		if(cla3p::show_dbg_messages()) { \
			std::stringstream ss_; \
			ss_ << msg; \
			cla3p::Warning_with_args(ss_.str(), __FILE__, __func__, __LINE__); \
		} \
	} while(0)

#define WarningNoReach() Warning("Should not reach here...")

#define Error(msg) \
	do { \
		if(cla3p::show_dbg_messages()) { \
			std::stringstream ss_; \
			ss_ << msg; \
			cla3p::Error_with_args(ss_.str(), __FILE__, __func__, __LINE__); \
		} \
	} while(0)

#define ErrorNoReach() Error("Should not reach here...")

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void enable_dbg_messages();
void disable_dbg_messages();
bool show_dbg_messages();

void Warning_with_args(const std::string& msg, const char *file, const char *fun, nint_t line);
void Error_with_args(const std::string& msg, const char *file, const char *fun, nint_t line);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_INTERNAL_HPP_
