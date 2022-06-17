#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

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
/* -------------------------------------------------------------------------- */

namespace ft {

	template <typename Key, typename Value>
	class LLRB {
		private:
			typedef Key* key_pointer;
			typedef Value* value_pointer;

			struct Node {
				Key _key;
				Value _value;
				Node * _left;
				Node * _right;
				std::bitset<1> _color;
				public:
					Node() : _key(), _value(), _left(nullptr), _right(nullptr), _color(RED) {}
					Node(Key key, Value value) : _key(key), _value(value), _left(nullptr), _right(nullptr) {
						this->_color = RED; // new nodes are always red
					} 
			};

			typedef Node* pointer;

			pointer _root;
		public:
			LLRB() : _root(nullptr) {}
			explicit LLRB(Key key, Value value) {
				this->_root = new Node(key, value);
			}
			// Будет дополняться другими конструкторами
		
		
			/* ------------------------------ Help methods ------------------------------ */
		public:
			key_pointer min() {
				pointer node = this->_root;
				while(node->_left != nullptr)
					node = node->_left;
				if (node == nullptr)
					return NULL;
				return &node->_key;
			}

			key_pointer min(pointer node) {
				pointer tmp = node;
				while(tmp->_left != nullptr)
					tmp = tmp->_left;
				if (tmp == nullptr)
					return 0;
				return &tmp->_key;	
			}
			
			value_pointer get(Key key) {
				pointer tmp = this->_root;
				while(tmp != nullptr) {
					if (key == tmp->_key)
						return &tmp->_value;
					else if (key < tmp->_key)
						tmp = tmp->_left;
					else
						tmp = tmp->_right;
				}
				return NULL;
			}

			value_pointer get(pointer node, Key key) {
				pointer tmp = node;
				while(tmp != nullptr) {
					if (key == tmp->_key)
						return &tmp->_value;
					else if (key < tmp->_key)
						tmp = tmp->_left;
					else
						tmp = tmp->_right;
				}
				return NULL;
			}
		private:
			inline bool isRed(pointer node) {
				if (node == nullptr)
					return false;
				return node->_color == RED ? true : false; 
			}
			inline void flipColor(pointer node) { node->_color.flip(); }
			/* -------------------------------------------------------------------------- */

			/* ---------------------- Node rotations and color flip --------------------- */
			pointer rotateLeft(pointer unit) {
				pointer balanced = unit->_right;
				unit->_right = balanced->_left;
				balanced->_left = unit;
				balanced->_color = unit->_color;
				unit->_color = RED;
				return balanced;
			}

			pointer rotateRight(pointer unit) {
				pointer balanced = unit->_left;
				unit->_left= balanced->_right;
				balanced->_right= unit;
				balanced->_color = unit->_color;
				unit->_color = RED;
				return balanced;
			}

			void colorFlip(pointer unit) {
				flipColor(unit);
				flipColor(unit->_left);
				flipColor(unit->_right);
			}

			pointer moveRedLeft(pointer unit) {
				colorFlip(unit);
				if (isRed(unit->_right->_left)) {
					unit->_right = rotateRight(unit->_right);
					unit = rotateLeft(unit);
					colorFlip(unit);
				}
				return unit;
			}
			pointer moveRedRight(pointer unit) {
				colorFlip(unit);
				if (isRed(unit->_left->_left)) {
					unit = rotateRight(unit);
					colorFlip(unit);
				}
				return unit;
			}

			pointer fixUp(pointer unit) {
				if (isRed(unit->_right))
					unit = rotateLeft(unit);
				if (isRed(unit->_left) && isRed(unit->_left->_left))
					unit = rotateRight(unit);
				if (isRed(unit->_left) && isRed(unit->_right))
					colorFlip(unit);
				return unit;
			}
			/* -------------------------------------------------------------------------- */
		public:
			/* --------------------------------- Search --------------------------------- */
			value_pointer search(Key key) {
				pointer node = this->_root;
				while (node != nullptr) {
					if (key == node->_key)
						return &node->_value;
					else if (key < node->_key) 
						node = node->_left;
					else if (key > node->_key)
						node = node->_right;
				}
				return NULL;
			}
			/* -------------------------------------------------------------------------- */

			/* --------------------------------- Insert --------------------------------- */
			void insert(Key key, Value value) {
				this->_root = insert(this->_root, key, value);
				this->_root->_color = BLACK;
			}

		private : 
			pointer insert(pointer unit, Key key, Value value) {
				if (unit == nullptr)
					return new Node(key, value);
				if (isRed(unit->_left) && isRed(unit->_right))
					colorFlip(unit);
				if (key == unit->_key)
					unit->_value = value;
				else if (key < unit->_key)
					unit->_left = insert(unit->_left, key, value);
				else
					unit->_right = insert(unit->_right, key, value);

				// Balancing by rotating
				if (isRed(unit->_right) && isRed(unit->_left) == false)
					unit = rotateLeft(unit);
				if (isRed(unit->_left) && isRed(unit->_left->_left))
					unit = rotateRight(unit);
				
				return unit;
			}
			/* -------------------------------------------------------------------------- */

			/* --------------------------------- Delete --------------------------------- */
		public:

			void deleteMin() {
				this->_root = deleteMin(this->_root);
				this->_root.color = BLACK;
			}

			void delete_(Key key) {
				this->_root = delete_(this->_root, key);
				this->_root->_color = BLACK;
			}
			
		private:

			pointer deleteMin(pointer unit) {
				if (unit->_left == nullptr)
					return nullptr;
				if (isRed(unit->_left) == false && isRed(unit->_left->_left) == false)
					unit = moveRedLeft(unit);
				unit->_left = deleteMin(unit->_left);

				return fixUp(unit);
			}

			pointer delete_(pointer unit, Key key) {
				if (key < unit->_key) {
					if (isRed(unit->_left) == false && isRed(unit->_left->_left))
						unit = moveRedLeft(unit);
					unit->_left = delete_(unit->_left, key);
				} else {
					if (isRed(unit->_left))
						unit = rotateRight(unit);
					if (key == unit->_key && unit->_right == nullptr)
						return NULL;
					if (isRed(unit->_right) == false && isRed(unit->_right->_left) == false)
						unit = moveRedRight(unit);
					if (key == unit->_key) {
						unit->_key = *min(unit->_right);
						unit->_value = *get(unit->_right, unit->_key);
						unit->_right = deleteMin(unit->_right);
					} else
						unit->_right = delete_(unit->_right, key);
				}
				return fixUp(unit);
			}
			/* -------------------------------------------------------------------------- */


	};
}

#endif
