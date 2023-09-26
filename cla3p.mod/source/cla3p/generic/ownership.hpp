#ifndef CLA3P_OWNERSHIP_HPP_
#define CLA3P_OWNERSHIP_HPP_

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The ownership metadata class.
 */
class Ownership {

	public:
		Ownership();
		~Ownership();

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
		 * Deallocate auto-allocated data using i_free().
		 */
		void unbind();

	protected:
		void setOwner(bool owner);

		void clear();

	private:
		bool m_owner;

		void defaults();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_OWNERSHIP_HPP_
