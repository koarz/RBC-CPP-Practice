#pragma once

namespace rbc {
template <typename T> class stack;
}

template <typename T> class rbc::stack {

public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = T &;
  using const_reference = const T &;

  stack<T>() = default;
  ~stack<T>() = default;
  stack<T> &operator=(const rbc::stack<T> &other);
  stack<T> &operator=(rbc::stack<T> &&other) noexcept;
  reference top();
  const_reference top() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  void push(const_reference value);
  void push(value_type &&value);
  void pop();
  void swap(stack &other) noexcept;
  template <typename U>
  friend bool operator==(const rbc::stack<U> &lhs, const rbc::stack<U> &rhs);
  template <typename U>
  friend bool operator>(const rbc::stack<U> &lhs, const rbc::stack<U> &rhs);
  template <typename U>
  friend bool operator>=(const rbc::stack<U> &lhs, const rbc::stack<U> &rhs);
  template <typename U>
  friend bool operator<(const rbc::stack<U> &lhs, const rbc::stack<U> &rhs);
  template <typename U>
  friend bool operator<=(const rbc::stack<U> &lhs, const rbc::stack<U> &rhs);
  template <typename U>
  friend bool operator!=(const rbc::stack<U> &lhs, const rbc::stack<U> &rhs);
};

#define RBC_STACK template <typename T> rbc::stack<T>
#define RBC_STACK_REF_V                                                        \
  template <typename T> typename rbc::stack<T>::reference rbc::stack<T>
#define RBC_STACK_C_REF_V                                                      \
  template <typename T> typename rbc::stack<T>::const_reference rbc::stack<T>
#define RBC_STACK_VOID template <typename T> void rbc::stack<T>

RBC_STACK &rbc::stack<T>::operator=(const rbc::stack<T> &other) {}
RBC_STACK &rbc::stack<T>::operator=(rbc::stack<T> &&other) noexcept {}

RBC_STACK_REF_V::top() {}

RBC_STACK_C_REF_V::top() const {}

template <typename T> bool rbc::stack<T>::empty() const {}

template <typename T>
typename rbc::stack<T>::size_type rbc::stack<T>::size() const {}

RBC_STACK_VOID::push(rbc::stack<T>::value_type &&value) {}

RBC_STACK_VOID::push(rbc::stack<T>::const_reference value) {}

RBC_STACK_VOID::pop() {}

RBC_STACK_VOID::swap(stack<T> &other) noexcept {}

namespace rbc {
template <typename T>
bool operator==(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return false;
}

template <typename T>
bool operator>(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return false;
}

template <typename T>
bool operator>=(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return false;
}

template <typename T>
bool operator<(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return false;
}

template <typename T>
bool operator<=(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return false;
}

template <typename T>
bool operator!=(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return false;
}
} // namespace rbc