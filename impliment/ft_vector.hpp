#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

/* -------------------------------- Macroses -------------------------------- */
# define EMPTY 0
# define CHAR_SIZE 8
/* -------------------------------------------------------------------------- */

/* -------------------------------- Headers --------------------------------- */
# include <memory>
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
				this->_begin = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_begin + i, val);
			}
			template <class InputIterator>
			explicit vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
				: _alloc(alloc), _cap(last - first), _sz(last - first) {
				difference_type diff = last - first;
				try
				{
					this->_begin = this->_alloc.allocate(diff);
				}
				catch(const std::exception& e)
				{
					this->~vector();
					std::__throw_out_of_range("vector");
				}
				for (difference_type i = 0; i < diff; i++)
					this->_alloc.construct(this->_begin + i, *(first + i));
			}
			explicit vector (const vector& x)
				: _begin(nullptr), _alloc(x._alloc), _cap(x._cap), _sz(x.sz) {
				try
				{
					this->_alloc.allocate(x._cap);
				}
				catch(std::exception & e)
				{
					std::cout << e.what() << std::endl;
					this->~vector();
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
				if (this->_sz < n) {
					if (n <= this->_cap) {
						for (size_type i = this->_sz; i < n; i++)
							this->_alloc.construct(this->_begin + i, val);
						this->_sz = n;
					} else {
						pointer new_begin = this->_alloc.allocate(n * 2);
						memmove(new_begin, this->_begin, sizeof(value_type) * this->_sz);
						for (size_type i = this->_sz; i < n; i++)
							this->_alloc.construct(new_begin + i, val);
						for (size_type i = 0; i < this->_sz; i++)
							this->_alloc.destroy(this->_begin + i);
						this->_alloc.deallocate(this->_begin, this->_cap);
						this->_cap = n * 2;
						this->_sz = n;
						this->_begin = new_begin;
					}
				}
				else if (this->_sz >= n) {
					for (size_type i = n; i < this->_sz; ++i)
						this->_alloc.destroy(this->_begin + i);
					this->_sz = n;
				}
			}
			void reserve(size_type n) {
				if (n > this->_cap) {
					pointer new_begin = this->_alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(new_begin + i, this->_begin[i]);
					for (size_type i = 0; i < this->_sz; i++)
						this->_alloc.destroy(this->_begin + i);
					this->_alloc.deallocate(this->_begin, this->_cap);
					this->_cap = n;
					this->_begin = new_begin;
				}
			}
			/* -------------------------------------------------------------------------- */

			/* ----------------------------- Element access ----------------------------- */
			reference operator[](size_type n) {
				_LIBCPP_ASSERT(n < this->_sz, "vector[] index out of bounds");
				return this->_begin[n];
			}
			const_reference operator[](size_type n) const {
				_LIBCPP_ASSERT(n < this->_sz, "vector[] index out of bounds");
				return this->_begin[n];
			}
			reference at(size_type n) {
				if (n >= this->_sz)
					std::__throw_out_of_range("vector");
				return this->_begin[n];
			}
			const_reference at(size_type n) const {
				if (n >= this->_sz)
					std::__throw_out_of_range("vector");
				return this->_begin[n];
			}
			reference front(void) {
				_LIBCPP_ASSERT(!empty(), "front() called for empty vector");
				return *this->_begin;
			}
			const_reference front(void) const {
				_LIBCPP_ASSERT(!empty(), "front() called for empty vector");
				return *this->_begin;
			}
			reference back(void) {
				_LIBCPP_ASSERT(!empty(), "back() called for empty vector");
				return *(this->_begin + (this->_sz) - 1);
			}
			const_reference back(void) const {
				_LIBCPP_ASSERT(!empty(), "back() called for empty vector");
				return *(this->_begin + (this->_sz) - 1);
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Modifiers ------------------------------- */
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, 
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) { // range
				difference_type diff = last - first;
				clear();
				reserve(last - first);
				std::copy(first, last, this->_begin);
				this->_sz = diff;
			}
			void assign(size_type n, const value_type& val) { // fill
				clear();
				reserve(n);
				insert(begin(), n, val);
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) {
				iterator pos = this->_begin + (position - begin());
				difference_type diff = last - first;
				if (this->_sz + diff < this->_cap) {
					if (pos.base() == (this->_begin + this->_sz))
						std::copy(first, last, end());
					else {
						vector tmp(pos, end());
						std::copy(tmp.begin(), tmp.end(), pos + diff);
						std::copy(first, last, pos);
					}
				} else {
					pointer new_begin = this->_alloc.allocate(this->_cap ? this->_cap * 2 : 1);
					size_type old_index = 0;
					size_type new_index = 0;
					while (new_index < this->_sz + diff) {
						if (this->_begin + new_index == position.base()) {
							for (size_type i = 0; i < size_type(diff); i++, new_index++)
								this->_alloc.construct(new_begin + new_index, *(first + i));
							continue;
						}
						this->_alloc.construct(new_begin + new_index, *(this->_begin + old_index));
						this->_alloc.destroy(this->_begin + old_index);
						new_index++;
						old_index++;
					}
					this->_alloc.deallocate(this->_begin, this->_cap);
					this->_cap = this->_cap ? this->_cap * 2 : 1; 
					this->_begin = new_begin;
				}
				this->_sz += diff;
			}
			void insert (iterator position, size_type n, const value_type& val) {
				ft::vector<value_type> newPart(n, val);
				this->insert(position, newPart.begin(), newPart.end());
			}
			iterator insert (iterator position, const value_type& val) {
				size_type before = position - this->begin();
				this->insert(position, 1, val);
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
				iterator pos = this->_begin + (position - begin());
				std::copy(position + 1, end(), pos);
				this->_sz--;
				return pos;
			}
			iterator erase(iterator first, iterator last) {
				iterator pos = this->_begin + (first - begin());
				difference_type diff = last - first;
				std::copy(last, this->_begin, pos);
				this->_sz -= diff;
				return pos;
			}
			void clear(void) {
				if (this->_begin == nullptr)
					return ;
				for (size_type i = 0; i < this->_sz; i++)
					this->_alloc.destroy(this->_begin + i);
				this->_alloc.deallocate(this->_begin, this->_cap);
				this->_begin = nullptr;
				this->_cap = 0;
				this->_sz = 0;
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Allocator ------------------------------- */
			allocator_type get_allocator(void) const {return this->_alloc;}
			/* -------------------------------------------------------------------------- */
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
