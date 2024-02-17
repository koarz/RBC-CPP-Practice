#pragma once

namespace rbc {
template <typename T> class stack;
template <typename T> struct basic_stack {
  T data;
  basic_stack<T> *next{nullptr};
  basic_stack<T> *pre{nullptr};
  basic_stack<T>() = default;
  ~basic_stack<T>() { delete next; }
};
} // namespace rbc

template <typename T> class rbc::stack {
  basic_stack<T> front_;
  basic_stack<T> back_;
  unsigned int size_{0};

public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = T &;
  using const_reference = const T &;

  stack<T>() = default;
  ~stack<T>() {
    delete front_.next;
    front_.next = nullptr;
    back_.next = nullptr;
  }
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

RBC_STACK &rbc::stack<T>::operator=(const rbc::stack<T> &other) {
  auto other_front = other.front_.next;
  auto this_front = front_.next;
  while (other_front) {
    if (!front_.next) {
      front_.next = this_front = new basic_stack<T>();
    }
    this_front->data = other_front->data;
    other_front = other_front->next;
    if (!this_front->next && other_front) {
      this_front->next = new basic_stack<T>();
      this_front->next->pre = this_front;
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

RBC_STACK &rbc::stack<T>::operator=(rbc::stack<T> &&other) noexcept {
  delete front_.next;
  front_.next = other.front_.next;
  back_.next = other.back_.next;
  size_ = other.size();
  other.front_.next = nullptr;
  other.back_.next = nullptr;
  other.size_ = 0;
  return *this;
}

RBC_STACK_REF_V::top() { return back_.next->data; }

RBC_STACK_C_REF_V::top() const { return back_.next->data; }

template <typename T> bool rbc::stack<T>::empty() const { return size_ == 0; }

template <typename T>
typename rbc::stack<T>::size_type rbc::stack<T>::size() const {
  return size_;
}

RBC_STACK_VOID::push(rbc::stack<T>::value_type &&value) {
  auto temp = back_.next;
  back_.next = new basic_stack<T>();
  back_.next->data = value;
  if (!front_.next) {
    front_.next = back_.next;
  } else {
    temp->next = back_.next;
    back_.next->pre = temp;
  }
  size_++;
}

RBC_STACK_VOID::push(rbc::stack<T>::const_reference value) {
  auto temp = back_.next;
  back_.next = new basic_stack<T>();
  back_.next->data = value;
  if (!front_.next) {
    front_.next = back_.next;
  } else {
    temp->next = back_.next;
    back_.next->pre = temp;
  }
  size_++;
}

RBC_STACK_VOID::pop() {

  if (back_.next) {
    auto temp = back_.next;
    back_.next = temp->pre;
    delete temp;
    if (--size_ == 0) {
      front_.next = nullptr;
    } else {
      back_.next->next = nullptr;
    }
  }
}

RBC_STACK_VOID::swap(stack<T> &other) noexcept {
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
bool operator==(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  rbc::stack<T> temp1, temp2;
  temp1 = lhs;
  temp2 = rhs;
  if (temp1.size() != temp2.size()) {
    return false;
  }
  while (!temp1.empty()) {
    if (temp1.front_.next->data != temp2.front_.next->data) {
      return false;
    }
    auto func = [](auto &temp1) {
      auto temp = temp1.front_.next;
      temp1.front_.next = temp->next;
      temp->next = nullptr;
      delete temp;
      temp1.size_--;
    };
    func(temp1);
    func(temp2);
  }
  return true;
}

template <typename T>
bool operator>(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  rbc::stack<T> temp1, temp2;
  temp1 = lhs;
  temp2 = rhs;
  while (!temp1.empty() && !temp2.empty()) {
    if (temp1.front_.next->data < temp2.front_.next->data) {
      return false;
    } else if (temp1.front_.next->data > temp2.front_.next->data) {
      return true;
    }
    auto func = [](auto &temp1) {
      auto temp = temp1.front_.next;
      temp1.front_.next = temp->next;
      temp->next = nullptr;
      delete temp;
      temp1.size_--;
    };
    func(temp1);
    func(temp2);
  }
  return temp1.size() > temp2.size();
}

template <typename T>
bool operator>=(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return lhs > rhs || lhs == rhs;
}

template <typename T>
bool operator<(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  rbc::stack<T> temp1, temp2;
  temp1 = lhs;
  temp2 = rhs;
  while (!temp1.empty() && !temp2.empty()) {
    if (temp1.front_.next->data > temp2.front_.next->data) {
      return false;
    } else if (temp1.front_.next->data < temp2.front_.next->data) {
      return true;
    }
    auto func = [](auto &temp1) {
      auto temp = temp1.front_.next;
      temp1.front_.next = temp->next;
      temp->next = nullptr;
      delete temp;
      temp1.size_--;
    };
    func(temp1);
    func(temp2);
  }
  return temp1.size() < temp2.size();
}

template <typename T>
bool operator<=(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator!=(const rbc::stack<T> &lhs, const rbc::stack<T> &rhs) {
  return !(lhs == rhs);
}
} // namespace rbc
