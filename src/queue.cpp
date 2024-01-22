/**
 ******************************************************************************
 * @file           : queue.cpp
 * @author         : koarz
 * @date           : 2024/1/22
 ******************************************************************************
 */
#include "queue.h"
// 在这里实现类的所有函数

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

template <typename T>
bool operator==(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {}

template <typename T>
bool operator>(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {}

template <typename T>
bool operator>=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {}

template <typename T>
bool operator<(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {}

template <typename T>
bool operator<=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {}

template <typename T>
bool operator!=(const rbc::queue<T> &lhs, const rbc::queue<T> &rhs) {}
