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

	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {}
		pair(first_type const &t1, second_type const &t2) : first(t1), second(t2) {}
		template<class U1, class U2>
		pair(ft::pair<U1, U2> const &p) : first(p.first), second(p.second) {} 
		pair &operator=(pair const& p)
		{
			this->first = p.first;
			this->second = p.second;
			return *this;
		}

		void swap(ft::pair<first_type, second_type> &p)
		{
			swap(this->first, p.first);
			swap(this->second, p.second);
		}
	};
}

#endif
