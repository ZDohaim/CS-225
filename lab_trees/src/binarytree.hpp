/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{   
  BTmirror(root);
}
template<typename T>
void BinaryTree<T>::BTmirror(Node* subroot){
    if(subroot == NULL){
        return;
    }
    BTmirror(subroot->right);
    BTmirror(subroot->left);

    auto *temp = subroot->left;
    subroot->left = subroot->right;
    subroot->right = temp;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const

   
    //    if (!root) return true;

    // std::stack<Node*> stack;
    // Node* current = root;
    // T lastVal;
    // bool isFirst = true;

    // while (!stack.empty() || current != nullptr) {
    //     while (current != nullptr) {
    //         stack.push(current);
    //         current = current->left; 
    //     }

    //     current = stack.top();
    //     stack.pop();

    //     if (!isFirst && lastVal >= current->elem) {
    //         return false;
    //     }
    //     lastVal = current->elem; 
    //     isFirst = false;

    //     current = current->right; 
    // }

    // return true;

  {
    if (!root){
    return true;
    } 

    InorderTraversal<T> t(root);
    typename TreeTraversal<T>::Iterator it = t.begin();    
    T prev = (*it)->elem;
    

    for (it = t.begin(); it != t.end(); it = ++it){
        if ((*it)->elem < prev) {
            return false; 
        }
        prev = (*it)->elem;
    }

    return true; 
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
   return recursive(root, NULL, NULL );

// std::vector<T> Vector;
// inOrder(Vector); //in-order population

// for(size_t i = 1 ; i < Vector.size(); i++){
//     if(Vector[i-1] > Vector[i]){
//         return false;
//     }
// }
// return true;
}
template <typename T>
bool BinaryTree<T>::recursive(Node* subroot, Node* Min, Node* Max) const {
    if(subroot == NULL){
        return true;
    }

   if((Min != NULL && subroot->elem <= Min->elem) || ( Max != NULL && subroot->elem >= Max->elem)){
    return false;
   }

   return recursive(subroot->left, Min, subroot) && recursive(subroot->right, subroot, Max);
    
}