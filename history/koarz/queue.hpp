#pragma once

namespace rbc {
template <typename T> class queue;
template <typename T> struct basic_queue {
  basic_queue<T> *next{nullptr};
  T data;
  basic_queue<T>() = default;
  ~basic_queue<T>() { delete next; }
};
} // namespace rbc

template <typename T> class rbc::queue {
  // 这里可以添加数据成员，保证它们是private的，例如 T head什么的
  basic_queue<T> front_;
  basic_queue<T> back_;
  unsigned int size_{0};

public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = T &;
  using const_reference = const T &;

  queue<T>() = default;
  ~queue<T>() {
    delete front_.next;
    front_.next = nullptr;
    back_.next = nullptr;
  }
  queue<T> &operator=(const rbc::queue<T> &other);
  queue<T> &operator=(rbc::queue<T> &&other) noexcept;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  void push(const_reference value);
  void push(value_type &&value);
  void pop();
  void swap(queue &other) noexcept;
  template <typename U>
  friend bool operator==(const rbc::queue<U> &lhs, const rbc::queue<U> &rhs);
  template <typename U>
  friend bool operator>(const rbc::queue<U> &lhs, const rbc::queue<U> &rhs);
  template <typename U>
  friend bool operator>=(const rbc::queue<U> &lhs, const rbc::queue<U> &rhs);
  template <typename U>
  friend bool operator<(const rbc::queue<U> &lhs, const rbc::queue<U> &rhs);
  template <typename U>
  friend bool operator<=(const rbc::queue<U> &lhs, const rbc::queue<U> &rhs);
  template <typename U>
  friend bool operator!=(const rbc::queue<U> &lhs, const rbc::queue<U> &rhs);
};

#define RBC_QUEUE template <typename T> rbc::queue<T>
#define RBC_QUEUE_REF_V                                                        \
  template <typename T> typename rbc::queue<T>::reference rbc::queue<T>
#define RBC_QUEUE_C_REF_V                                                      \
  template <typename T> typename rbc::queue<T>::const_reference rbc::queue<T>
#define RBC_QUEUE_VOID template <typename T> void rbc::queue<T>

RBC_QUEUE &rbc::queue<T>::operator=(const rbc::queue<T> &other) {
  // copy all of other's data
  auto other_front = other.front_.next;
  auto this_front = front_.next;
  while (other_front) {
    if (!front_.next) {
      front_.next = this_front = new basic_queue<T>();
    }
    this_front->data = other_front->data;
    other_front = other_front->next;
    if (!this_front->next && other_front) {
      this_front->next = new basic_queue<T>();
    }
    if (this_front->next)
      this_front = this_front->next;
  }
  if (size() > other.size()) {
    delete this_front->next;
    this_front->next = nullptr;
  }
  back_.next = this_front;
  size_ = other.size();
  return *this;
}

RBC_QUEUE &rbc::queue<T>::operator=(rbc::queue<T> &&other) noexcept {
  delete front_.next;
  front_.next = other.front_.next;
  back_.next = other.back_.next;
  size_ = other.size();
  other.front_.next = nullptr;
  other.back_.next = nullptr;
  other.size_ = 0;
  return *this;
}

RBC_QUEUE_REF_V::front() { return front_.next->data; }

RBC_QUEUE_C_REF_V::front() const { return front_.next->data; }

RBC_QUEUE_REF_V::back() { return back_.next->data; }

RBC_QUEUE_C_REF_V::back() const { return back_.next->data; }

template <typename T> bool rbc::queue<T>::empty() const { return size_ == 0; }

template <typename T>
typename rbc::queue<T>::size_type rbc::queue<T>::size() const {
  return size_;
}

RBC_QUEUE_VOID::push(rbc::queue<T>::value_type &&value) {
  auto temp = back_.next;
  back_.next = new basic_queue<T>();
  back_.next->data = value;
  if (!front_.next) {
    front_.next = back_.next;
  } else {
    temp->next = back_.next;
  }
  size_++;
}

RBC_QUEUE_VOID::push(rbc::queue<T>::const_reference value) {
  auto temp = back_.next;
  back_.next = new basic_queue<T>();
  back_.next->data = value;
  if (!front_.next) {
    front_.next = back_.next;
  } else {
    temp->next = back_.next;
  }
  size_++;
}

RBC_QUEUE_VOID::pop() {
  if (front_.next) {
    auto temp = front_.next;
    front_.next = temp->next;
    temp->next = nullptr;
    delete temp;
    if (--size_ == 0) {
      back_.next = nullptr;
    }
  }
}

RBC_QUEUE_VOID::swap(queue<T> &other) noexcept {
  auto temp = front_.next;
  front_.next = other.front_.next;
  other.front_.next = temp;
  temp = back_.next;
  back_.next = other.back_.next;
  other.back_.next = temp;
  auto t_size = size_;
  size_ = other.size();
  other.size_ = t_size;
}

namespace rbc {
template <typename T>
bool operator==(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  rbc::queue<T> temp1, temp2;
  temp1 = lhs;
  temp2 = rhs;
  if (temp1.size() != temp2.size()) {
    return false;
  }
  while (!temp1.empty()) {
    if (temp1.front() != temp2.front()) {
      return false;
    }
    temp1.pop();
    temp2.pop();
  }
  return true;
}

template <typename T>
bool operator>(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  rbc::queue<T> temp1, temp2;
  temp1 = lhs;
  temp2 = rhs;
  while (!temp1.empty() && !temp2.empty()) {
    if (temp1.front() < temp2.front()) {
      return false;
    } else if (temp1.front() > temp2.front()) {
      return true;
    }
    temp1.pop();
    temp2.pop();
  }
  return temp1.size() > temp2.size();
}

template <typename T>
bool operator>=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return lhs > rhs || lhs == rhs;
}

template <typename T>
bool operator<(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  rbc::queue<T> temp1, temp2;
  temp1 = lhs;
  temp2 = rhs;
  while (!temp1.empty() && !temp2.empty()) {
    if (temp1.front() > temp2.front()) {
      return false;
    } else if (temp1.front() > temp2.front()) {
      return true;
    }
    temp1.pop();
    temp2.pop();
  }
  return temp1.size() < temp2.size();
}

template <typename T>
bool operator<=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator!=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return !(lhs == rhs);
}
} // namespace rbc
