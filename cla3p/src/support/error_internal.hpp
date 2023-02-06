#ifndef CLA3P_ERROR_INTERNAL_HPP_
#define CLA3P_ERROR_INTERNAL_HPP_

#include <string>
#include <sstream>

#include "../types.hpp"

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

enum class status_t {
	SUCCESS     = 0,
	ERROR_DIM      ,
	ERROR_PTR      ,
	ERROR_LD       ,
	ERROR_PROP     ,
	ERROR_PRSQ     ,
	ERROR_EMPTY    
};

const std::string& msg_unknown();
const std::string& msg_success();
const std::string& msg_invalid_dimensions();
const std::string& msg_invald_pointer();
const std::string& msg_invalid_leading_dimension();
const std::string& msg_invalid_property();
const std::string& msg_invalid_property_for_square();
const std::string& msg_empty_object();


class Status {
	public:
		Status();
		Status(const Status&);
		Status& operator=(const Status&);
		explicit Status(status_t);
		~Status();

		status_t type() const;
		bool success() const;
		const std::string& message() const;

	private:
		status_t m_type;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_INTERNAL_HPP_
