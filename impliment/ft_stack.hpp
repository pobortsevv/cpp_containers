#ifndef FT_STACK_HPP
# define FT_STACK_HPP

/* --------------------------------- Headers -------------------------------- */
# include "ft_vector.hpp"
/* -------------------------------------------------------------------------- */

namespace ft {
	template <typename T, class Container = ft::vector<T>, typename Alloc = std::allocator<T> >
	class stack {
		public:
			typedef T               value_type;
			typedef Container       container_type;
			typedef size_t          size_type;

			/* ------------------------------ Constructors ------------------------------ */
			explicit stack(const container_type &container = container_type()): cont(container) {}
			stack(const stack &ths): cont(ths.cont) {}
			~stack() {}
			/* -------------------------------------------------------------------------- */

			/* ---------------------------- Member functions ---------------------------- */
			bool empty() const { return cont.empty(); }

			size_t size() const { return cont.size(); }

			void push(const value_type &val) { cont.push_back(val); }

			value_type &top() { return cont.back(); }

			const value_type &top() const { return cont.back(); }

			void pop() { cont.pop_back(); }
			/* -------------------------------------------------------------------------- */
		private:
			container_type  cont;
	};

	/* ------------------------------- Opertators ------------------------------- */
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs == rhs; }

    template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs != rhs; }

    template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs < rhs; }

    template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs  <= rhs; }

    template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs > rhs; }

    template <class T, class Container, class Alloc>
	bool operator>= (const stack<T,Container, Alloc>& lhs, const stack<T,Container, Alloc>& rhs) { return lhs >= rhs; }
	/* -------------------------------------------------------------------------- */
}
#endif
