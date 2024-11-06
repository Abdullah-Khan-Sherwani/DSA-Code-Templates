#include <iostream>
#include <vector>
#include <stdexcept>

// INCOMPLETE
// Remove functions not maintaining LLRB property
template <typename Key, typename Value>
class LLRB
{
    static constexpr bool RED = true;
    static constexpr bool BLACK = false;

    struct Node
    {
        Key key;
        Value val;
        Node *right; // Right tree with larger values
        Node *left;  // left tree with smaller values
        int count;   // Node count to keep track of subtree size
        int height;  // Counts depth of the tree
        bool color;

        Node(Key k, Value v, int c, bool col) : key(k), val(v), right(nullptr), left(nullptr), count(c), height(0), color(col) {}
        Node(Key k, Value v) : key(k), val(v), right(nullptr), left(nullptr), count(1) {}
        Node() : right(nullptr), left(nullptr), count(0) {}
    };

    Node *root;

    bool isRed(Node *x)
    {
        if (x == nullptr)
            return false;
        return x->color == RED;
    }

    void flipColors(Node *h)
    {
        h->color = RED;
        h->left->color = BLACK;
        h->right->color = BLACK;
    }

    Node *rotateLeft(Node *h)
    {
        if (h == nullptr || h->right == nullptr)
        {
            return h; // No rotation needed if either h or h->right is null
        }

        Node *x = h->right; // x is the node that will move up
        h->right = x->left; // h's right child becomes x's left child
        x->left = h;        // h becomes x's left child

        // Update colors after the rotation
        x->color = h->color; // x takes the color of h
        h->color = RED;      // h becomes red after rotation

        // Update counts (size of the subtree rooted at each node)
        x->count = 1 + size(x->left) + size(x->right);
        h->count = 1 + size(h->left) + size(h->right);

        return x; // x is the new root of the rotated subtree
    }

    Node *rotateRight(Node *h)
    {
        if (h == nullptr || h->left == nullptr)
        {
            return h; // No rotation needed if either h or h->left is null
        }

        Node *x = h->left;  // x is the node that will move up
        h->left = x->right; // h's left child becomes x's right child
        x->right = h;       // h becomes x's right child

        // Update colors after the rotation
        x->color = h->color; // x takes the color of h
        h->color = RED;      // h becomes red after rotation

        // Update counts (size of the subtree rooted at each node)
        x->count = 1 + size(x->left) + size(x->right);
        h->count = 1 + size(h->left) + size(h->right);

        return x; // x is the new root of the rotated subtree
    }

    Node *put(Node *h, Key key, Value val)
    {
        if (h == nullptr)
            return new Node(key, val, 1, RED); // if h is null, return a new node with default count of 1

        if (key < h->key)
        {
            h->left = put(h->left, key, val); // go left if key is smaller than h and update left pointer
        }
        else if (key > h->key)
        {
            h->right = put(h->right, key, val); // go right if key is greater than h and update right pointer
        }
        else
        {
            h->val = val; // Overwrite h's value if it already exists
        }

        if (isRed(h->right) && !isRed(h->left))
            h = rotateLeft(h);
        if (isRed(h->left) && isRed(h->left->left))
            h = rotateRight(h);
        if (isRed(h->right) && isRed(h->left))
            flipColors(h);

        h->count = 1 + size(h->left) + size(h->right); // Update the count of the current node
        h->height = height(h);                         // Update height of the tree
        return h;                                      // Return the updated node
    }

    size_t size(Node *x)
    {
        if (x == nullptr)
            return 0;
        return x->count;
    }

    int rank(Key key, Node *x)
    { // If node is null, return 0
        if (x == nullptr)
            return 0;

        if (key > x->key)
            return 1 + size(x->left) + rank(key, x->right); // Recur right if key is greater than x's key
        else if (key < x->key)
            return rank(key, x->left); // Recur left if key is smaller than x's key
        else
            return size(x->left); // Return the size of left subtree if key is found
    }

