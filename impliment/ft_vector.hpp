#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

/* -------------------------------- Macroses -------------------------------- */
# define EMPTY 0
# define CHAR_SIZE 8
/* -------------------------------------------------------------------------- */

/* -------------------------------- Headers --------------------------------- */
# include <memory>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <climits>
# include <__debug>
# include "utility.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
/* -------------------------------------------------------------------------- */

/* ------------------------------ FT Namespace ------------------------------ */
namespace ft {

	template <typename T, typename Alloc = std::allocator<T> >
	class vector {
		private:
			typedef Alloc									allocator_type;
		public:
			// Name requirements for c++ container:
			typedef T										value_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef	typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef wrap_iter<pointer>						iterator;
			typedef wrap_iter<const_pointer>				const_iterator;
			typedef reverse_wrap_iter<iterator>				reverse_iterator;
			typedef reverse_wrap_iter<const_iterator>		const_reverse_iterator;

			typedef std::size_t size_type;
			typedef signed int difference_type;

			pointer _begin;
			allocator_type 	_alloc;
			size_type _cap;
			size_type _sz;

			/* ------------------------------ Constructors ------------------------------ */
			explicit vector (const allocator_type & alloc = allocator_type()) 
				: _begin(nullptr), _alloc(alloc), _cap(EMPTY), _sz(EMPTY)
			{}
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _cap(n), _sz(n) {
					try {
						this->_begin = this->_alloc.allocate(n);
					} catch(std::exception & e) {
						this->~vector();
						throw vector::LengthError();
					}

					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(this->_begin + i, val);
			}
			template <class InputIterator>
			explicit vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
				: _alloc(alloc), _cap(last - first), _sz(last - first) {
				difference_type diff = last - first;
				try {
					this->_begin = this->_alloc.allocate(diff);
				} catch(const std::exception& e) {
					this->~vector();
					throw vector::LengthError();
				}
				for (difference_type i = 0; i < diff; i++)
					this->_alloc.construct(this->_begin + i, *(first + i));
			}
			explicit vector (const vector& x)
				: _begin(nullptr), _alloc(x._alloc), _cap(x._cap), _sz(x._sz) {
				try {
					this->_begin = this->_alloc.allocate(x._cap);
				} catch(std::exception & e) {
					this->~vector();
					throw vector::LengthError();
				}
				for (size_type i = 0; i < x._sz; i++)
					this->_alloc.construct(this->_begin + i, x[i]);
			}
			virtual ~vector(void) {
				if (this->_begin == nullptr)
					return;
				for (size_type i = 0; i < this->_sz; i++)
					this->_alloc.destroy(this->_begin + i);
				this->_alloc.deallocate(this->_begin, this->_cap);
				this->_sz = 0;
				this->_cap = 0;
				this->_begin = nullptr;
			}
			vector const & operator=(vector const & rhs) {
				if (this == &rhs)
					return *this;
				this->~vector();
				this->_alloc = rhs.get_allocator();
				this->_begin = this->_alloc.allocate(rhs.capacity());
				for (size_type i = 0; i < rhs.size(); i++)
					this->_alloc.construct(this->_begin + i, rhs[i]);
				this->_cap = rhs.capacity();
				this->_sz = rhs.size();
				return *this;
			}

			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Iterators ------------------------------- */
			iterator	begin(void) {return iterator(this->_begin);}
			iterator	end(void) {return iterator(this->_begin + this->_sz);}
			const_iterator begin(void) const {return const_iterator(this->_begin);}
			const_iterator end(void) const {return const_iterator(this->_begin + this->_sz);}
			reverse_iterator	rbegin(void) {
				if (this->_sz == 0)
					return reverse_iterator(iterator(this->_begin));
				return reverse_iterator(iterator(this->_begin + this->_sz - 1));
			}
			reverse_iterator	rend(void) {
				if (this->_sz == 0)
					return reverse_iterator(iterator(this->_begin));
				return reverse_iterator(iterator(this->_begin - 1));
			}
			const_reverse_iterator	rbegin(void) const {
				if (this->_sz == 0)
					return const_reverse_iterator(const_iterator(this->_begin));
				return const_reverse_iterator(const_iterator(this->_begin + this->_sz - 1));
			}
			const_reverse_iterator	rend(void) const {
				if (this->_sz == 0)
					return const_reverse_iterator(const_iterator(this->_begin));
				return const_reverse_iterator(const_iterator(this->_begin - 1));
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Capacity -------------------------------- */
			size_type size(void) const {return this->_sz;}
			size_type max_size(void) const {return this->_alloc.max_size();}
			size_type capacity(void) const {return this->_cap;}
			bool empty(void) const {return this->_sz == 0 ? true : false;}
			void resize(size_type n, value_type val = value_type()) {
				if (n <= this->_sz)
					erase(iterator(this->_begin + n), end());
				else
					insert(iterator(this->_begin + this->_sz), n - this->_sz , val);
			}
			void reserve(size_type n) {
				if (n > this->_cap) {
					pointer new_begin = this->_alloc.allocate(n);
					
					memmove(new_begin,this->_begin, sizeof(value_type) * this->_sz);
					if (this->_begin != 0) {
						this->_alloc.deallocate(this->_begin, this->_sz);
					}
					this->_cap = n;
					this->_begin = new_begin;
				}
			}
			/* -------------------------------------------------------------------------- */

			/* ----------------------------- Element access ----------------------------- */
			reference operator[](size_type n) {
				return this->_begin[n];
			}
			const_reference operator[](size_type n) const {
				return this->_begin[n];
			}
			reference at(size_type n) {
				if (n >= this->_sz)
					throw vector::Out_of_range();
				return this->_begin[n];
			}
			const_reference at(size_type n) const {
				if (n >= this->_sz)
					throw vector::Out_of_range();
				return this->_begin[n];
			}
			reference front(void) {
				return *this->_begin;
			}
			const_reference front(void) const {
				return *this->_begin;
			}
			reference back(void) {
				return *(this->_begin + (this->_sz - 1));
			}
			const_reference back(void) const {
				return *(this->_begin + (this->_sz - 1));
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Modifiers ------------------------------- */
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, 
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) { // range
				difference_type diff = last - first;

				if (diff < 0) {
					this->~vector();
					throw vector::LengthError();
				}

				vector save(first, last);

				clear();
				reserve(diff);
				insert(begin(), save.begin(), save.end());
				this->_sz = diff;
			}
			void assign(size_type n, const value_type& val) { // fill
				value_type save(val);
				clear();
				reserve(n);
				insert(begin(), n, save);
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, 
			typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) {
				difference_type diff = last - first;
				difference_type before = position - begin();

				// Incorrect iterators as arguments
				if (diff <= 0) {
					return;
				}

				// if true - add new elements(without allocation)
				if (this->_cap >= this->_sz + diff) {
					while (first != last) {
						insert(position, *first);
						first++;
						position++;
					}
					return;
				}

				// else - allocate new memory
				size_t new_cap = this->_cap * 2;
				if (this->_sz + diff > new_cap) {
					new_cap = this->_sz + diff;
				}

				pointer new_begin = this->_alloc.allocate(new_cap);

				memmove(new_begin, this->_begin, sizeof(value_type) * before);
				iterator new_position(new_begin + before);

				for (; first != last; ++first, (void) ++new_position)
					*new_position = *first;
				memmove(new_begin + before + diff, this->_begin + before, sizeof(value_type) * (this->_sz - before));
				if (this->_begin != 0) {
					this->_alloc.deallocate(this->_begin, this->_cap);
				}

				this->_sz += diff;
				this->_begin = new_begin;
				this->_cap = new_cap;
			}
			iterator insert (iterator position, size_type n, const value_type& val) {
				size_type before = position - begin();

				if (this->_cap >= this->_sz + n) {
					size_type last = (this->_sz == 0) ? 0 : this->_sz - 1;

					for(size_type i = before; i < this->_sz; i++, last--)
						memmove(this->_begin + last + n, this->_begin + last, sizeof(value_type));
					
					for(size_type i = 0; i < n; i++) 
						this->_alloc.construct(this->_begin + before + i, val);
					this->_sz += n;
					return iterator(this->_begin + before);
				}
				size_type new_cap = this->_cap * 2;
				
				if (new_cap < this->_sz + n)
					new_cap = this->_sz + n;
				difference_type save_pos(position - begin());

				reserve(new_cap);
				insert(iterator(this->_begin + save_pos), n, val);
				return iterator(this->_begin + before);
			}
			iterator insert (iterator position, const value_type& val) {
				difference_type before = position - begin();
				insert(position, 1, val);
				return iterator(this->_begin + before);
			}
			void push_back(const value_type & val) {insert(end(), val);}
			void pop_back(void) {
				_LIBCPP_ASSERT(!empty(), "vector::pop_back called for empty vector");
				this->_alloc.destroy(this->_begin + this->_sz - 1);
				this->_sz--;
			}
			void swap(vector& x) {
				ft::swap(this->_begin, x._begin);
				ft::swap(this->_alloc, x._alloc);
				ft::swap(this->_sz, x._sz);
				ft::swap(this->_cap, x._cap);
			}
			iterator erase(iterator position) {
				difference_type index = position - begin();

				if (this->_sz == 0)
					return iterator(this->_begin + index);

				this->_alloc.destroy(this->_begin + index);
				this->_sz--;
				std::memmove(this->_begin + index, this->_begin + index + 1, sizeof(value_type) * (this->_sz - index));
				return iterator(this->_begin + index);
			}
			iterator erase(iterator first, iterator last) {
				size_type start = first - begin();

				while (first != last) {
					erase(first);
					--last;
				}
				return iterator(this->_begin + start);
			}
			void clear(void) {
				if (this->_begin == nullptr)
					return ;
				for (size_type i = 0; i < this->_sz; i++)
					this->_alloc.destroy(this->_begin + i);
				this->_sz = 0;
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Allocator ------------------------------- */
			allocator_type get_allocator(void) const {return this->_alloc;}
			/* -------------------------------------------------------------------------- */

		class LengthError: public std::exception {
			const char* what() const throw() {
				return "vector";
			}
		};

		class Out_of_range : public std::exception {
			const char*  what() const throw() {
				return "vector";
			}
		};
	};

	template <class T, class Alloc>
	inline bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

	template <class T, class Alloc>
	inline bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return !(rhs == lhs);}

	template <class T, class Alloc>
	inline bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

	template <class T, class Alloc>
	inline bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return rhs < lhs;}

	template <class T, class Alloc>
	inline bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return !(rhs < lhs);}

	template <class T, class Alloc>
	inline bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs < rhs);}
}
/* -------------------------------------------------------------------------- */

#endif
