#ifndef TRAITS_HPP
# define TRAITS_HPP

// Standard algorithms determine certain properties of the iterators passed to them
// and the range they represent by using the members of the 
// corresponding iterator_traits instantiation.

# include <type_traits>

namespace ft {
	
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef T	value_type;
		typedef T*	pointer;
		typedef T&	reference;
		typedef std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef T	value_type;
		typedef const T*	pointer;
		typedef const T&	reference;
		typedef std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };
} 

#endif