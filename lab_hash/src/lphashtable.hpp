/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */

    (void) key;   // prevent warnings... When you implement this function, remove this line.
    (void) value; // prevent warnings... When you implement this function, remove this line.    
 elems++;
    if(shouldResize()){
        resizeTable();
    }
    int ind = hashes::hash(key,size);
    for(unsigned int i =0;i < size;i++){
        ind = (ind+i)%size;
        if(table[ind]==NULL){
            should_probe[ind]= true;
            table[ind] = new std::pair<K,V>(key,value);
            break;
        }
    }
    
}


template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
     int index = findIndex(key);
     if(index!=-1 && table[index]!=NULL){
        delete table[index];
        table[index]=NULL;
        elems--;
     }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    int ind = hashes::hash(key,size);
    while((table[ind]!=NULL&&table[ind]->first!=key) && should_probe[ind]){
        ind++;
        ind = ind%size;
    }
    if(should_probe[ind]==false||table[ind]==NULL){
        return -1;
    }
    if(table[ind]->first==key){
        return ind;
    }

    
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     auto size2 = findPrime(size*2);
     std::pair<K, V> **table2=new std::pair<K, V>*[size2];
     delete[] should_probe;
     should_probe = new bool[size2];
     for(unsigned int i = 0; i < size2;i++){
        table2[i]=NULL;
        should_probe[i]= false;
     }
     for(unsigned int i = 0 ;i < size;i++){
        if(table[i]!=NULL){
            int ind = hashes::hash(table[i]->first,size2);
            for(unsigned int j=0;j < size2;j++){
                ind = (ind+j)%size2;
                if(table2[ind]==NULL){
                    should_probe[ind]= true;
                    table2[ind] = new std::pair<K,V>(table[i]->first,table[i]->second);
                    break;
                }
            }
            
        }
     }
     for(unsigned int i = 0 ;i < size;i++){
        if(table[i]!=NULL){
            delete table[i];
        }
     }
     delete[] table;
     table = table2;
     size = size2;
}