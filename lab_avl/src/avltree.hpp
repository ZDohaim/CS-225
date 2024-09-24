/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t) {
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)

    Node* tempR = t->right;
    t->right = tempR->left;
    tempR->left = t;

    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));

    tempR->height = 1 + std::max(heightOrNeg1(tempR->left), heightOrNeg1(tempR->right));

    t = tempR; // Make tempR the new root of this subtree
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t) {
    functionCalls.push_back("rotateRight");
    
    Node* tempR = t->left;
    t->left = tempR->right;
    tempR->right = t;

    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));

    t = tempR;

    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}


template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree) {
    if(subtree == nullptr) {
        return;
    }

    int balanceFactor = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);

    if (balanceFactor > 1) {
        if (heightOrNeg1(subtree->left->left) >= heightOrNeg1(subtree->left->right)) {
            rotateRight(subtree);
        }
        else {
            rotateLeftRight(subtree);
        }
    }
    else if (balanceFactor < -1) {
        if (heightOrNeg1(subtree->right->right) >= heightOrNeg1(subtree->right->left)) {
            rotateLeft(subtree);
        }
        else {
            rotateRightLeft(subtree);
        }
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value) {
    if (subtree == nullptr) {
        subtree = new Node(key, value);
    } else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else if (key > subtree->key) {
            insert(subtree->right, key, value);
        } 
    }

    rebalance(subtree);
}


template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key) {
 if (subtree == nullptr) {
        return; 
    }

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == nullptr || subtree->right == nullptr) {
            Node* temp = subtree->left ? subtree->left : subtree->right;

            if (temp == nullptr) {
                temp = subtree;
                subtree = nullptr;
            } else {
                *subtree = *temp; 
            }
            
            delete temp;
        } else {
            Node* temp = (subtree->left);
                    while (temp->right!= nullptr) {
                temp = temp->right;
                    }

            subtree->key = temp->key;
            subtree->value = temp->value;

            remove(subtree->left, temp->key);
        }
    }

    rebalance(subtree);
}
