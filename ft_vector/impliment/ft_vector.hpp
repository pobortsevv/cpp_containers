#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

/* -------------------------------- Macroses -------------------------------- */
# define EMPTY 0
# define CHAR_SIZE 8
/* -------------------------------------------------------------------------- */

/* -------------------------------- Libaries -------------------------------- */
# include <memory>
# include <__debug>
# include "generics.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"

/* -------------------------------------------------------------------------- */

/* ------------------------------ FT Namespace ------------------------------ */
namespace ft {

	template <typename T, typename Allocator = std::allocator<T> >
	class vector 
	{
		private:
			typedef Allocator				allocator_type;
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
			explicit vector (const vector& x)
				: _begin(nullptr), _alloc(x._alloc), _cap(x._cap), _sz(x.sz)
			{
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
			virtual ~vector(void)
			{
				if (this->_begin == nullptr)
					return;
				for (size_type i = 0; i < this->_sz; i++)
					this->_alloc.destroy(this->_begin + i);
				this->_alloc.deallocate(this->_begin, this->_cap);
				this->_sz = 0;
				this->_cap = 0;
				this->_begin = nullptr;
			}

			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Iterators ------------------------------- */
			iterator	begin(void) {return iterator(this->_begin);}
			iterator	end(void) {return iterator(this->_begin + this->_sz);}
			const_iterator begin(void) const {return const_iterator(this->_begin);}
			const_iterator end(void) const {return const_iterator(this->_begin + this->_sz);}
			reverse_iterator	rbegin(void) 
			{
				if (this->_sz == 0)
					return reverse_iterator(iterator(this->_begin));
				return reverse_iterator(iterator(this->_begin + this->_sz - 1));
			}
			reverse_iterator	rend(void) 
			{
				if (this->_sz == 0)
					return reverse_iterator(iterator(this->_begin));
				return reverse_iterator(iterator(this->_begin - 1));
			}
			const_reverse_iterator	rbegin(void) const
			{
				if (this->_sz == 0)
					return const_reverse_iterator(const_iterator(this->_begin));
				return const_reverse_iterator(const_iterator(this->_begin + this->_sz - 1));
			}
			const_reverse_iterator	rend(void) const
			{
				if (this->_sz == 0)
					return const_reverse_iterator(const_iterator(this->_begin));
				return const_reverse_iterator(const_iterator(this->_begin - 1));
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Capacity -------------------------------- */
			size_type size(void) const {return this->_sz;}
			size_type max_size(void) const
			{
				size_type amax = this->_alloc.max_size();
				// size_type nmax = numeric_limits<size_type>::max() / 2;
				return amax;
			}
			size_type capacity(void) const {return this->_cap;}
			bool empty(void) const {return this->_sz == 0 ? true : false;}
			/* -------------------------------------------------------------------------- */
			/*                               Сделать resize                               */
			/* -------------------------------------------------------------------------- */
			void reserve(size_type n)
			{
				if (n > this->_cap)
				{
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
			reference operator[](size_type n)
			{
				_LIBCPP_ASSERT(n < this->_sz, "vector[] index out of bounds");
				return this->_begin[n];
			}
			const_reference operator[](size_type n) const
			{
				_LIBCPP_ASSERT(n < this->_sz, "vector[] index out of bounds");
				return this->_begin[n];
			}
			reference at(size_type n)
			{
				if (n >= this->_sz)
					_VSTD::__throw_out_of_range("vector");
				return this->_begin[n];
			}
			const_reference at(size_type n) const
			{
				if (n >= this->_sz)
					_VSTD::__throw_out_of_range("vector");
				return this->_begin[n];
			}
			reference front(void)
			{
				_LIBCPP_ASSERT(!empty(), "front() called for empty vector");
				return *this->_begin;
			}
			const_reference front(void) const
			{
				_LIBCPP_ASSERT(!empty(), "front() called for empty vector");
				return *this->_begin;
			}
			reference back(void)
			{
				_LIBCPP_ASSERT(!empty(), "back() called for empty vector");
				return *(this->_begin + (this->_sz) - 1);
			}
			const_reference back(void) const
			{
				_LIBCPP_ASSERT(!empty(), "back() called for empty vector");
				return *(this->_begin + (this->_sz) - 1);
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Modifiers ------------------------------- */
			void push_back(const value_type & val)
			{
				if (this->_sz < this->_cap)
				{
					this->_alloc.construct(this->_begin + size(), val);
					this->_sz++;	
				}
				else
				{
					pointer new_begin = this->_alloc.allocate(this->_cap ? this->_cap * 2 : 1);
					for(size_type i = 0; i < this->_cap; i++)
						this->_alloc.construct(new_begin + i, this->_begin[i]);
					this->_alloc.construct(new_begin + this->_cap, val);
					for(size_type i = 0; i < this->_sz; i++)
						this->_alloc.destroy(this->_begin + i);
					this->_alloc.deallocate(this->_begin, this->_cap);
					this->_cap = this->_cap ? this->_cap * 2 : 1; 
					this->_sz++;
					this->_begin = new_begin;
				}
			}
			void pop_back(void)
			{
				_LIBCPP_ASSERT(!empty(), "vector::pop_back called for empty vector");
				this->_alloc.destroy(this->_begin + this->_sz - 1);
				this->_sz--;
			}
			void swap(vector& x) 
			{
				ft::swap(this->_begin, x._begin);
				ft::swap(this->_alloc, x._alloc);
				ft::swap(this->_sz, x._sz);
				ft::swap(this->_cap, x._cap);
			}
			void clear(void)
			{
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
}
/* -------------------------------------------------------------------------- */

#endif
