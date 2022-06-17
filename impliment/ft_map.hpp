#ifndef FT_MAP_HPP
# define FT_MAP_HPP

/* -------------------------------- Macroses -------------------------------- */

/* -------------------------------------------------------------------------- */

/* --------------------------------- Headers -------------------------------- */
# include <memory>
# include <functional>
# include "red_black_tree.hpp"
# include "utility.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
/* -------------------------------------------------------------------------- */

/* ------------------------------ FT Namespace ------------------------------ */
namespace ft {
	template < typename Key, 
	typename T,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<pair<const Key,T> > >
	class map {
		private:
			typedef Alloc				allocator_type;
		private:
			// Name requirements for c++ container:
			typedef T										value_type;
			typedef	T&										reference;
			typedef const T&								const_reference;
			typedef Compare         						key_compare;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef wrap_iter<pointer>						iterator;
			typedef wrap_iter<const_pointer>				const_iterator;
			typedef reverse_wrap_iter<iterator>				reverse_iterator;
			typedef reverse_wrap_iter<const_iterator>		const_reverse_iterator;

			typedef std::size_t size_type;
			typedef signed int difference_type;

		// This is a function object that compares objects of type std::map::value_type (key-value pairs)
		// by comparing of the first components of the pairs.
		class value_compare {
		private:
			Compare comp;
		public:
			typedef typename ft::pair<Key, T> value_type;

			explicit value_compare (Compare const & c) : comp(c) {}
			virtual ~value_compare() {}
			bool operator() (const value_type &x, const value_type &y) const {
				return (comp(x.first, y.first));
			}
			bool operator() (const value_type &x, const key_type &y) const {
				return (comp(x.first, y));
			}
			bool operator() (const key_type &x, const value_type &y) const {
				return (comp(x, y.first));
			}
		};
		
		private:
            LLRB<value_type, value_compare, allocator_type>        _map;

		public:
			typedef bool            result_type;
			typedef value_type      first_argument_type;
			typedef value_type      second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {
				return cmp(x.first, y.first);
			}

			/* ------------------------------ Constructors ------------------------------ */
			map(const key_compare & cmp, const allocator_type& alloc): _map(LLRB<value_type, value_compare, allocator_type>(value_compare(cmp), alloc)) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp,
                const allocator_type &alloc,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *):
                _map(RBTree<value_type, value_compare, allocator_type>(first, last, value_compare(comp), alloc)) {}

			map(const map &x,const key_compare& comp, const allocator_type& alloc): _map(RBTree<value_type, value_compare, allocator_type>((x.begin()), (x.end()), value_compare(comp), alloc)) {}

			~map() {}
			/* -------------------------------------------------------------------------- */

			/* ----------------------------- Element access ----------------------------- */
			reference operator[](const key_type &key) {
				iterator    it;
				it = (find(key));

				if (it == end()) {
					_map.insert_map(ft::make_pair(key, value_type()), value_compare(key_comp()));
					it = find(key);
				}

				return it->second;
			}
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Iterators ------------------------------- */
			iterator begin() { return (_map.begin()); }

			const_iterator begin() const { return (_map.begin()); }

			iterator end() { return (_map.end()); }

			const_iterator end() const { return (_map.end()); }

			reverse_iterator  rbegin() { return ((_map.rbegin())); }

			const_reverse_iterator rbegin() const { return ((_map.rbegin())); }

			reverse_iterator rend() { return ((_map.rend())); }

			const_reverse_iterator rend() const { return ((_map.rend())); }

			bool empty() const { return (_map.empty()); }

			size_t size() const { return (_map.size()); }

			size_t max_size() const { return (_map.max_size()); }
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Capacity -------------------------------- */
			bool empty() const { return (_map.empty()); }

			size_t size() const { return (_map.size()); }

			size_t max_size() const { return (_map.max_size()); }
			/* -------------------------------------------------------------------------- */

