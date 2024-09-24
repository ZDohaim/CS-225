/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <cmath>
template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent
    return std::floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return currentIdx*2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    //   as defined by higherPriority()

    if(rightChild(currentIdx) >= _elems.size()) {
        return leftChild(currentIdx);} 

    return (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))?leftChild(currentIdx):rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
  if(!hasAChild(currentIdx)){
    return;
  }
  auto childIdx = maxPriorityChild(currentIdx);
  if(_elems[childIdx] < _elems[currentIdx]){
    std::swap(_elems[childIdx] , _elems[currentIdx]);
    heapifyDown(childIdx);
  }

}
template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
if(currentIdx==1){
    return;
}

auto parentIdx = parent(currentIdx);
if(_elems[parentIdx] > _elems[currentIdx]){
    std::swap(_elems[parentIdx],_elems[currentIdx]);
    heapifyUp(parentIdx);
}

}
// auto theheap;
// for (int i =0; i < v.size(); i++){
//     theheap.insert(v[i]);
// }

// auto thevector;

// for(int i = 0 ; i < n ; i++){
//     auto temp theheap.remove();
//     thevector.pop_back(temp);
    
// }
// return thevector;

// auto <T>::remove();
// auto Value = _elems[1];
// _elems[1] = _elems[_elems.size()-1];
// _elems.pop_back();
// heapifyDown(1);
// return Value;

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    //  not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(unsigned int i = 0;i <elems.size();i++){
        _elems.push_back(elems.at(i));
    }
 
    for(unsigned i = _elems.size()-1; i >=1;i--){
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T toret =  _elems.at(root());
    std::swap(_elems[root()],_elems[_elems.size()-1]);
    _elems.pop_back();
    if(_elems.size()>1){
        heapifyDown(1);
    }
    return toret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return  _elems.at(root());
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    heapifyUp(idx);
    heapifyDown(idx);
    
    
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() < 2;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
