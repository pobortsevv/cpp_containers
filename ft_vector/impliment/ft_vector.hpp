#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

/* -------------------------------- Macroses -------------------------------- */

/* -------------------------------------------------------------------------- */

/* -------------------------------- Libaries -------------------------------- */
# include <memory>

/* -------------------------------------------------------------------------- */

/* ------------------------------ FT Namespace ------------------------------ */
namespace ft {

	template <typename T, typename Allocator = std::allocator<T> >
	class vector 
	{
		public:
			typedef Allocator								allocator_type;
			typedef std::allocator_traits<allocator_type>	traits;
			// allocator_traits class template provides the standardized way to access various properties of allocators.

		protected:
			// Name requirements for c++ container:
			typedef T			value_type;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef	typename traits::pointer	pointer;
			typedef typename traits::const_pointer const_pointer;
			typedef pointer		iterator;
			typedef const_pointer const_iterator;

			typedef size_t size_type;
			typedef signed int difference_type;

			pointer arr;
			size_type sz;
			size_type cap;
	};


}
/* -------------------------------------------------------------------------- */

#endif
