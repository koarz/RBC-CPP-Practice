#pragma once

namespace rbc {
template <typename T> class forward_list;
template <typename T> struct forward_list_node {
  T data_{};
  forward_list_node<T> *next_node_{nullptr};

  forward_list_node<T>() = default;
  forward_list_node<T>(T val) { data_ = val; }
  ~forward_list_node<T>() { delete next_node_; }
};

} // namespace rbc

template <typename T> class rbc::forward_list {
  forward_list_node<T> head_;
  unsigned int max_size_{1000000000};
  static forward_list_node<T> for_no_initialized_node;

public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = value_type &;
  using const_reference = const value_type &;

  forward_list<T>() = default;
  ~forward_list<T>() = default;
  forward_list<T> &operator=(const rbc::forward_list<T> &other);
  forward_list<T> &operator=(rbc::forward_list<T> &&other) noexcept;
  const_reference front() const;
  reference front();
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type max_size() const;
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
      this_head->next_node_ = new forward_list_node<T>();
    }
    if (this_head->next_node_)
      this_head = this_head->next_node_;
  }
  if (max_size() > other.max_size()) {
    delete this_head->next_node_;
    this_head->next_node_ = nullptr;
  }
  max_size_ = other.max_size();
  return *this;
}
RBC_FORWARD_LIST &
rbc::forward_list<T>::operator=(rbc::forward_list<T> &&other) noexcept {
  delete head_.next_node_;
  head_.next_node_ = other.head_.next_node_;
  max_size_ = other.max_size();
  other.head_.next_node_ = nullptr;
  return *this;
}

RBC_FORWARD_LIST_REF_V::front() { return head_.next_node_->data_; }

RBC_FORWARD_LIST_C_REF_V::front() const { return head_.next_node_->data_; }

template <typename T> bool rbc::forward_list<T>::empty() const {
  return head_.next_node_ == nullptr;
}

template <typename T>
typename rbc::forward_list<T>::size_type
rbc::forward_list<T>::max_size() const {
  return max_size_;
}

RBC_FORWARD_LIST_VOID::push_front(rbc::forward_list<T>::const_reference value) {
  if (!head_.next_node_) {
    head_.next_node_ = new forward_list_node<T>(value);
  } else {
    auto node = head_.next_node_;
    head_.next_node_ = new forward_list_node<T>(value);
    head_.next_node_->next_node_ = node;
  }
}

RBC_FORWARD_LIST_VOID::pop_front() {
  if (!head_.next_node_) {
    return;
  }
  if (!head_.next_node_->next_node_) {
    delete head_.next_node_;
    head_.next_node_ = nullptr;
  } else {
    auto node = head_.next_node_;
    head_.next_node_ = node->next_node_;
    node->next_node_ = nullptr;
    delete node;
  }
}

RBC_FORWARD_LIST_VOID::swap(rbc::forward_list<T> &other) {
  auto temp = head_.next_node_;
  head_.next_node_ = other.head_.next_node_;
  other.head_.next_node_ = temp;
  auto t_size = max_size_;
  max_size_ = other.max_size();
  other.max_size_ = t_size;
}

RBC_FORWARD_LIST_VOID::resize(size_type count, const value_type &value) {
  size_type cnt = 0;
  auto node = head_.next_node_;
  while (node) {
    cnt++;
    if (node->next_node_) {
      node = node->next_node_;
    }
    if (cnt > count) {
      node = nullptr;
    }
  }
  if (cnt < count) {
    auto x = count - cnt;
    for (unsigned int i = 0; i < x; i++) {
      push_front(value);
    }
  }
}

RBC_FORWARD_LIST_VOID::insert_after(iterator<T> pos, const_reference value) {
  auto node = pos.node_->next_node_;
  pos.node_->next_node_ = new forward_list_node<T>(value);
  pos.node_->next_node_->next_node_ = node;
}

RBC_FORWARD_LIST_VOID::erase_after(iterator<T> first, iterator<T> last) {
  auto node = first.node_->next_node_;
  while (node != last.node_) {
    auto it = node;
    node = node->next_node_;
    delete it;
  }
  first.node_->next_node_ = last.node_;
}

RBC_FORWARD_LIST_VOID::clear() noexcept {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
typename rbc::forward_list<T>::template iterator<T>
rbc::forward_list<T>::begin() {
  return iterator<T>();
}

template <typename T>
typename rbc::forward_list<T>::template iterator<T>
rbc::forward_list<T>::end() {
  return iterator<T>();
}
