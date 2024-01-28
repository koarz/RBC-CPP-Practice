/**
 ******************************************************************************
 * @file           : queue.h
 * @author         : Koarz
 * @date           : 2024/1/22
 ******************************************************************************
 */

#pragma once

namespace rbc {
template <typename T> class queue;
} // namespace rbc

template <typename T> class rbc::queue {
  // 这里可以添加数据成员，保证它们是private的，例如 T head什么的

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

RBC_QUEUE &rbc::queue<T>::operator=(const rbc::queue<T> &other) {}
RBC_QUEUE &rbc::queue<T>::operator=(rbc::queue<T> &&other) noexcept {}

RBC_QUEUE_REF_V::front() {}

RBC_QUEUE_C_REF_V::front() const {}

RBC_QUEUE_REF_V::back() {}

RBC_QUEUE_C_REF_V::back() const {}

template <typename T> bool rbc::queue<T>::empty() const {}

template <typename T>
typename rbc::queue<T>::size_type rbc::queue<T>::size() const {}

RBC_QUEUE_VOID::push(rbc::queue<T>::value_type &&value) {}

RBC_QUEUE_VOID::push(rbc::queue<T>::const_reference value) {}

RBC_QUEUE_VOID::pop() {}

RBC_QUEUE_VOID::swap(queue<T> &other) noexcept {}

namespace rbc {
template <typename T>
bool operator==(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return false;
}

template <typename T>
bool operator>(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return false;
}

template <typename T>
bool operator>=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return false;
}

template <typename T>
bool operator<(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return false;
}

template <typename T>
bool operator<=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return false;
}

template <typename T>
bool operator!=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {
  return false;
}
} // namespace rbc
