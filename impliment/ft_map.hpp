#ifndef FT_MAP_HPP
# define FT_MAP_HPP

/* ------------------------------- Explanation ------------------------------ */
// This is implementation of Left-Leaning-Red-Black tree.
// Experimental studies have not been able to distinguish these algorithms
// from optimal.
// Unlike hashing, they support ordered operations such as 
// select, rank, and range search.
// Specifically, in a left-leaning red-black 2-3 tree built from N random keys:
// 	• A random successful search examines lg N – 0.5 nodes.
//	• The average tree height is about 2 ln N (!)
//	• The average size of left subtree exhibits log-oscillating behavior.
// This code is based on com- bining three ideas:
//	1) Use a recursive implementation.
//	2) Require that all 3-nodes lean left.
//	3) Perform rotations on the way up the tree (after the recursive calls).
// Most published implementations involve code laden
// with cases that are nearly identical for right and left.
// This code show that the number of cases can be substantially reduced by:
// • requiring that 3-nodes always lean to the left (and that 4-nodes are balanced)
// • doing rotations after the recursive calls, on the way up the tree.
// The rotate-on-the-way up strategy simplifies the code (and our understanding of it)
// by combining various cases in a natural way.
// 
// This LLRB tree model is described by Robert Sedgewick.
/* -------------------------------------------------------------------------- */

/* -------------------------------- Macroses -------------------------------- */
# define RED 1
# define BLACK 0
/* -------------------------------------------------------------------------- */

/* --------------------------------- Headers -------------------------------- */
# include <bitset>
# include "utility.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <iomanip>
/* -------------------------------------------------------------------------- */

namespace ft {
	template<	class Key,
				class T,
				class Compare = ft::less<Key>,
				class Alloc = std::allocator<std::pair<const Key,T> > 
			>
	class map {
		/* ------------------------------ Member types ------------------------------ */
	public:
		typedef Key 										key_type;
		typedef T 											mapped_type;
		typedef std::pair<const Key, T> 					value_type;
		typedef Compare 									key_compare;
		typedef Alloc 										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef ptrdiff_t 									difference_type;
		typedef size_t 										size_type;

		class value_compare : public std::binary_function < value_type, value_type, bool > {
		public:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			bool operator() (const value_type& node, const value_type& y) const { return comp(node.first, y.first); }
		};
		/* -------------------------------------------------------------------------- */

	protected:
		/* -------------------------- Inside the container -------------------------- */
		static const bool black = false;
		static const bool red = true;

		struct _tNode {
			struct _tNode	*_left;
			struct _tNode 	*_right;
			struct _tNode 	*_parent;
			bool			_color;
			value_type 		*_data;
		};

		_tNode *_root;
		_tNode *_postLastNode;
		_tNode *_preFirstNode;
		size_type _size;

		typedef typename Alloc::template rebind<_tNode>::other Alloc_rebind;
		Alloc_rebind _allocNode;
		Alloc _allocData;
		Compare _comp;
		/* -------------------------------------------------------------------------- */
	public:
		/* -------------------------------- Iterators ------------------------------- */
		class const_iterator;
		class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_tNode 	*_data;

		public:
			/* ------------------------- Internal Help Functions ------------------------ */
			iterator() : _data(nullptr) {};
			~iterator() {}
			explicit iterator(_tNode *data) : _data(data) {}
			iterator(iterator const &src) { *this = src; }
			iterator &operator=(const iterator &rhs) { if (this != &rhs) { _data = rhs._data; } return *this; }

			bool operator==(iterator const &rhs) const { return(this->_data == rhs._data); }
			bool operator!=(iterator const &rhs) const { return(this->_data != rhs._data); }
			bool operator==(const_iterator const &rhs) const { return(this->_data == rhs.getData()); }
			bool operator!=(const_iterator const &rhs) const { return(this->_data != rhs.getData()); }

			value_type &operator* () const { return *_data->_data; }
			value_type *operator->() const { return  _data->_data; }

			iterator &operator++() { _data = _goToNext(_data); return *this; }
			iterator &operator--() { _data = _goToPrev(_data); return *this; }
			iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
			iterator operator--(int) { iterator tmp(*this); operator--(); return tmp; }

