#pragma once

#include "list.hpp"
#include <cstddef>
#include <forward_list>
#include <iostream>
#include <memory>
namespace rbc {
template <typename T> class forward_list;
} // namespace rbc

template <typename T> class rbc::forward_list {
public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using allocator_type = std::allocator<T>;

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
    // 这几个是必须的，剩下自由发挥
    iterator<U> operator++();
    iterator<U> operator--();
    reference operator*();
    friend bool operator!=(const iterator<U> &lhs,
                           const iterator<U> &rhs) noexcept;
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
rbc::forward_list<T>::operator=(const rbc::forward_list<T> &other) {}
RBC_FORWARD_LIST &
rbc::forward_list<T>::operator=(rbc::forward_list<T> &&other) noexcept {}

RBC_FORWARD_LIST_REF_V::front() {}

RBC_FORWARD_LIST_C_REF_V::front() const {}

template <typename T> bool rbc::forward_list<T>::empty() const {}

template <typename T>
typename rbc::forward_list<T>::size_type
rbc::forward_list<T>::max_size() const {}

RBC_FORWARD_LIST_VOID::push_front(rbc::forward_list<T>::const_reference value) {
}

RBC_FORWARD_LIST_VOID::pop_front() {}

RBC_FORWARD_LIST_VOID::swap(rbc::forward_list<T> &other) {}

RBC_FORWARD_LIST_VOID::resize(size_type count, const value_type &value) {}

RBC_FORWARD_LIST_VOID::insert_after(iterator<T> pos, const_reference value) {}

RBC_FORWARD_LIST_VOID::erase_after(iterator<T> first, iterator<T> last) {}

RBC_FORWARD_LIST_VOID::clear() noexcept {}

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

namespace rbc {
template <typename T>
bool operator==(const std::forward_list<T> &lhs,
                const std::forward_list<T> &rhs) {}
} // namespace rbc
