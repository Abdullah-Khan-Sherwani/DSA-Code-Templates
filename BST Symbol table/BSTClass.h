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

		Node(Key k, Value v, int c) : key(k), val(v), right(nullptr), left(nullptr), count(c) {}
		Node(Key k, Value v) : key(k), val(v), right(nullptr), left(nullptr), count(1) {}
		Node() : right(nullptr), left(nullptr), count(0) {}
	};

	Node* root;

	Node* put(Node* x, Key key, Value val) {
		if (x == nullptr) return new Node(key, val, 1);                            // if x is null, return a new node with default count of 1

		if (key < x->key) {
			x->left = put(x->left, key, val);                                   // go left if key is smaller than x and update left pointer
		} else if (key > x->key) {
			x->right = put(x->right, key, val);                                 // go right if key is greater than x and update right pointer
		} else {
			x->val = val;                                                       // Overwrite x's value if it already exists
		}

		x->count = 1 + size(x->left) + size(x->right);                          // Update the count of the current node
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
		// Base case: if the current node is null, no floor can be found
		if (x == nullptr) return nullptr;

		// If we find the exact key, this node is the floor
		if (x->key == key) return x;

		// If the current node's key is greater than the target key,
		// search in the left subtree, where smaller keys are located
		if (x->key > key) return Floor(x->left, key);

		// If the current node's key is less than the target key,
		// search in the right subtree for a closer match
		Node* t = Floor(x->right, key);

		// If a valid floor was found in the right subtree, return it
		if (t != nullptr) return t;

		// If no closer match in the right subtree, the current node is the floor
		return x;
	}
	Node* Ceil(Node* x, Key key) {
		// Base case: if the current node is null, no ceil can be found
		if (x == nullptr) return nullptr;

		// If we find the exact key, this node is the ceil
		if (x->key == key) return x;

		// If the current node's key is less than the target key,
		// search in the right subtree, where larger keys are located
		if (x->key < key) return Ceil(x->right, key);

		// If the current node's key is greater than the target key,
		// search in the left subtree for a closer match
		Node* t = Ceil(x->left, key);

		// If a valid ceil was found in the left subtree, return it
		if (t != nullptr) return t;

		// If no closer match in the left subtree, the current node is the ceil
		return x;

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
};



/*#include <iostream>
#include <vector>

template<typename Key, typename Value>
class BST {
	struct Node {
		Key key;
		Value val;
		Node* right;                                                            // Right tree with larger values
		Node* left;                                                             // left tree with smaller values
		int count

		Node(Key k, Value v, count c) : key(k), val(v), right(nullptr), left(nullptr), count(c) {}
		Node(Key k, Value v) : key(k), val(v), right(nullptr), left(nullptr), count(1) {}
		Node() : right(nullptr), left(nullptr), count(0) {}
	};

	Node* root;

	Node* put(Node* x, Key key, Value val) {
		if(x == nullptr) return new Node(key, val, 1);                          // if x null return a new node which will connect with the remaining nodes

		if(key < x->key) return put(x->left, key, val);                         // go left if key is smaller than x
		else if(key > x->key) return put(x->right, key, val);                   // go right if key is greater than x
		else x->val = val;                                                      // Overwrite x's value if it already exists
		x->count = 1 + size(x->left) + size(x->right);
		return x;                                                               // Due to else statement just returns the same node with the value changed
	}

	size_t size(Node* x) {
		if(x == nullptr) return 0;
		return x->count;
	}

	int rank(Key key, Node x) {
		if(x == nullptr) return 0;

		if(key > x->key) return 1 + size(x->left) + rank(key, x->right);
		else if(key < x->key) return rank(key, x->left);
		else return size(x->left);
	}

	void inorder(Node* x, std::vector<Key> keys) {
		if(x == nullptr) return;

		inorder(x->left, keys);
		keys.push_back(x->key);
		inorder(x->right, keys);
	}

	Node* Floor(Node x, Key key) {
		// Base case: if the current node is null, no floor can be found
		if (x == nullptr) return nullptr;

		// If we find the exact key, this node is the floor
		if (x->key == key) return x;

		// If the current node's key is greater than the target key,
		// search in the left subtree, where smaller keys are located
		if (x->key > key) return Floor(x->left, key);

		// If the current node's key is less than the target key,
		// search in the right subtree for a closer match
		Node* t = Floor(x->right, key);

		// If a valid floor was found in the right subtree, return it
		if (t != nullptr) return t;

		// If no closer match in the right subtree, the current node is the floor
		return x;
	}
	Node* Ceil(Node x, Key key) {
		// Base case: if the current node is null, no ceil can be found
		if (x == nullptr) return nullptr;

		// If we find the exact key, this node is the ceil
		if (x->key == key) return x;

		// If the current node's key is less than the target key,
		// search in the right subtree, where larger keys are located
		if (x->key < key) return Ceil(x->right, key);

		// If the current node's key is greater than the target key,
		// search in the left subtree for a closer match
		Node* t = Ceil(x->left, key);

		// If a valid ceil was found in the left subtree, return it
		if (t != nullptr) return t;

		// If no closer match in the left subtree, the current node is the ceil
		return x;

	}

public:
	BST(Key k, Value v) : root(k, v) {}
	BST() {}

	void put(Key key, Value val) {
		root = put(root, key, val);
	}

	Value get(Key key) {
		Node* x = root;

		while(x != nullptr) {
			if(key < x) x = x->left;
			else if(key > x) x = x->right;
			else return x->val;
		}

		return std::out_of_range("Value Not Found");
	}

	size_t size() {
		return size(root);
	}

	int rank(Key key) {
		return rank(key, root);
	}

	Key Floor(Key key) {
		Node* x = Floor(root, key);
		if(x == nullptr) throw std::out_of_range("Tree empty");
		else return x->key;
	}

	Key Ceil(Key key){
	    Node* x = Ceil(root, key);
	    if(x == nullptr) throw std::out_of_range("Tree Empty");
	    else return x->key;
	}

	std::vector<Keys> keys() {
		std::vector<key> keyList;
		inorder(root, keyList);
		return keyList;
	}
};*/