			_tNode *getData() const { return _data; }
			/* -------------------------------------------------------------------------- */
		};

		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_tNode 	*_data;

		public:
			const_iterator() : _data(nullptr) {};
			~const_iterator() {}
			explicit const_iterator(_tNode *data) : _data(data) {}
			const_iterator(const_iterator const &src) { *this = src; }
			const_iterator(iterator const &src) { *this = src; }
			const_iterator &operator=(const const_iterator &rhs) { if (this != &rhs) { _data = rhs._data; } return *this; }
			const_iterator &operator=(const iterator &rhs) { if (*this != rhs) { _data = rhs.getData(); } return *this; }

			bool operator==(const_iterator const &rhs) const { return(this->_data == rhs._data); }
			bool operator!=(const_iterator const &rhs) const { return(this->_data != rhs._data); }
			bool operator==(iterator const &rhs) const { return(this->_data == rhs.getData()); }
			bool operator!=(iterator const &rhs) const { return(this->_data != rhs.getData()); }

			value_type &operator* () const { return *_data->_data; }
			value_type *operator->() const { return  _data->_data; }

			const_iterator &operator++() { _data = _goToNext(_data); return *this; }
			const_iterator &operator--() { _data = _goToPrev(_data); return *this; }
			const_iterator operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
			const_iterator operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }

			_tNode *getData() const { return _data; }
			/* -------------------------------------------------------------------------- */
		};

		class const_reverse_iterator;
		class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_tNode 	*_data;

		public:
			/* ------------------------- Internal Help Functions ------------------------ */
			reverse_iterator() : _data(nullptr) {};
			~reverse_iterator() {}
			explicit reverse_iterator(_tNode *data) : _data(data) {}
			reverse_iterator(reverse_iterator const &src) { *this = src; }
			reverse_iterator &operator=(const reverse_iterator &rhs) { if (this != &rhs) { _data = rhs._data; } return *this; }

			bool operator==(reverse_iterator const &rhs) const { return(this->_data == rhs._data); }
			bool operator!=(reverse_iterator const &rhs) const { return(this->_data != rhs._data); }
			bool operator==(const_reverse_iterator const &rhs) const { return(this->_data == rhs.getData()); }
			bool operator!=(const_reverse_iterator const &rhs) const { return(this->_data != rhs.getData()); }

			value_type &operator* () const { return *_data->_data; }
			value_type *operator->() const { return  _data->_data; }

			reverse_iterator &operator++() { _data = _goToPrev(_data); return *this; }
			reverse_iterator &operator--() { _data = _goToNext(_data); return *this; }
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); operator++(); return tmp; }
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); operator--(); return tmp; }

			_tNode *getData() const { return _data; }
			/* -------------------------------------------------------------------------- */
		};

		class const_reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_tNode 	*_data;

		public:
			/* ------------------------- Internal Help Functions ------------------------ */
			const_reverse_iterator() : _data(nullptr) {};
			~const_reverse_iterator() {}
			explicit const_reverse_iterator(_tNode *data) : _data(data) {}
			const_reverse_iterator(const_reverse_iterator const &src) { *this = src; }
			const_reverse_iterator(reverse_iterator const &src) { *this = src; }
			const_reverse_iterator &operator=(const const_reverse_iterator &rhs) { if (this != &rhs) { _data = rhs._data; } return *this; }
			const_reverse_iterator &operator=(const reverse_iterator &rhs) { if (*this != rhs) { _data = rhs.getData(); } return *this; }

			bool operator==(const_reverse_iterator const &rhs) const { return(this->_data == rhs._data); }
			bool operator!=(const_reverse_iterator const &rhs) const { return(this->_data != rhs._data); }
			bool operator==(reverse_iterator const &rhs) const { return(this->_data == rhs.getData()); }
			bool operator!=(reverse_iterator const &rhs) const { return(this->_data != rhs.getData()); }

			value_type &operator* () const { return *_data->_data; }
			value_type *operator->() const { return  _data->_data; }

			const_reverse_iterator &operator++() { _data = _goToPrev(_data); return *this; }
			const_reverse_iterator &operator--() { _data = _goToNext(_data); return *this; }
			const_reverse_iterator operator++(int) { const_reverse_iterator tmp(*this); operator++(); return tmp; }
			const_reverse_iterator operator--(int) { const_reverse_iterator tmp(*this); operator--(); return tmp; }

			_tNode *getData() const { return _data; }
			/* -------------------------------------------------------------------------- */
		};

	protected:
		/* ------------------------- Internal Help Functions ------------------------ */
		static _tNode *_minimum(_tNode *_node) {
			while (_node->_left)
				_node = _node->_left;
			return _node;
		}

		static _tNode *_maximum(_tNode *_node) {
			while(_node->_right)
				_node = _node->_right;
			return _node;
		}

		static _tNode *_goToNext(_tNode *_node) {
			if (_node->_right)
				return _minimum(_node->_right);
			if (_node->_parent && _node->_parent->_left == _node)
				return _node->_parent;
			_tNode *tmp = _node;
			while (tmp->_parent && tmp->_parent->_right == tmp)
				tmp = tmp->_parent;
			if (!tmp->_parent)
				return _node->_right;
			return tmp->_parent;
		}

		static _tNode *_goToPrev(_tNode *_node) {
			if (_node->_left)
				return _maximum(_node->_left);
			if (_node->_parent && _node->_parent->_right == _node)
				return _node->_parent;
			_tNode *tmp = _node;
			while (tmp->_parent && tmp->_parent->_left == tmp)
				tmp = tmp->_parent;
			if (!tmp->_parent)
				return _node->_left;
			return tmp->_parent;
		}

		void _changeNodes(_tNode *node, _tNode *y){
			if (_root != node) {
				if (node == node->_parent->_right)
					node->_parent->_right = y;
				else
					node->_parent->_left = y;
			}
			else
				_root = y;
			y->_parent = node->_parent;
			y->_left = node->_left;
			y->_right = node->_right;
			if (node->_left)
				node->_left->_parent = y;
			if (node->_right)
				node->_right->_parent = y;
			y->_color = node->_color;
		};

		void _deleteTheoreticalBinds() {
			_tNode *tmp = _root;
			if (tmp) {
				while (tmp->_right != _postLastNode)
					tmp = tmp->_right;
				tmp->_right = nullptr;
			}

			tmp = _root;
			if (tmp) {
				while (tmp->_left != _preFirstNode)
					tmp = tmp->_left;
				tmp->_left = nullptr;
			}
		}

		void _addTheoreticalBinds() {
			_tNode *tmp = _root;
			if (!tmp) {
				_preFirstNode->_parent = _postLastNode;
				_postLastNode->_parent = _preFirstNode;
				return ;
			}
			while (tmp->_right)
				tmp = tmp->_right;
			tmp->_right = _postLastNode;
			_postLastNode->_parent = tmp;

			tmp = _root;
			while (tmp->_left)
				tmp = tmp->_left;
			tmp->_left = _preFirstNode;
			_preFirstNode->_parent = tmp;
		}

		void _createTheoreticalNodes() {
			_tNode *postNode;
			postNode = _allocNode.allocate(1);
			_allocNode.construct(postNode);
			postNode->_parent = nullptr;
			postNode->_left = nullptr;
			postNode->_right = nullptr;
			postNode->_color = black;
			postNode->_data = _allocData.allocate(1);
			_allocData.construct(postNode->_data);
			_postLastNode = postNode;

			_tNode *preNode;
			preNode = _allocNode.allocate(1);
			_allocNode.construct(preNode);
			preNode->_parent = nullptr;
			preNode->_left = nullptr;
			preNode->_right = nullptr;
			preNode->_color = black;
			preNode->_data = _allocData.allocate(1);
			_allocData.construct(preNode->_data);
			_preFirstNode = preNode;

			_preFirstNode->_parent = _postLastNode;
			_postLastNode->_parent = _preFirstNode;
		}

		_tNode *_createNode(const value_type& val, _tNode *parent) {
			_tNode *node;
			node = _allocNode.allocate(1);
			_allocNode.construct(node);
			node->_parent = parent;
			node->_left = nullptr;
			node->_right = nullptr;
			node->_color = red;
			node->_data = _allocData.allocate(1);
			_allocData.construct(node->_data, val);
			return node;
		}

		void _insertNodeInTree(_tNode *parent, _tNode *newNode) {
			if(parent) {
				if (newNode->_data->first < parent->_data->first)
					parent->_left = newNode;
				else
					parent->_right = newNode;
			} else {
				_root = newNode;
			}
		};

		void _rotateLeft(_tNode *node) {
			_tNode *y = node->_right;

			/* establish node->_right link */
			node->_right = y->_left;
			if (y->_left != nullptr) y->_left->_parent = node;

			/* establish y->_parent link */
			if (y != nullptr) y->_parent = node->_parent;
			if (node->_parent) {
				if (node == node->_parent->_left)
					node->_parent->_left = y;
				else
					node->_parent->_right = y;
			} else {
				_root = y;
			}

			/* link node and y */
			y->_left = node;
			if (node != nullptr) node->_parent = y;
		}

		void _rotateRight(_tNode *node) {
			_tNode *y = node->_left;

			/* establish node->_left link */
			node->_left = y->_right;
			if (y->_right != nullptr) y->_right->_parent = node;

			/* establish y->_parent link */
			if (y != nullptr) y->_parent = node->_parent;
			if (node->_parent) {
				if (node == node->_parent->_right)
					node->_parent->_right = y;
				else
					node->_parent->_left = y;
			} else {
				_root = y;
			}

			/* link node and y */
			y->_right = node;
			if (node != nullptr) node->_parent = y;
		}

		void _balanceAfterInsert(_tNode *node) {
			/* check Red-Black properties */
			while (node != _root && node->_parent->_color == red) {

				/* we have a violation */
				if (node->_parent == node->_parent->_parent->_left) {
					_tNode *y = node->_parent->_parent->_right;
					if (y && y->_color == red) {

						/* uncle is red */
						node->_parent->_color = black;
						y->_color = black;
						node->_parent->_parent->_color = red;
						node = node->_parent->_parent;
					} else {

						/* uncle is black */
						if (node == node->_parent->_right) {
							/* make node a left child */
							node = node->_parent;
							_rotateLeft(node);
						}

						/* recolor and rotate */
						node->_parent->_color = black;
						node->_parent->_parent->_color = red;
						_rotateRight(node->_parent->_parent);
					}
				} else {
					/* mirror image of above code */
					_tNode *y = node->_parent->_parent->_left;
					if (y && y->_color == red) {

						/* uncle is red */
						node->_parent->_color = black;
						y->_color = black;
						node->_parent->_parent->_color = red;
						node = node->_parent->_parent;
					} else {
						/* uncle is black */
						if (node == node->_parent->_left) {
							node = node->_parent;
							_rotateRight(node);
						}
						node->_parent->_color = black;
						node->_parent->_parent->_color = red;
						_rotateLeft(node->_parent->_parent);
					}
				}
			}
			_root->_color = black;
		}

		void _balanceAfterDelete(_tNode *node) {
			_tNode *s;
			while (node != _root && node->_color == black) {
				if (node == node->_parent->_left) {
					s = node->_parent->_right;
					if (s->_color == red) {
						s->_color = black;
						node->_parent->_color = red;
						_rotateLeft(node->_parent);
						s = node->_parent->_right;
					}

					if ((!s->_left || s->_left->_color == black) && (!s->_right || s->_right->_color == black)) {
						s->_color = red;
						node = node->_parent;
					} else {
						if (!s->_right || s->_right->_color == black) {
							s->_left->_color = black;
							s->_color = red;
							_rotateRight(s);
							s = node->_parent->_right;
						}

						s->_color = node->_parent->_color;
						node->_parent->_color = black;
						s->_right->_color = black;
						_rotateLeft(node->_parent);
						node = _root;
					}
				} else {
					s = node->_parent->_left;
					if (s->_color == red) {
						s->_color = black;
						node->_parent->_color = red;
						_rotateRight(node->_parent);
						s = node->_parent->_left;
					}

					if ((!s->_left || s->_left->_color == black) && (!s->_right || s->_right->_color == black)) {
						s->_color = red;
						node = node->_parent;
					} else {
						if (!s->_left || s->_left->_color == black) {
							s->_right->_color = black;
							s->_color = red;
							_rotateLeft(s);
							s = node->_parent->_left;
						}

						s->_color = node->_parent->_color;
						node->_parent->_color = black;
						s->_left->_color = black;
						_rotateRight(node->_parent);
						node = _root;
					}
				}
			}
			node->_color = black;
		}

		iterator _checkBounds(_tNode *node, const key_type& k, bool isLower) {
			if (!node || node == _preFirstNode || node == _postLastNode)
				return iterator(_postLastNode);

			bool less = _comp(k, node->_data->first);
			bool greater = _comp(node->_data->first, k);
			if (!less && !greater) {
				if (!isLower)
					return iterator(node);
				return ++iterator(node);
			}
			if (less) {
				if (!node->_left || node->_left == _preFirstNode) {
					if (isLower)
						return ((!node->_left) ? --iterator(node) : iterator(node));
					return iterator(node);
				}
				return _checkBounds(node->_left, k, isLower);
			} else {
				if (!node->_right || node->_right == _postLastNode) {
					if (isLower)
						return ((!node->_right) ? iterator(node) : iterator(_postLastNode));
					return ++iterator(node);
				}
				return _checkBounds(node->_right, k, isLower);
			}
		}
		/* -------------------------------------------------------------------------- */

		public:
		/**** Constructor ****/
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _root(nullptr), _size(0), _allocData(alloc), _comp(comp) {
			_createTheoreticalNodes();
		};

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type(),
			 typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) : _root(nullptr), _size(0), _allocData(alloc), _comp(comp) {
			_createTheoreticalNodes();
			for (; first != last; first++) {
				this->insert(*first);
			}
		 };

		map (const map& node) : _root(nullptr), _size(0) {
			_createTheoreticalNodes();
			*this = node;
		};

		/**** Destructor ****/
		~map() {
			clear();
			_allocData.destroy(_preFirstNode->_data);
			_allocNode.destroy(_preFirstNode);
			_allocData.destroy(_postLastNode->_data);
			_allocNode.destroy(_postLastNode);
			_allocData.deallocate(_preFirstNode->_data, 1);
			_allocNode.deallocate(_preFirstNode, 1);
			_allocData.deallocate(_postLastNode->_data, 1);
			_allocNode.deallocate(_postLastNode, 1);
		};

		/**** Assign content ****/
		map& operator= (const map& x) {
			if (this != &x) {
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		};

		/**** Iterators ****/
		iterator begin() { return iterator(_preFirstNode->_parent); }
		const_iterator begin() const { return const_iterator(_preFirstNode->_parent); }
		reverse_iterator rbegin() { return reverse_iterator(_postLastNode->_parent); };
		const_reverse_iterator rbegin() const { return reverse_iterator(_postLastNode->_parent); };

		iterator end() { return iterator(_postLastNode); };
		const_iterator end() const { return iterator(_postLastNode); };
		reverse_iterator rend() { return reverse_iterator(_preFirstNode); };
		const_reverse_iterator rend() const { return reverse_iterator(_preFirstNode); };

		/**** Capacity ****/
		bool empty() const { return (_size == 0); };
		size_type size() const { return this->_size; };
		size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_tNode); };

		/****  Element access ****/
		mapped_type& operator[] (const key_type& k) {
			value_type elem = std::make_pair(k, mapped_type());
			std::pair<iterator, bool> res = insert(elem);
			return ((*res.first).second);
		};

		/**** Modifiers ****/
		std::pair<iterator, bool> insert (const value_type& val) {
			/* find where node belongs */
			_tNode *current = _root;
			_tNode *parent = nullptr;
			while (current != nullptr && current != _postLastNode && current != _preFirstNode) {
				if (val.first == (current->_data->first)) return std::make_pair(iterator(current), false);
				parent = current;
				current = (val.first < current->_data->first) ? current->_left : current->_right;
			}
			_deleteTheoreticalBinds();
			_tNode *newNode = _createNode(val, parent);
			_insertNodeInTree(parent, newNode);
			_size += 1;
			_balanceAfterInsert(newNode);
			_addTheoreticalBinds();
			return std::make_pair(iterator(newNode), true);
		};

		iterator insert (iterator position, const value_type& val) {
			static_cast<void>(position);
			return insert(val).first;
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
					 typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) {
			for (; first != last; first++) {
				this->insert(*first);
			}
		};

		void erase (iterator position) {
			_tNode *node = position.getData();
			_deleteTheoreticalBinds();
			if (node == nullptr)
				return;
			_tNode *x, *y, tmp;
			tmp._color = black;
			tmp._left = &tmp;
			tmp._right = &tmp;
			tmp._data = nullptr;
			tmp._parent = nullptr;

			if (node->_left == nullptr || node->_right == nullptr) {
				y = node;
			} else {
				y = node->_right;
				while (y->_left != nullptr) y = y->_left;
			}
			if (y->_left != nullptr)
				x = y->_left;
			else if (y->_right != nullptr)
				x = y->_right;
			else
				x = &tmp;
			x->_parent = y->_parent;
			if (y->_parent)
				if (y == y->_parent->_left)
					y->_parent->_left = x;
				else
					y->_parent->_right = x;
			else
				_root = x;

			bool flag = false;
			if (y != node) { flag = true; }

			if (y->_color == black) {
				_balanceAfterDelete(x);
			}
			if (flag)
				_changeNodes(node, y);

			if (tmp._parent != nullptr) {
				if (tmp._parent->_right == &tmp)
					tmp._parent->_right = nullptr;
				else if (tmp._parent->_left == &tmp)
					tmp._parent->_left = nullptr;
			}
			_size -= 1;
			_allocData.destroy(node->_data);
			_allocNode.destroy(node);
			_allocData.deallocate(node->_data, 1);
			_allocNode.deallocate(node, 1);
			if (_size == 0)
				_root = nullptr;
			_addTheoreticalBinds();
		};

		size_type erase (const key_type& k) {
			iterator node = this->find(k);
			if (node == iterator(_postLastNode))
				return 0;
			this->erase(node);
			return 1;
		};

		void erase (iterator first, iterator last) {
			iterator tmp;
			while(first != last) {
				tmp = first;
				first++;
				erase(tmp);
			}
		};

		void clear() { erase(this->begin(), this->end()); };

		void swap (map& x) {
			_tNode *tmp = _root;
			_root = x._root;
			x._root = tmp;

			tmp = _postLastNode;
			_postLastNode = x._postLastNode;
			x._postLastNode = tmp;

			tmp = _preFirstNode;
			_preFirstNode = x._preFirstNode;
			x._preFirstNode = tmp;

			size_t tmpSize = _size;
			_size = x._size;
			x._size = tmpSize;
		};

		/**** Observers ****/
		key_compare key_comp() const { return _comp; };
		value_compare value_comp() const { return value_compare(_comp); };

		/**** Operations ****/
		iterator find (const key_type& k) {
			_tNode *current = _root;
			while(current != nullptr && current != _postLastNode && current != _preFirstNode) {
				if(k == current->_data->first)
					return iterator(current);
				else
					current = (k < current->_data->first) ?
							  current->_left : current->_right;
			}
			return iterator(_postLastNode);
		};
		const_iterator find (const key_type& k) const {
			_tNode *current = _root;
			while(current != nullptr && current != _postLastNode && current != _preFirstNode) {
				if(k == current->_data->first)
					return const_iterator(current);
				else
					current = (k < current->_data->first) ?
							  current->_left : current->_right;
			}
			return const_iterator(_postLastNode);
		};
		size_type count (const key_type& k) const {
			const_iterator res = this->find(k);
			if (res == const_iterator(_postLastNode))
				return 0;
			return 1;
		};
		iterator lower_bound (const key_type& k) { return _checkBounds(_root, k, false); };
		const_iterator lower_bound (const key_type& k) const { return _checkBounds(_root, k, false); };
		iterator upper_bound (const key_type& k) { return _checkBounds(_root, k, true); };
		const_iterator upper_bound (const key_type& k) const { return _checkBounds(_root, k, true); };
		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return std::make_pair(lower_bound(k), upper_bound(k)); };
		std::pair<iterator,iterator> equal_range (const key_type& k) { return std::make_pair(lower_bound(k), upper_bound(k)); };
	};
}

#endif
