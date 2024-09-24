/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <algorithm>
template <class K, class V>
V BST<K, V>::find(const K& key)
{
 if (find(root, key) == NULL){
        return V(); 
    }
    return (find(root,key))->value;
}
template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if(subtree == NULL){ return subtree;}

    else if(subtree->key == key){
        return subtree;
    }
    else if(subtree->key < key){
        return(find(subtree->right, key));
    }
    return(find(subtree->left,key));
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
      insert(root,key,value);    
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{

    Node *& temp = find (subtree,key);
    if (temp == NULL){
         temp = new Node(key,value);
    }

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    Node *& temp = first;
    first->key = second->key;
    first->value = second->value;

    second->key = temp->key;
    second->value = temp->value;

    // you can also use this:
    // std::swap(first->key, second->key);
    // std::swap(first->value, second->value);
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root,key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
if (subtree == nullptr) return; 

    if (key < subtree->key) { 
        remove(subtree->left, key);
    } else if (key > subtree->key) { 
        remove(subtree->right, key);
    } else { 
        
        if (subtree->left == nullptr && subtree->right == nullptr) {
            delete subtree;
            subtree = nullptr;
        }
        
        else if (subtree->left == nullptr) { 
            Node* temp = subtree;
            subtree = subtree->right;
            delete temp;
        } else if (subtree->right == nullptr) { 
            Node* temp = subtree;
            subtree = subtree->left;
            delete temp;
        }
       
        else {
            Node* inorderpre = subtree->left;
            while (inorderpre->right != nullptr) {
                inorderpre = inorderpre->right;
            }
            
            std::swap(subtree->key, inorderpre->key);
            std::swap(subtree->value, inorderpre->value);
            remove(subtree->left, inorderpre->key);
        }
    }
    }

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> histogram;
    for(unsigned int i = 0; i < inList.size();i++){
        histogram.insert(inList.at(i).first,inList.at(i).second);
    }
    return histogram;

}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> histogram;
    std::sort(inList.begin(), inList.end());
     do {
        BST<K, V> bst = listBuild(inList);
        int h = bst.height();
        if (h >= static_cast<int>(histogram.size())) {
            histogram.resize(h + 1, 0); 
        }
        histogram[h]++; 
    } while (std::next_permutation(inList.begin(), inList.end()));
    return histogram;
}