			/* -------------------------------- Modifiers ------------------------------- */
			pair<iterator, bool> insert(const value_type &val, const key_compare &comp, const allocator_type &alloc) {
				if (&alloc == &alloc) {};
				if (_map.insert_map(val, value_compare(comp))) {
					iterator it = _map.lower_bound(val,value_compare(comp));
					return (ft::make_pair(it, true));
				} else {
				iterator it = _map.lower_bound(val,value_compare(comp));

				return (ft::make_pair(it, false));
				}
			}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last, const key_compare &comp,
													typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *)  {
				_map.insert(first, last, value_compare(comp));
			}

            void erase(iterator position, const key_compare& comp) {
                _map.erase(position, value_compare(comp));
			}

			size_t erase(const key_type &k, const key_compare &cmp) {
				iterator it = find(k);
				if (it == end())
					return 0;
				_map.erase(it, value_comp(cmp));
				return 1;
			}

			void erase(iterator first, iterator last, const key_compare &comp) {
				_map.erase(first, last, value_compare(comp));
			}

			void swap(map &xp) {
				_map.swap(xp._map);
			}

			void swap (map& left, map& right) {
				left.swap(right);
			}

			void clear(const key_compare& comp) {
				_map.clear(value_compare(comp));
			}

			key_compare key_comp(const key_compare& comp) const {
				return comp;
			}

			value_compare value_comp(const key_compare &comp) const {
				return value_compare(comp);
			}

			iterator find(const key_type &k, const key_compare &comp) {
				return _map.find_map(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			const_iterator find(const key_type &k, const key_compare &comp) const {
				return _map.find_map(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			size_t count(const key_type &k, const key_compare &comp) const {
				return _map.count(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			iterator lower_bound(const key_type &k, const key_compare &comp) {
				return _map.lower_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			const_iterator lower_bound(const key_type &k, const key_compare &comp) const {
				return _map.lower_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			iterator upper_bound(const key_type &k, const key_compare &comp) {
				return _map.upper_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			const_iterator upper_bound(const key_type &k, const key_compare &comp) const {
				return _map.upper_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
			}

			pair<iterator, iterator> equal_range(const key_type &k, const key_compare& comp) const {
				return make_pair(_map.lower_bound(ft::make_pair(k, mapped_type()), value_compare(comp)), _map.upper_bound(ft::make_pair(k, mapped_type()), value_compare(comp)));
			}

			allocator_type get_allocator(const allocator_type &alloc) const {
				return alloc;
			}
			/* -------------------------------------------------------------------------- */
	};

	/* -------------------------------- Operators ------------------------------- */
	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		if (lhs.size() == 0)
			return true;
		typename map<Key, T, Compare, Alloc>::const_iterator itL = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator itR = rhs.begin();
		for (size_t i=0; i<lhs.size(); ++i, ++itL, ++itR) {
			if ((itL->first != itR->first) || (itL->second != itR->second))
				return false;
		}
		return true;
	}

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(lhs == rhs); }

    template <class Key, class T, class Compare, class Alloc> bool operator<  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        size_t left_size = lhs.size();
        size_t right_size = rhs.size();
        if (left_size == 0 && right_size != 0)
            return true;
        else if (left_size == 0)
            return false;
        else if (right_size == 0)
        	return false;

        typename map<Key, T, Compare, Alloc>::const_iterator itl = lhs.begin();
        typename map<Key, T, Compare, Alloc>::const_iterator itr = rhs.begin();

        for (size_t i = 0; i < left_size && i < right_size; ++i) {
            if (itl->first > itr->first || itl->second > itr->second)
                return false;
		}

        if (left_size <= right_size)
            return true;
        else
            return false;
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return ((lhs < rhs) || (lhs == rhs));
	}

    template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return (!(lhs < rhs) && !(lhs == rhs));
	}

    template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return ((lhs > rhs) || (lhs == rhs));
	}
	/* -------------------------------------------------------------------------- */
}
/* -------------------------------------------------------------------------- */

#endif