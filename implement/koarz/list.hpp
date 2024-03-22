#pragma once

namespace rbc {
template <typename T> class list;
template <typename T> struct list_node {
  T data_{};
  list_node<T> *pre_node_{nullptr};
  list_node<T> *next_node_{nullptr};

  list_node<T>() = default;
  ~list_node<T>() { delete next_node_; }
};
} // namespace rbc

template <typename T> class rbc::list {
  list_node<T> head_;
  list_node<T> tail_;
  unsigned int size_{0};
  static list_node<T> for_no_initialized_node;

public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = value_type &;
  using const_reference = const value_type &;

  list<T>() = default;
  ~list<T>() {
    delete head_.next_node_;
    head_.next_node_ = nullptr;
    tail_.next_node_ = nullptr;
  };
  list<T> &operator=(const rbc::list<T> &other);
  list<T> &operator=(rbc::list<T> &&other) noexcept;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  void push_front(const_reference value);
  void push_back(const_reference value);
  void pop_back();
  void pop_front();
  void swap(list &other) noexcept;
  void resize(size_type size, const value_type &value);

  // 迭代器部分
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
    iterator<U>(list_node<U> *node) : node_(node) {}
    list_node<U> *node_{nullptr};
  };
  void insert(iterator<T> pos, const_reference value);
  void erase(iterator<T> pos);
  iterator<T> begin();
  iterator<T> end();
};

#define RBC_LIST template <typename T> rbc::list<T>
#define RBC_LIST_REF_V                                                         \
  template <typename T> typename rbc::list<T>::reference rbc::list<T>
#define RBC_LIST_C_REF_V                                                       \
  template <typename T> typename rbc::list<T>::const_reference rbc::list<T>
#define RBC_LIST_VOID template <typename T> void rbc::list<T>

RBC_LIST &rbc::list<T>::operator=(const rbc::list<T> &other) {
  auto other_head = other.head_.next_node_;
  auto this_head = head_.next_node_;
  while (other_head) {
    if (!head_.next_node_) {
      head_.next_node_ = this_head = new list_node<T>();
    }
    this_head->data_ = other_head->data_;
    other_head = other_head->next_node_;
    if (!this_head->next_node_ && other_head) {
      this_head->next_node_ = new list_node<T>();
      this_head->next_node_->pre_node_ = this_head;
    }
    if (this_head->next_node_)
      this_head = this_head->next_node_;
  }
  if (size() > other.size()) {
    delete this_head->next_node_;
    this_head->next_node_ = nullptr;
  }
  tail_.next_node_ = this_head;
  size_ = other.size();
  return *this;
}

RBC_LIST &rbc::list<T>::operator=(rbc::list<T> &&other) noexcept {
  delete head_.next_node_;
  head_.next_node_ = other.head_.next_node_;
  tail_.next_node_ = other.tail_.next_node_;
  size_ = other.size();
  other.head_.next_node_ = nullptr;
  other.tail_.next_node_ = nullptr;
  other.size_ = 0;
  return *this;
}

RBC_LIST_REF_V::front() { return head_.next_node_->data_; }

RBC_LIST_C_REF_V::front() const { return head_.next_node_->data_; }

RBC_LIST_REF_V::back() { return tail_.next_node_->data_; }

RBC_LIST_C_REF_V::back() const { return tail_.next_node_->data_; }

template <typename T> bool rbc::list<T>::empty() const { return size_ == 0; }

template <typename T>
typename rbc::list<T>::size_type rbc::list<T>::size() const {
  return size_;
}

RBC_LIST_VOID::push_front(rbc::list<T>::const_reference value) {
  auto new_node = new list_node<T>();
  new_node->data_ = value;
  if (++size_ == 1) {
    tail_.next_node_ = new_node;
  } else {
    new_node->next_node_ = head_.next_node_;
    head_.next_node_->pre_node_ = new_node;
  }
  head_.next_node_ = new_node;
}

RBC_LIST_VOID::push_back(rbc::list<T>::const_reference value) {
  auto new_node = new list_node<T>();
  new_node->data_ = value;
  if (++size_ == 1) {
    head_.next_node_ = new_node;
  } else {
    new_node->pre_node_ = tail_.next_node_;
    tail_.next_node_->next_node_ = new_node;
  }
  tail_.next_node_ = new_node;
}

RBC_LIST_VOID::pop_front() {
  if (!head_.next_node_)
    return;
  auto node = head_.next_node_;
  if (--size_ == 0) {
    tail_.next_node_ = nullptr;
  } else {
    node->next_node_->pre_node_ = nullptr;
  }
  head_.next_node_ = node->next_node_;
  node->next_node_ = nullptr;
  delete node;
}

RBC_LIST_VOID::pop_back() {
  if (!tail_.next_node_)
    return;
  auto node = tail_.next_node_;
  if (--size_ == 0) {
    head_.next_node_ = nullptr;
  } else {
    node->pre_node_->next_node_ = nullptr;
  }
  tail_.next_node_ = node->pre_node_;
  delete node;
}

RBC_LIST_VOID::swap(list<T> &other) noexcept {
  auto temp = head_.next_node_;
  head_.next_node_ = other.head_.next_node_;
  other.head_.next_node_ = temp;
  temp = tail_.next_node_;
  tail_.next_node_ = other.tail_.next_node_;
  other.tail_.next_node_ = temp;
  auto t_size = size_;
  size_ = other.size();
  other.size_ = t_size;
}

RBC_LIST_VOID::resize(rbc::list<T>::size_type size, const value_type &value) {
  if (size == size_) {
    return;
  }
  size_type p = size - size_;
  if (size > size_) {
    for (int i = 0; i < p; i++) {
      push_back(value);
    }
  } else {
    for (int i = 0; i < -p; i++) {
      pop_back();
    }
  }
}

RBC_LIST_VOID::insert(rbc::list<T>::iterator<T> pos,
                      rbc::list<T>::const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else if (pos == end()) {
    push_back(value);
  } else {
    auto new_node = new list_node<T>;
    new_node->pre_node_ = pos.node_->pre_node_;
    new_node->next_node_ = pos.node_;
    new_node->data_ = value;
    pos.node_->pre_node_->next_node_ = new_node;
    pos.node_->pre_node_ = new_node;
    size_++;
  }
}

RBC_LIST_VOID::erase(rbc::list<T>::iterator<T> pos) {
  size_--;
  if (pos == begin()) {
    auto node = head_.next_node_;
    head_.next_node_ = node->next_node_;
    node->next_node_ = nullptr;
    delete node;
    if (size_ == 0) {
      tail_.next_node_ = nullptr;
    }
    return;
  }
  // 最后一个元素，且size一定大于1
  if (pos.node_ == tail_.next_node_) {
    auto node = tail_.next_node_;
    node->pre_node_->next_node_ = nullptr;
    tail_.next_node_ = node->pre_node_;
    delete node;
    return;
  }
  pos.node_->pre_node_->next_node_ = pos.node_->next_node_;
  pos.node_->next_node_ = nullptr;
  delete pos.node_;
}

template <typename T>
typename rbc::list<T>::template iterator<T> rbc::list<T>::begin() {
  return iterator<T>(head_.next_node_);
}

template <typename T>
typename rbc::list<T>::template iterator<T> rbc::list<T>::end() {
  return iterator<T>();
}