    void inorder(Node *x, std::vector<Key> &keys)
    {
        if (x == nullptr)
            return; // Base case: return if node is null

        inorder(x->left, keys);  // Traverse left subtree
        keys.push_back(x->key);  // Add current node's key
        inorder(x->right, keys); // Traverse right subtree
    }

    Node *Floor(Node *x, Key key)
    {
        if (x == nullptr)
            return nullptr; // Base case: if the current node is null, no floor can be found

        if (x->key == key)
            return x; // If we find the exact key, this node is the floor
        if (x->key > key)
            return Floor(x->left, key); // If the current node's key is greater than the target key, search in the left subtree, where smaller keys are located

        Node *t = Floor(x->right, key); // If the current node's key is less than the target key, search in the right subtree for a closer match
        if (t != nullptr)
            return t; // If a valid floor was found in the right subtree, return it
        return x;     // If no closer match in the right subtree, the current node is the floor
    }
    Node *Ceil(Node *x, Key key)
    {
        if (x == nullptr)
            return nullptr; // Base case: if the current node is null, no ceil can be found

        if (x->key == key)
            return x; // If we find the exact key, this node is the ceil
        if (x->key < key)
            return Ceil(x->right, key); // If the current node's key is less than the target key, search in the right subtree, where larger keys are located

        Node *t = Ceil(x->left, key); // If the current node's key is greater than the target key, search in the left subtree for a closer match
        if (t != nullptr)
            return t; // If a valid ceil was found in the left subtree, return it
        return x;     // If no closer match in the left subtree, the current node is the ceil
    }

    Node *balance(Node *h)
    {
        if (isRed(h->right))
        {
            h = rotateLeft(h);
        }

        if (isRed(h->left) && isRed(h->left->left))
        {
            h = rotateRight(h);
        }
        if (isRed(h->left) && isRed(h->right))
        {
            flipColors(h);
        }

        h->count = 1 + size(h->right) + size(h->left);
        h->height = height(h);
        return h;
    }

    Node *min(Node *x)
    {
        if (x == nullptr)
            throw std::out_of_range("called min() with empty symbol table");
        while (x->left != nullptr)
            x = x->left;
        return x;
    }

    Node *max(Node *x)
    {
        if (x == nullptr)
            throw std::out_of_range("called max() with empty symbol table");
        while (x->right != nullptr)
            x = x->right;
        return x;
    }

    Node *removeMin(Node *h)
    {
        if (h == nullptr)
            return nullptr; // Return if h is nullptr

        if (h->left == nullptr) // If left is null, this is the minimum node
        {
            delete h;
            return nullptr;
        }

        if (!isRed(h->left) && !isRed(h->left->left)) // Ensure red link on the left
        {
            h = rotateLeft(h);
        }

        h->left = removeMin(h->left);
        return balance(h);
    }

    Node *removeMax(Node *h)
    {
        if (h == nullptr)
            return nullptr;

        if (isRed(h->left)) // Ensure that the left link is red
        {
            h = rotateRight(h);
        }

        if (h->right == nullptr) // If right is null, this is the max node
        {
            delete h;
            return nullptr;
        }

        h->right = removeMax(h->right);
        return balance(h);
    }

    Node *remove(Node *h, Key key)
    {
        if (h == nullptr)
            return nullptr;

        if (key < h->key)
        {
            if (h->left != nullptr && !isRed(h->left) && !isRed(h->left->left))
            {
                h = rotateLeft(h); // Adjust to ensure the left link is red
            }
            h->left = remove(h->left, key);
        }
        else
        {
            if (isRed(h->left))
            {
                h = rotateRight(h);
            }

            if (key == h->key && h->right == nullptr) // If the node to remove is found and it has no right child
            {
                delete h;
                return nullptr;
            }

            if (h->right != nullptr && !isRed(h->right) && !isRed(h->right->left))
            {
                h = rotateLeft(h);
            }

            if (key == h->key)
            {
                Node *x = min(h->right);
                h->key = x->key;
                h->val = x->val;
                h->right = removeMin(h->right);
            }
            else
            {
                h->right = remove(h->right, key);
            }
        }

        return balance(h);
    }

