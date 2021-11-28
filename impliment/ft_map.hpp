#ifndef FT_MAP_HPP
# define FT_MAP_HPP

/* -------------------------------- Macroses -------------------------------- */

/* -------------------------------------------------------------------------- */

/* --------------------------------- Headers -------------------------------- */
# include <memory>
# include <functional>
# include "red_black_tree.hpp"
# include "utility.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
/* -------------------------------------------------------------------------- */

/* ------------------------------ FT Namespace ------------------------------ */
namespace ft {
	template < typename Key, 
	typename T,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		private:
			typedef Alloc				allocator_type;
		private:
		// Name requirements for c++ container:
		typedef T										value_type;
		typedef	T&										reference;
		typedef const T&								const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef wrap_iter<pointer>						iterator;
		typedef wrap_iter<const_pointer>				const_iterator;
		typedef reverse_wrap_iter<iterator>				reverse_iterator;
		typedef reverse_wrap_iter<const_iterator>		const_reverse_iterator;

		typedef std::size_t size_type;
		typedef signed int difference_type;

	};
}
/* -------------------------------------------------------------------------- */

#endif