#ifndef EXCEPTION_SAFE_STACK_INLINES_HH_INCLUDE_GUARD
#define EXCEPTION_SAFE_STACK_INLINES_HH_INCLUDE_GUARD 1

#include <algorithm>
#include <cassert>

template <typename T>
inline
Stack<T>::Stack(const size_type capacity)
  : vec_(new T[capacity == 0 ? 16 : capacity]),
    capacity_(capacity == 0 ? 16 : capacity),
    size_(0) {
  // NOTA: la capacita` deve essere maggiore di 0.
  assert(OK());
}

template <typename T>
inline
Stack<T>::Stack(const Stack& y)
  : vec_(make_copy(y.vec_, y.size_, (y.size_ == 0) ? 1 : y.size_)),
    capacity_((y.size_ == 0) ? 1 : y.size_),
    size_(y.size_) {
  // NOTA: la capacita` deve essere maggiore di 0. Si e` deciso di
  // impostarla uguale alla dimensione dello stack copiato.
  assert(OK());
}

template <typename T>
template <typename U>
inline
Stack<T>::Stack(const Stack<U>& y)
  : vec_(make_copy(y.vec_, y.size_, (y.size_ == 0) ? 1 : y.size_)),
    capacity_((y.size_ == 0) ? 1 : y.size_),
    size_(y.size_) {
  // NOTA: la capacita` deve essere maggiore di 0. Si e` deciso di
  // impostarla uguale alla dimensione dello stack copiato.
  assert(OK());
}

template <typename T>
inline
Stack<T>::~Stack() {
  delete[] vec_;
}

template <typename T>
inline void
Stack<T>::swap(Stack& y) {
  std::swap(vec_, y.vec_);
  std::swap(size_, y.size_);
  std::swap(capacity_, y.capacity_);
}

template <typename T>
inline Stack<T>&
Stack<T>::operator=(const Stack& y) {
  if (this != &y) {
    // Costruisco una copia di y e la scambio con this.
    Stack temp(y);
    swap(temp);
  }
  return *this;
}

template <typename T>
inline typename Stack<T>::size_type
Stack<T>::size() const {
  return size_;
}

template <typename T>
inline bool
Stack<T>::is_empty() const {
  return size() == 0;
}

template <typename T>
inline const T&
Stack<T>::top() const {
  // NOTA: e` responsabilita` del chiamante assicurarsi che
  // lo stack contenga almeno un elemento.
  assert(size_ > 0);
  return vec_[size_ - 1];
}

template <typename T>
inline T&
Stack<T>::top() {
  // NOTA: e` responsabilita` del chiamante assicurarsi che
  // lo stack contenga almeno un elemento.
  assert(size_ > 0);
  return vec_[size_ - 1];
}

template <typename T>
inline void
Stack<T>::push(const T& elem) {
  if (size_ == capacity_) {
    // Devo espandere la struttura dati.
    size_type new_capacity = 2*size_ + 1;
    T* temp = make_copy(vec_, size_, new_capacity);
    // Da qui (e fino alla fine del blocco) ho solo operazioni
    // che non possono lanciare eccezioni.
    delete[] vec_;
    vec_ = temp;
    capacity_ = new_capacity;
  }
  vec_[size_] = elem;
  ++size_;
  assert(OK());
}

template <typename T>
inline void
Stack<T>::pop() {
  // NOTA: e` responsabilita` del chiamante assicurarsi che
  // lo stack contenga almeno un elemento.
  assert(size_ > 0);
  --size_;
  assert(OK());
}

#endif // EXCEPTION_SAFE_STACK_INLINES_HH_INCLUDE_GUARD