    Node *select(Node *x, int k)
    {
        if (x == nullptr)
            return nullptr;

        int t = size(x->left);
        if (t > k)
            return select(x->left, k);
        else if (t < k)
            return select(x->right, k - t - 1);
        else
            return x;
    }

    int height(Node *x)
    {
        if (x == nullptr)
            return -1;

        return 1 + std::max(height(x->right), height(x->left));
    }

public:
    LLRB() : root(nullptr) {}

    void put(Key key, Value val)
    {
        root = put(root, key, val);
        root->color = BLACK;
    }

    Value get(Key key)
    {
        Node *x = root;

        while (x != nullptr)
        { // Search loop until key is found or null
            if (key < x->key)
                x = x->left; // Move left if key is smaller
            else if (key > x->key)
                x = x->right; // Move right if key is larger
            else
                return x->val; // Return value if key matches
        }

        throw std::out_of_range("Value Not Found"); // Throw exception if key is not in tree
    }

    size_t size()
    {
        return size(root);
    }

    int rank(Key key)
    {
        return rank(key, root);
    }

    Key Floor(Key key)
    {
        Node *x = Floor(root, key);
        if (x == nullptr)
            throw std::out_of_range("No floor exists for the given key");
        return x->key;
    }

    Key Ceil(Key key)
    {
        Node *x = Ceil(root, key);
        if (x == nullptr)
            throw std::out_of_range("No ceiling exists for the given key");
        return x->key;
    }

    std::vector<Key> keys()
    {
        std::vector<Key> keyList;
        inorder(root, keyList);
        return keyList;
    }

    int height()
    {
        return root->height;
    }

    void removeMax()
    {
        if (root == nullptr)
            throw std::out_of_range("Symbol table underflow");
        root = removeMax(root);
        if (root != nullptr)
            root->color = BLACK;
    }

    void removeMin()
    {
        if (root == nullptr)
            throw std::out_of_range("Symbol table underflow");
        root = removeMin(root);
        if (root != nullptr)
            root->color = BLACK;
    }

    void remove(const Key &key)
    {
        if (root == nullptr)
            throw std::out_of_range("Symbol table underflow");
        root = remove(root, key);
        if (root != nullptr)
            root->color = BLACK;
    }

    Key min()
    { // Returns the smallest key in the BST.
        if (root == nullptr)
            throw std::out_of_range("called min() with empty symbol table");
        Node *x = root;
        while (x->left != nullptr)
            x = x->left;
        return x->key;
    }

    Key max()
    {
        if (root == nullptr)
            throw std::out_of_range("called max() with empty symbol table");
        Node *traverse = root;
        while (traverse->right != nullptr)
        {
            traverse = traverse->right;
        }
        return traverse->key; // Return the maximum key
    }

    Key select(int k)
    { // Returns the key with a specified rank k.
        if (k < 0 || k >= size())
            throw std::out_of_range("called select() with invalid argument");

        Node *x = select(root, k);
        return x->key;
    }

    Value &operator[](const Key &key)
    { // Accesses or inserts the value for a given key. If the key doesn't exist, it inserts a new node with a default value.
        if (root == nullptr)
            root = new Node(key, Value());

        Node *x = root;
        while (true)
        {
            if (key < x->key)
            {
                if (x->left == nullptr)
                    x->left = new Node(key, Value());
                x = x->left;
            }
            else if (x->key < key)
            {
                if (x->right == nullptr)
                    x->right = new Node(key, Value());
                x = x->right;
            }
            else
                return x->val;
        }
    }
};