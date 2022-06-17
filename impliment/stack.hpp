#ifndef STACK_HPP
# define STACK_HPP

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
		private:
			container_type  cont;
			stack(const stack &ths);
        	stack & operator=(const stack &ths);
		public:
			/* ------------------------------ Constructors ------------------------------ */
			explicit stack(const container_type &container): cont(container) {}
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