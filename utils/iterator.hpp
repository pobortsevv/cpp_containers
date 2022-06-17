#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "traits.hpp"

namespace ft {

	template < class Iter>
	class wrap_iter {
		public:
			typedef Iter														iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category 	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type        	value_type;
			typedef typename iterator_traits<iterator_type>::difference_type   	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer           	pointer;
			typedef typename iterator_traits<iterator_type>::reference         	reference;
			typedef wrap_iter<iterator_type> this_type;
		private:
			pointer _i;
		public:
			wrap_iter(void) : _i(0) {} // default
			wrap_iter(pointer x) : _i(x) {}
			wrap_iter(this_type const &x) : _i(x.base()) {} // copy
			virtual ~wrap_iter(void) {this->_i = nullptr;}

			this_type & operator=(this_type const & rhs) {
				if (this == &rhs)
					return *this;
				this->_i = rhs.base();
				return *this;
			}
			inline reference operator*(void) const {return *this->_i;}
			inline pointer operator->(void) const {return this->_i;}
			inline reference operator[](difference_type index) const {return this->_i[index];}
			inline this_type &operator++(void) {this->_i++; return *this;}
			inline this_type operator++(int) {this_type tmp(*this); ++(this->_i); return tmp;}
			inline this_type &operator--(void) {this->_i--; return *this;}
			inline this_type operator--(int) {this_type tmp(*this); --(this->_i); return tmp;}
			inline this_type &operator+=(difference_type n) {this->_i += n; return *this;}
			inline this_type &operator-=(difference_type n) {this->_i -= n; return *this;}
			inline this_type operator+(difference_type n) const {this_type tmp(*this); tmp += n; return tmp;}
			inline this_type operator-(difference_type n) const {this_type tmp(*this); tmp -= n; return tmp;}

			inline pointer base(void) const {return this->_i;}
	};

	# define WRAP_TEMPLATE template < class Iter>
	# define TYPE_TEMPLATE wrap_iter<Iter>

	WRAP_TEMPLATE
	inline bool operator==(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return lhs.base() == rhs.base();
	}
	WRAP_TEMPLATE
	inline bool operator!=(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return !(lhs.base() == rhs.base());
	}
	WRAP_TEMPLATE
	inline bool operator>(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return lhs.base() > rhs.base();
	}
	WRAP_TEMPLATE
	inline bool operator<(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return lhs.base() < rhs.base();
	}
	WRAP_TEMPLATE
	inline bool operator>=(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return !(lhs.base() < rhs.base());
	}
	WRAP_TEMPLATE
	inline bool operator<=(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return !(lhs.base() > rhs.base());
	}
	WRAP_TEMPLATE
	inline typename TYPE_TEMPLATE::difference_type operator-(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return lhs.base() - rhs.base();
	}
	WRAP_TEMPLATE
	inline typename TYPE_TEMPLATE::difference_type operator+(TYPE_TEMPLATE const & lhs, TYPE_TEMPLATE const & rhs) {
		return lhs.base() + rhs.base();
	}
	WRAP_TEMPLATE
	inline TYPE_TEMPLATE operator+(typename TYPE_TEMPLATE::difference_type n, TYPE_TEMPLATE const & rhs) {
		rhs += n;
		return rhs;
	}
	WRAP_TEMPLATE
	inline TYPE_TEMPLATE operator-(typename TYPE_TEMPLATE::difference_type n, TYPE_TEMPLATE const & rhs) {
		rhs -= n;
		return rhs;
	}
}

#endif
