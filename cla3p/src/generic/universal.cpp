// this file inc
#include "universal.hpp"

// system

// 3rd

// cla3p
#include "../support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
UniversalMetaTypes::UniversalMetaTypes(
		UniversalMetaTypes::ObjectType otype, 
		UniversalMetaTypes::DataType dtype, 
		UniversalMetaTypes::PrecisionType ptype)
	: 
		m_otype(otype),
		m_dtype(dtype),
		m_ptype(ptype)
{
}
/*-------------------------------------------------*/
UniversalMetaTypes::~UniversalMetaTypes()
{
}
/*-------------------------------------------------*/
UniversalMetaTypes::ObjectType    UniversalMetaTypes::otype() const { return m_otype; }
UniversalMetaTypes::DataType      UniversalMetaTypes::dtype() const { return m_dtype; }
UniversalMetaTypes::PrecisionType UniversalMetaTypes::ptype() const { return m_ptype; }
/*-------------------------------------------------*/
static const std::string str_unknown = "Unknown";
/*-------------------------------------------------*/
static const std::string str_dns_vector = "Dense Vector";
static const std::string str_dns_matrix = "Dense Matrix";
static const std::string str_csc_vector = "Sparse (csc) Vector";
static const std::string str_csc_matrix = "Sparse (csc) Matrix";
/*-------------------------------------------------*/
const std::string& UniversalMetaTypes::objTypeName() const
{
	if(otype() == ObjectType::DNS_VECTOR) return str_dns_vector;
	if(otype() == ObjectType::DNS_MATRIX) return str_dns_matrix;
	if(otype() == ObjectType::CSC_VECTOR) return str_csc_vector;
	if(otype() == ObjectType::CSC_MATRIX) return str_csc_matrix;

	throw Exception("Unknown object type");
	return str_unknown;
}
/*-------------------------------------------------*/
static const std::string str_datatype_integer  = "Integer";
static const std::string str_datatype_unsigned = "Unsigned integer";
static const std::string str_datatype_real     = "Real";
static const std::string str_datatype_complex  = "Complex";
/*-------------------------------------------------*/
const std::string& UniversalMetaTypes::dataTypeName() const
{
	if(dtype() == DataType::INT    ) return str_datatype_integer ;
	if(dtype() == DataType::UINT   ) return str_datatype_unsigned;
	if(dtype() == DataType::REAL   ) return str_datatype_real    ;
	if(dtype() == DataType::COMPLEX) return str_datatype_complex ;

	throw Exception("Unknown data type");
	return str_unknown;
}
/*-------------------------------------------------*/
static const std::string str_precision_single = "Single (32bit)";
static const std::string str_precision_double = "Double (64bit)";
/*-------------------------------------------------*/
const std::string& UniversalMetaTypes::precTypeName() const
{
	if(ptype() == PrecisionType::SINGLE) return str_precision_single;
	if(ptype() == PrecisionType::DOUBLE) return str_precision_double;

	throw Exception("Unknown precision type");
	return str_unknown;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
UniversalMetaData::UniversalMetaData()
{
	defaults();
}
/*-------------------------------------------------*/
UniversalMetaData::~UniversalMetaData()
{
}
/*-------------------------------------------------*/
uint_t UniversalMetaData::rsize() const { return m_rsize; }
uint_t UniversalMetaData::csize() const { return m_csize; }
bool   UniversalMetaData::owner() const { return m_owner; }
/*-------------------------------------------------*/
void UniversalMetaData::setRsize(uint_t rsize) { m_rsize = rsize; }
void UniversalMetaData::setCsize(uint_t csize) { m_csize = csize; }
void UniversalMetaData::setOwner(bool   owner) { m_owner = owner; }
/*-------------------------------------------------*/
void UniversalMetaData::setAllMeta(uint_t rsize, uint_t csize, bool owner)
{
	setRsize(rsize);
	setCsize(csize);
	setOwner(owner);
}
/*-------------------------------------------------*/
void UniversalMetaData::defaults()
{
	setAllMeta(0, 0, false);
}
/*-------------------------------------------------*/
bool UniversalMetaData::empty() const
{
	return (!rsize() || !csize());
}
/*-------------------------------------------------*/
void UniversalMetaData::unbind()
{
	setOwner(false);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
