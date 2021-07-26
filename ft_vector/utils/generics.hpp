#ifndef GENERICS_HPP
# define GENERICS_HPP

namespace ft {

	template<typename T>
	void swap(T & lhs, T & rhs)
	{
		T buf(rhs);
		rhs = lhs;
		lhs = buf;
	}
}

#endif
