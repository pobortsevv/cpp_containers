#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

/* -------------------------------- Macroses -------------------------------- */
# define EMPTY 0
/* -------------------------------------------------------------------------- */

/* -------------------------------- Libaries -------------------------------- */
# include <memory>

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
			typedef T			value_type;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef	typename allocator_type::pointer	pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			/* ---------- Разобрать как работают итераторы и как их реализовать --------- */
			// typedef pointer		iterator;
			// typedef const_pointer const_iterator;
			/* -------------------------------------------------------------------------- */

			typedef size_t size_type;
			typedef signed int difference_type;

			pointer _begin;
			allocator_type 	_alloc;
			size_type _cap;
			size_type _sz;

			/* ------------------------------ Constructors ------------------------------ */
			explicit vector (const allocator_type & alloc = allocator_type()) 
				: _begin(nullptr), _alloc(alloc), _cap(EMPTY), _sz(EMPTY)
			{}

			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Capacity -------------------------------- */
			size_type size(void) const {return static_cast<size_type>(this->_sz);}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Modifiers ------------------------------- */
			void push_back (const value_type & val)
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
					for(size_type i = 0; i < this->_cap; i++)
						this->_alloc.destroy(this->_begin + i);
					this->_alloc.deallocate(this->_begin, this->_cap);
					this->_cap = this->_cap ? this->_cap * 2 : 1; 
					this->_sz++;
					this->_begin = new_begin;
				}
			}
			/* -------------------------------------------------------------------------- */

	};
}
/* -------------------------------------------------------------------------- */

#endif
