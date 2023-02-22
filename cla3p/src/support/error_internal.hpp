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

namespace msg {

std::string out_of_bounds(uint_t m, uint_t n, uint_t i, uint_t j);
std::string out_of_bounds(uint_t n, uint_t i);

const std::string& unknown();
const std::string& success();
const std::string& invalid_dimensions();
const std::string& invalid_pointer();
const std::string& invalid_leading_dimension();
const std::string& invalid_property();
const std::string& invalid_property_for_square();
const std::string& empty_object();
const std::string& op_not_allowed();
const std::string& lapack_error();

} // namespace msg

#if 0
class Status {

	public:
		enum class status_t {
			SUCCESS     = 0,
			ERROR_DIM      ,
			ERROR_PTR      ,
			ERROR_LD       ,
			ERROR_PROP     ,
			ERROR_PRSQ     ,
			ERROR_EMPTY    
		};

		Status();
		explicit Status(status_t);
		~Status();

		Status(const Status&);
		Status& operator=(const Status&);

		status_t type() const;
		bool success() const;
		const std::string& message() const;

	private:
		status_t m_type;
};
using status_t = Status::status_t;
#endif

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_INTERNAL_HPP_
