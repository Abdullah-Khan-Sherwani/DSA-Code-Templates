#include <iostream>
#include <vector>
#include <stdexcept>

template<typename Key, typename Value>
class BST {
	struct Node {
		Key key;
		Value val;
		Node* right;                                                            // Right tree with larger values
		Node* left;                                                             // left tree with smaller values
		int count;                                                              // Node count to keep track of subtree size
		int height;                                                             // Counts depth of the tree

		Node(Key k, Value v, int c) : key(k), val(v), right(nullptr), left(nullptr), count(c), height(0) {}
		Node(Key k, Value v) : key(k), val(v), right(nullptr), left(nullptr), count(1) {}
		Node() : right(nullptr), left(nullptr), count(0) {}
	};

	Node* root;

	Node* put(Node* x, Key key, Value val) {
		if (x == nullptr) return new Node(key, val, 1);                         // if x is null, return a new node with default count of 1

		if (key < x->key) {
			x->left = put(x->left, key, val);                                   // go left if key is smaller than x and update left pointer
		} else if (key > x->key) {
			x->right = put(x->right, key, val);                                 // go right if key is greater than x and update right pointer
		} else {
			x->val = val;                                                       // Overwrite x's value if it already exists
		}

		x->count = 1 + size(x->left) + size(x->right);                          // Update the count of the current node
		x->height = height(x);                                                  // Update height of the tree
		return x;                                                               // Return the updated node
	}


	size_t size(Node* x) {
		if (x == nullptr) return 0;
		return x->count;
	}

	int rank(Key key, Node* x) {                                                // If node is null, return 0
		if (x == nullptr) return 0;

		if (key > x->key) return 1 + size(x->left) + rank(key, x->right);       // Recur right if key is greater than x's key
		else if (key < x->key) return rank(key, x->left);                       // Recur left if key is smaller than x's key
		else return size(x->left);                                              // Return the size of left subtree if key is found
	}

	void inorder(Node* x, std::vector<Key>& keys) {
		if (x == nullptr) return;                                               // Base case: return if node is null

		inorder(x->left, keys);                                                 // Traverse left subtree
		keys.push_back(x->key);                                                 // Add current node's key
		inorder(x->right, keys);                                                // Traverse right subtree
	}

	Node* Floor(Node* x, Key key) {
		if (x == nullptr) return nullptr;										// Base case: if the current node is null, no floor can be found

		if (x->key == key) return x;											// If we find the exact key, this node is the floor
		if (x->key > key) return Floor(x->left, key);							// If the current node's key is greater than the target key, search in the left subtree, where smaller keys are located

		Node* t = Floor(x->right, key);											// If the current node's key is less than the target key, search in the right subtree for a closer match
		if (t != nullptr) return t;												// If a valid floor was found in the right subtree, return it
		return x;																// If no closer match in the right subtree, the current node is the floor
	}
	Node* Ceil(Node* x, Key key) {
		if (x == nullptr) return nullptr;										// Base case: if the current node is null, no ceil can be found

		if (x->key == key) return x;											// If we find the exact key, this node is the ceil
		if (x->key < key) return Ceil(x->right, key);							// If the current node's key is less than the target key, search in the right subtree, where larger keys are located

		Node* t = Ceil(x->left, key);											// If the current node's key is greater than the target key, search in the left subtree for a closer match
		if (t != nullptr) return t;												// If a valid ceil was found in the left subtree, return it
		return x;																// If no closer match in the left subtree, the current node is the ceil
	}

	Node* removeMin(Node* x) {
		if (x->left == nullptr) {
			Node* right = x->right;
			delete x;
			return right;
		}
		x->left  = removeMin(x->left);

		x->count = 1 + size(x->left) + size(x->right);
		x->height = height(x);
		return x;
	}

	// modify delete x node into public function to avoid memory leak
	Node* removeMax(Node* x) {
		if (x->right == nullptr) {
			Node* left = x->left;
			delete x;
			return left;
		}
		x->right = removeMax(x->right);

		x->count = 1 + size(x->left) + size(x->right);
		x->height = height(x);
		return x;
	}

