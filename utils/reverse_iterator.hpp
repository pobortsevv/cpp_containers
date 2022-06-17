#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "traits.hpp"

namespace ft {

	template < class Iter>
	class reverse_wrap_iter {
		public:
			typedef Iter														iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category 	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type        	value_type;
			typedef typename iterator_traits<iterator_type>::difference_type   	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer           	pointer;
			typedef typename iterator_traits<iterator_type>::reference         	reference;
			typedef reverse_wrap_iter<iterator_type> this_type;
		private:
			iterator_type _i;
		public:
			reverse_wrap_iter(void) : _i(0) {} // default
			reverse_wrap_iter(iterator_type x) : _i(x) {} // pointer
			reverse_wrap_iter(this_type const &x) : _i(x.base()) {} // copy
			virtual ~reverse_wrap_iter(void) {}

			this_type & operator=(this_type const & rhs) {
				if (this == &rhs)
					return *this;
				this->_i = rhs.base();
				return *this;
			}
			inline reference operator*(void) const {return *this->_i;}
			inline pointer operator->(void) const {return this->_i.base();}
			inline reference operator[](difference_type index) const {return *(*this->_i[index]);}
			inline this_type &operator++(void) {--this->_i; return *this;}
			inline this_type operator++(int) {this_type tmp(*this); --(this->_i); return tmp;}
			inline this_type &operator--(void) {++this->_i; return *this;}
			inline this_type operator--(int) {this_type tmp(*this); ++(this->_i); return tmp;}
			inline this_type &operator+=(difference_type n) {this->_i -= n; return *this;}
			inline this_type &operator-=(difference_type n) {this->_i += n; return *this;}
			inline this_type operator+(difference_type n) const {this_type tmp(*this); tmp -= n; return tmp;}
			inline this_type operator-(difference_type n) const {this_type tmp(*this); tmp += n; return tmp;}

			inline iterator_type base(void) const {return this->_i;}
	};

	# define REVERSE_WRAP_TEMPLATE template < class Iter>
	# define REVERSE_TYPE_TEMPLATE reverse_wrap_iter<Iter>

	REVERSE_WRAP_TEMPLATE
	inline bool operator==(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return lhs.base() == rhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline bool operator!=(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return lhs.base() != rhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline bool operator>(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return lhs.base() < rhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline bool operator<(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return lhs.base() > rhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline bool operator>=(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return lhs.base() <= rhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline bool operator<=(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return lhs.base() >= rhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline typename REVERSE_TYPE_TEMPLATE::difference_type operator-(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return rhs.base() - lhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline typename REVERSE_TYPE_TEMPLATE::difference_type operator+(REVERSE_TYPE_TEMPLATE const & lhs, REVERSE_TYPE_TEMPLATE const & rhs) {
		return rhs.base() + lhs.base();
	}
	REVERSE_WRAP_TEMPLATE
	inline REVERSE_TYPE_TEMPLATE operator+(typename REVERSE_TYPE_TEMPLATE::difference_type n, REVERSE_TYPE_TEMPLATE const & rhs) {
		rhs -= n;
		return rhs;
	}
	REVERSE_WRAP_TEMPLATE
	inline REVERSE_TYPE_TEMPLATE operator-(typename REVERSE_TYPE_TEMPLATE::difference_type n, REVERSE_TYPE_TEMPLATE const & rhs) {
		rhs += n;
		return rhs;
	}
}

#endif
