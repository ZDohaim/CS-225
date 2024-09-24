/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
    ListNode* destroy = head_; 
    while (destroy != NULL) {
        head_ = head_->next;
        delete destroy;
        destroy = head_;
    }
    head_ = NULL; 
    tail_ = NULL;
    length_ = 0; 
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = NULL;

  if (head_ == NULL) {
   head_ = newNode;
   tail_ = newNode;
  } else {
  
  newNode->next = head_;
  head_ ->prev = newNode;
  head_ = newNode;
  }

  ++length_;
}


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;

   if (head_ == NULL) {
   head_ = newNode;
   tail_ = newNode;
  } else {
  
  tail_ -> next = newNode;
  newNode ->prev = tail_;
  tail_ = newNode;
  }

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
ListNode* curr = start;

    if (splitPoint == 0 || start == NULL) {
      return start;
  }
  // if (splitPoint > length_){
  //   return NULL;
  // }

  for (int i = 0; (i < splitPoint) && (curr != NULL); i++) {
    curr = curr->next;
  }

  if (curr->prev != NULL && curr != NULL) {
      curr->prev->next = NULL; 
      curr->prev = NULL; 

}

return curr; 

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
     if (length_ < 3) return; 

    if (head_ == nullptr || head_->next == nullptr) {
    return;
  }
    ListNode* curr = head_;
    while (curr != NULL && curr->next != NULL && curr->next->next != NULL) {

        ListNode* move = curr->next;
        curr = curr->next->next;

        move->prev->next = move->next;
        move->next->prev = move->prev;


        tail_->next = move;
        move->prev = tail_;
        move->next = NULL;
        tail_ = move;

    }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint) {
    if (!startPoint || !endPoint) return; 

    ListNode *curr = startPoint;
    ListNode *prev = nullptr, *next = nullptr;

    while (prev != endPoint) {
        next = curr->next;
        curr->next = prev; 

        if (prev != NULL) {
            prev->prev = curr;
        }
        prev = curr; 
        curr = next; 
    }


    ListNode *tempStart = startPoint;
    startPoint = endPoint;
    endPoint = tempStart;


    if (startPoint->next != NULL) {
        startPoint->next->prev = startPoint;
    }

    if (endPoint->prev != NULL) {
        endPoint->prev->next = endPoint;
    }
}



/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
if (n <= 1 || n >= length_ || head_ == nullptr) {
    
  return; 
  }
if (n == 1) {
          reverse(head_, tail_);
    }
    ListNode* fake = new ListNode();
    fake->next = head_;
    ListNode* prevEnd = fake;

    while (prevEnd->next != nullptr) {
        ListNode* blockStart = prevEnd->next;
        ListNode* blockEnd = blockStart;

        int count = n-1;
       
        // for (int i = 0 ; i < count ; i++){
        //   blockEnd = blockEnd->next;
        // }
        
        while (count > 0 && blockEnd->next != nullptr) {
            blockEnd = blockEnd->next;
            count--;
        }

        ListNode* nextStart = blockEnd->next;
        ListNode* tempPrev = nextStart;
        ListNode* curr = blockStart;
        ListNode* tempNext = nullptr;

        while (curr != nextStart) {
            tempNext = curr->next;
            curr->next = tempPrev;
            tempPrev = curr;
            curr = tempNext;
        }
        prevEnd->next = tempPrev;
        prevEnd = blockStart;
    }

    head_ = fake->next;
    tail_ = fake; 
    while (tail_->next != nullptr) {
        tail_ = tail_->next;
    }

    delete fake; 
}
/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
      return;

}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  if(first == NULL){
    return second;
  } if ( second == NULL){
    return first;
  }
  ListNode * fakeHead = new ListNode;
  ListNode *curr = fakeHead;

  while( first != NULL && second != NULL){
    if (first->data < second->data){
      curr->next = first;
      first= first->next;
    } else {
      curr->next = second;
      second = second->next;
    }
    curr = curr->next;
  }

  if (first == NULL){
    curr->next = second;
  } else if(second == NULL){
    curr->next = first;
  }
  ListNode* mergedHead = fakeHead->next; 
  delete fakeHead;
  return mergedHead;

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
     if (start == nullptr || start->next == nullptr){
        return start;
    }
    ListNode* slow = start;
    ListNode* fast = start;
    ListNode* previous = NULL;
    
    while (fast != NULL && fast->next != NULL) {
        previous = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    previous->next = NULL; 
   
    ListNode* left = mergesort(start, chainLength / 2);
    ListNode* right = mergesort(slow, (chainLength + 1) / 2); 
    return merge(left, right);
}


