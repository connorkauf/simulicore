#ifndef CLA3P_DNS_GENERIC_HPP_
#define CLA3P_DNS_GENERIC_HPP_

#include <iostream>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/

template <class T>
class GenericObject {

	public:
	//protected:
		GenericObject();
		~GenericObject();

		GenericObject(const GenericObject&) = delete;
		GenericObject& operator=(const GenericObject&) = delete;

		GenericObject(GenericObject&&);
		GenericObject& operator=(GenericObject&&);

		void set_nrows (uint_t           nrows );
		void set_ncols (uint_t           ncols );
		void set_ld    (uint_t           ld    );
		void set_values(T*               values);
		void set_prop  (const Property&  prop  );
		void set_owner (bool             owner );

		uint_t          nrows () const;
		uint_t          ncols () const;
		uint_t          ld    () const;
		T*              values()      ;
		const T*        values() const;
		const Property& prop  () const;
		bool            owner () const;

		void clear();
		void unbind();

		GenericObject copy() const;
		GenericObject move();

		void info(const std::string& msg) const; // FIXME: remove this, final-object-specific
		void print(uint_t nsd = 3) const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

		// static members
		static uint_t const defaultld = 0;
		static GenericObject init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = defaultld);
		static GenericObject zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = defaultld);
		static GenericObject random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = defaultld);

	private:
		uint_t   m_nrows ;
		uint_t   m_ncols ;
		uint_t   m_ld    ;
		T*       m_values;
		Property m_prop  ;
		bool     m_owner ;

		GenericObject(uint_t nrows, uint_t ncols, T *values, uint_t ld, const Property& prop, bool owner);
		void defaults();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_GENERIC_HPP_
