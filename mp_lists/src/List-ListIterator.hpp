
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;
    ListNode *end_;
  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }
    ListIterator(ListNode* x, ListNode * y) : position_(x), end_(y) {; }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
       if (position_ != NULL) {
        position_ = position_->next;  }
    return *this;
}
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
       ListIterator  temp = position_;
    if (position_ != NULL) {
        position_ = position_->next;}
    return ListIterator(temp);
}

    // Pre-Decrement, --iter
    ListIterator& operator--() {
          // @TODO: graded in mp_lists part 1
          if (position_ != NULL) {
              position_ = position_->prev;
              return *this;
          }
          position_ = end_;
          return *this;
      }


    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in mp_lists part 1
        ListIterator temp = position_;
        if (position_ != NULL ) {
            position_ = position_->prev;
            return ListIterator(temp);}
        // position_ = prev;
        position_ = end_;
        return ListIterator(temp);
    }
    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
