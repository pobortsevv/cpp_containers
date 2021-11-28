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
	template < class Key, 
	class T,
	class Compare = less<Key>,
	class Alloc = allocator<pair<const Key,T> > >
	class map
	{
		private:
			typedef Allocator		

	};
}
/* -------------------------------------------------------------------------- */

#endif