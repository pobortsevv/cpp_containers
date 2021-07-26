#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

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
	
	template < class T, class P, class R>
	class wrap_iter
	{
		public:
			typedef ptrdiff_t                           difference_type;
			typedef T                                   value_type;
			typedef P                                   pointer;
			typedef R                                   reference;
			typedef std::random_access_iterator_tag     iterator_category;
			typedef wrap_iter<value_type, pointer, reference> this_type;
		private:
			pointer _i;
		public:
			wrap_iter(void) : _i(nullptr) {} // default
			explicit wrap_iter(this_type const &x) : _i(x.base()) {} // copy
			explicit ~wrap_iter(void) {this->_i = nullptr;}

			this_type & operator=(this_type const & rhs)
			{
				if (*this == rhs)
					return *this;
				this->_i = rhs.base();
				return *this;
			}
			inline reference operator*(void) const {return *this->_i;}
			inline pointer operator->(void) const {return this->_i;}
			inline reference operator[](difference_type index) const {return this->_i[index];}
			inline this_type &operator++(void) {this->_i++; return *this;}
			inline this_type operator++(int) const {this_type tmp(*this); ++(*this); return tmp;}
			inline this_type &operator--(void) {this->_i--; return *this;}
			inline this_type operator--(int) const {this_type tmp(*this); --(*this); return tmp;}
			inline this_type &operator+=(difference_type n) {this->_i + n; return *this;}
			inline this_type &operator-=(difference_type n) {this->_i - n; return *this;}
			inline this_type operator+(difference_type n) const {this_type tmp(*this); tmp += n; return tmp;}
			inline this_type operator-(difference_type n) const {this_type tmp(*this); tmp -= n; return tmp;}

			inline pointer base(void) const {return this->_i;}
	};

	# define WRAP_TEMPLATE template < class T, class P, class R>
	# define TYPE_TEMPLATE wrap_iter<T, P, R>

	WRAP_TEMPLATE
	inline bool operator==(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return lhs.base() == rhs.base();
	}
	WRAP_TEMPLATE
	inline bool operator!=(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return !(lhs.base() == rhs.base());
	}
	WRAP_TEMPLATE
	inline bool operator>(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return lhs.base() > rhs.base();
	}
	WRAP_TEMPLATE
	inline bool operator<(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return lhs.base() < rhs.base();
	}
	WRAP_TEMPLATE
	inline bool operator>=(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return !(lhs.base() < rhs.base());
	}
	WRAP_TEMPLATE
	inline bool operator<=(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return !(lhs.base() > rhs.base());
	}
	WRAP_TEMPLATE
	inline typename TYPE_TEMPLATE::difference_type operator-(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs)
	{
		return lhs.base() - rhs.base();
	}
	WRAP_TEMPLATE
	inline TYPE_TEMPLATE operator+(typename TYPE_TEMPLATE::difference_type n, TYPE_TEMPLATE const & rhs)
	{
		rhs += n;
		return rhs;
	}
}

#endif