	Node* remove(Node* x, const Key& key) {
		if (x == nullptr) return nullptr;

		if (key < x->key) {
			x->left = remove(x->left, key);
		} else if (key > x->key) {
			x->right = remove(x->right, key);
		} else {
			// Key found, proceed with deletion
			if (x->left == nullptr) {  // No left child
				Node* temp = x->right;
				delete x;  // Free memory of the current node
				return temp;
			}
			if (x->right == nullptr) {  // No right child
				Node* temp = x->left;
				delete x;  // Free memory of the current node
				return temp;
			}
			
			/*// Exception on root
			Node* t = x;
      		x = min(t->right);  // See page 407.
      		x->right = removeMin(t->right);
      		x->left = t->left;
			delete t;*/
			// Node with two children
			Node* minNode = min(x->right);  // Find successor minimum in right subtree
			x->key = minNode->key;          // Copy successor's key
			x->val = minNode->val;          // Copy successor's value
			x->right = remove(x->right, minNode->key);  // Remove successor node
		}

		// Recompute metadata (size and height)
		x->count = 1 + size(x->left) + size(x->right);
		x->height = height(x);
		return x;
	}

	Node* min(Node* x) {
		if (x == nullptr) throw std::out_of_range("called min() with empty symbol table");
		while (x->left != nullptr) x = x->left;
		return x;
	}

	Node* max(Node* x) {
		if(x == nullptr) throw std::out_of_range("called max() with empty symbol table");
		while (x->right != nullptr) x = x->right;
		return x;
	}

	Node* select(Node* x, int k) {
		if (x == nullptr) return nullptr;

		int t = size(x->left);
		if (t > k)
			return select(x->left,  k);
		else if (t < k)
			return select(x->right, k-t-1);
		else
			return x;
	}

	int height (Node* x) {
		if (x == nullptr) return -1;

		return 1 + std::max(height(x->right), height(x->left));
	}

public:
	BST() : root(nullptr) {}

	void put(Key key, Value val) {
		root = put(root, key, val);
	}

	Value get(Key key) {
		Node* x = root;

		while (x != nullptr) {                                                  // Search loop until key is found or null
			if (key < x->key) x = x->left;                                      // Move left if key is smaller
			else if (key > x->key) x = x->right;                                // Move right if key is larger
			else return x->val;                                                 // Return value if key matches
		}

		throw std::out_of_range("Value Not Found");                             // Throw exception if key is not in tree
	}

	size_t size() {
		return size(root);
	}

	int rank(Key key) {
		return rank(key, root);
	}

	Key Floor(Key key) {
		Node* x = Floor(root, key);
		if (x == nullptr) throw std::out_of_range("No floor exists for the given key");
		return x->key;
	}

	Key Ceil(Key key) {
		Node* x = Ceil(root, key);
		if (x == nullptr) throw std::out_of_range("No ceiling exists for the given key");
		return x->key;
	}

	std::vector<Key> keys() {
		std::vector<Key> keyList;
		inorder(root, keyList);
		return keyList;
	}

	int height() {
		return root->height;
	}

	void removeMax() {
		if (root == nullptr) throw std::out_of_range("Symbol table underflow");
		root = removeMax(root);
	}

	void removeMin() {
		if(root == nullptr) throw std::out_of_range("Symbol table underflow");
		root = removeMin(root);
	}

	void remove(const Key& key) {
		root = remove(root, key);
	}

	Key min() {   //Returns the smallest key in the BST.
		if (root == nullptr) throw std::out_of_range("called min() with empty symbol table");
		Node* x = root;
		while (x->left != nullptr) x = x->left;
		return x->key;
	}

	Key max() {
		if (root == nullptr) throw std::out_of_range("called max() with empty symbol table");
		Node* traverse = root;
		while (traverse->right != nullptr) {
			traverse = traverse->right;
		}
		return traverse->key;                                                   // Return the maximum key
	}

	Key select(int k) {                                                         //Returns the key with a specified rank k.
		if (k < 0 || k >= size())
			throw std::out_of_range("called select() with invalid argument");

		Node* x = select(root, k);
		return x->key;
	}

	Value& operator[](const Key& key) {                                         //Accesses or inserts the value for a given key. If the key doesn't exist, it inserts a new node with a default value.
		if (root == nullptr)
			root = new Node(key, Value());

		Node* x = root;
		while(true) {
			if (key < x->key) {
				if(x->left==nullptr) x->left = new Node(key, Value());
				x = x->left;
			}
			else if (x->key < key) {
				if(x->right==nullptr) x->right = new Node(key, Value());
				x = x->right;
			}
			else return x->val;
		}
	}
};