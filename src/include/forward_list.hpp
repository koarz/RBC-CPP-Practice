#pragma once

namespace rbc {
template <typename T> class forward_list;
template <typename T> struct forward_list_node {
  T data_{0};
  forward_list_node<T> *next_node_{nullptr};
  forward_list_node<T>(T val) { data_ = val; }
  forward_list_node<T>() = default;
  ~forward_list_node<T>() { delete next_node_; }
};

} // namespace rbc

template <typename T> class rbc::forward_list {
  forward_list_node<T> head_;
  forward_list_node<T> tail_;
  unsigned int size_{0};
  static forward_list_node<T> for_no_initialized_node;

public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = value_type &;
  using const_reference = const value_type &;

  forward_list<T>() = default;
  ~forward_list<T>();
  forward_list<T> &operator=(const rbc::forward_list<T> &other);
  forward_list<T> &operator=(rbc::forward_list<T> &&other) noexcept;
  const_reference front() const;
  reference front();
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  void assign(size_type count, const T &value);
  void clear() noexcept;
  void push_front(const_reference value);
  void pop_front();
  void resize(size_type count, const value_type &value);
  void swap(forward_list &other);
  template <typename U> struct iterator {
    iterator<U> operator++() {
      node_ = node_->next_node_ ?: nullptr;
      return *this;
    }
    iterator<U> operator--() {
      node_ = node_->pre_node ?: nullptr;
      return *this;
    }
    reference operator*() { return node_->data_; }
    template <typename V>
    friend bool operator==(const iterator<V> &lhs, const iterator<V> &rhs) {
      return lhs.node_ == rhs.node_;
    }
    template <typename V>
    friend bool operator!=(const iterator<V> &lhs, const iterator<V> &rhs) {
      return lhs.node_ != rhs.node_;
    }
    iterator<U>() = default;
    iterator<U>(forward_list_node<U> *node) : node_(node) {}
    forward_list_node<U> *node_{nullptr};
  };
  void insert_after(iterator<T> pos, const_reference value);
  void erase_after(iterator<T> first, iterator<T> last);
  iterator<T> begin();
  iterator<T> end();
};

#define RBC_FORWARD_LIST template <typename T> rbc::forward_list<T>
#define RBC_FORWARD_LIST_REF_V                                                 \
  template <typename T>                                                        \
  typename rbc::forward_list<T>::reference rbc::forward_list<T>
#define RBC_FORWARD_LIST_C_REF_V                                               \
  template <typename T>                                                        \
  typename rbc::forward_list<T>::const_reference rbc::forward_list<T>
#define RBC_FORWARD_LIST_VOID template <typename T> void rbc::forward_list<T>

RBC_FORWARD_LIST &
rbc::forward_list<T>::operator=(const rbc::forward_list<T> &other) {
  auto other_head = other.head_.next_node_;
  auto this_head = head_.next_node_;
  while (other_head) {
    if (!head_.next_node_) {
      head_.next_node_ = this_head = new forward_list_node<T>();
    }
    this_head->data_ = other_head->data_;
    other_head = other_head->next_node_;
    if (!this_head->next_node_ && other_head) {
      this_head->next_node_ = new forward_list_node<T>(other_head->data_);
    }
    this_head = this_head->next_node_;
    if (this_head->next_node_ && !other_head) {
      auto it = this_head->next_node_;
      while (it) {
        auto itt = it;
        it = it->next_node_;
        delete itt;
      }
    }
  }
  size_ = other.size_;
  return *this;
}
RBC_FORWARD_LIST &
rbc::forward_list<T>::operator=(rbc::forward_list<T> &&other) noexcept {
  delete head_.next_node_;
  head_.next_node_ = other.head_.next_node_;
  tail_.next_node_ = other.tail_.next_node_;
  other.head_.next_node_ = nullptr;
  other.tail_.next_node_ = nullptr;
  return *this;
}

// template <typename T> rbc::forward_list<T>::forward_list() {}

template <typename T> rbc::forward_list<T>::~forward_list() {
  auto it = head_.next_node_;
  while (it != nullptr) {
    auto itt = it;
    it = it->next_node_;
    delete itt;
  }
}

RBC_FORWARD_LIST_REF_V::front() { return head_.next_node_->data_; }

RBC_FORWARD_LIST_C_REF_V::front() const { return head_.next_node_->data_; }

template <typename T> bool rbc::forward_list<T>::empty() const {
  return head_.next_node_ == nullptr;
}

template <typename T>
typename rbc::forward_list<T>::size_type rbc::forward_list<T>::size() const {
  return size_;
}

RBC_FORWARD_LIST_VOID::push_front(rbc::forward_list<T>::const_reference value) {
  auto it = head_.next_node_;
  head_.next_node_ = new forward_list_node<T>(value);
  head_.next_node_->next_node_ = it;
  size_++;
}

RBC_FORWARD_LIST_VOID::pop_front() {
  if (!head_.next_node_)
    return;
  auto node = head_.next_node_;
  if (--size_ == 0) {
    tail_.next_node_ = nullptr;
  }
  head_.next_node_ = node->next_node_;
  node->next_node_ = nullptr;
  delete node;
}

RBC_FORWARD_LIST_VOID::swap(rbc::forward_list<T> &other) {
  auto temp = head_.next_node_;
  head_.next_node_ = other.head_.next_node_;
  other.head_.next_node_ = temp;
  temp = tail_.next_node_;
  tail_.next_node_ = other.tail_.next_node_;
  other.tail_.next_node_ = temp;
  auto t_size = size_;
  size_ = other.size_;
  other.size_ = t_size;
}

RBC_FORWARD_LIST_VOID::resize(size_type count, const value_type &value) {
  if (count == size_) {
    return;
  } else if (count > size_) {
    size_ = count;
    for (unsigned int i = 0; i < count - size_; i++) {
      push_front(value);
    }
  } else {
    size_ = count;
    for (unsigned int i = 0; i < size_ - count; i++) {
      pop_front();
    }
  }
}

RBC_FORWARD_LIST_VOID::insert_after(iterator<T> pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else {
    auto new_node = new forward_list_node<T>;
    auto it = pos.next_node_;
    pos.next_node_ = new_node;
    new_node.next_node_ = it;
    new_node->data_ = value;
    size_++;
  }
}

RBC_FORWARD_LIST_VOID::erase_after(iterator<T> first, iterator<T> last) {
  for (auto i = first; i != last; i++) {
    size_--;
    delete i;
  }
  first.next_node_ = last;
}

RBC_FORWARD_LIST_VOID::clear() noexcept {
  size_ = 0;
  auto it = head_.next_node_;
  while (it != nullptr) {
    auto itt = it;
    it = it->next_node_;
    delete itt;
  }
}

template <typename T>
typename rbc::forward_list<T>::template iterator<T>
rbc::forward_list<T>::begin() {
  return iterator<T>(head_.next_node_);
}

template <typename T>
typename rbc::forward_list<T>::template iterator<T>
rbc::forward_list<T>::end() {
  return iterator<T>();
}
