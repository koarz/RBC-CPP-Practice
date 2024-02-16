#pragma once

namespace rbc {
template <typename T> class list;
} // namespace rbc
template <typename T> class rbc::list {
public:
  using value_type = T;
  using size_type = unsigned int;
  using reference = value_type &;
  using const_reference = const value_type &;

  list<T>() = default;
  ~list<T>() = default;
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
    iterator<U>() = default;
    // 这几个是必须的，剩下自由发挥
    iterator<U> operator++() { return *this; }
    iterator<U> operator--() { return *this; }
    reference operator*() {
      T a;
      return a;
    }
    friend bool operator!=(const iterator<U> &lhs, const iterator<U> &rhs) {
      return false;
    }
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

RBC_LIST &rbc::list<T>::operator=(const rbc::list<T> &other) { return *this; }
RBC_LIST &rbc::list<T>::operator=(rbc::list<T> &&other) noexcept {
  return *this;
}

RBC_LIST_REF_V::front() {}

RBC_LIST_C_REF_V::front() const {}

RBC_LIST_REF_V::back() {}

RBC_LIST_C_REF_V::back() const {}

template <typename T> bool rbc::list<T>::empty() const { return true; }

template <typename T>
typename rbc::list<T>::size_type rbc::list<T>::size() const {
  return 0;
}

RBC_LIST_VOID::push_front(rbc::list<T>::const_reference value) {}

RBC_LIST_VOID::push_back(rbc::list<T>::const_reference value) {}

RBC_LIST_VOID::pop_front() {}

RBC_LIST_VOID::pop_back() {}

RBC_LIST_VOID::swap(list<T> &other) noexcept {}

RBC_LIST_VOID::resize(rbc::list<T>::size_type size, const value_type &value) {}

RBC_LIST_VOID::insert(rbc::list<T>::iterator<T> pos,
                      rbc::list<T>::const_reference value) {}

RBC_LIST_VOID::erase(rbc::list<T>::iterator<T> pos) {}

template <typename T>
typename rbc::list<T>::template iterator<T> rbc::list<T>::begin() {
  return iterator<T>();
}

template <typename T>
typename rbc::list<T>::template iterator<T> rbc::list<T>::end() {
  return iterator<T>();
}
