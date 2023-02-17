#ifndef CLA3P_UNIVERSAL_HPP_
#define CLA3P_UNIVERSAL_HPP_

/** 
 * @file
 * Basic object identification & meta data.
 */

#include <string>

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

class UniversalMetaTypes {

	protected:
		enum class ObjectType {
			NONE       = 0,
			DNS_VECTOR    ,
			DNS_MATRIX    ,
			CSC_VECTOR    ,
			CSC_MATRIX     
		};

		enum class DataType {
			NONE    = 0,
			INT        ,
			UINT       ,
			REAL       ,
			COMPLEX
		};

		enum class PrecisionType {
			NONE   = 0,
			SINGLE    ,
			DOUBLE     
		};

		UniversalMetaTypes(ObjectType otype, DataType dtype, PrecisionType ptype);
		~UniversalMetaTypes();

		ObjectType    otype() const;
		DataType      dtype() const;
		PrecisionType ptype() const;

		const std::string&  objTypeName() const;
		const std::string& dataTypeName() const;
		const std::string& precTypeName() const;

	private:
		const ObjectType    m_otype;
		const DataType      m_dtype;
		const PrecisionType m_ptype;
};

/*-------------------------------------------------*/

/**
 * @brief The universal metadata class.
 *
 * All objects inherit from this class.
 */
class UniversalMetaData {

	public:

		/**
		 * @brief Test whether object is empty.
		 * @return whether the object is empty.
		 */
		bool empty() const;

		/**
		 * @brief Test whether object is the owner of its contents.
		 *
		 * If the ownership flag is true, the object is responsible for deallocation of its contents. @n
		 * The content memory is deallocated on object destruction.
		 *
		 * @return whether the object is the owner of its contents.
		 */
		bool owner() const;

		/**
		 * @brief Unties data from object.
		 *
		 * Makes the object no longer responsible for content deallocation. @n
		 * Use with caution as it may lead to memory leaks if the contents are not deallocated by the user. @n
		 * Deallocate automatically allocated data using i_free().
		 */
		void unbind();

	protected:
		UniversalMetaData();
		~UniversalMetaData();

		uint_t rsize() const;
		uint_t csize() const;

		void setAllMeta(uint_t rsize, uint_t csize, bool owner);
		void defaults();

	private:
		uint_t m_rsize;
		uint_t m_csize;
		bool   m_owner;

		void setRsize(uint_t rsize);
		void setCsize(uint_t csize);
		void setOwner(bool   owner);
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_UNIVERSAL_HPP_
