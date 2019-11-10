#ifndef EXCEPTION_SAFE_STACK_INLINES_HH_INCLUDE_GUARD
#define EXCEPTION_SAFE_STACK_INLINES_HH_INCLUDE_GUARD 1

#include <cassert>

// Metodi classe Stack_Impl.

inline
Stack_Impl::Stack_Impl(size_type capacity)
  : vec_(static_cast<T*>(
	        operator new(sizeof(T)*(capacity == 0 ? 16 : capacity)))
                        ),
    size_(0),
    capacity_(capacity == 0 ? 16 : capacity) {
  // NOTA: l'uso di `operator new' (e del cast statico) consente di
  // separare l'allocazione della memoria grezza dalla sua inizializzazione.
  // Qui allochiamo la memoria per `capacity' elementi, ma nessuno di
  // questi viene inizializzato (ovvero, costruito).
}

inline void
Stack_Impl::swap(Stack_Impl& y) {
  std::swap(vec_, y.vec_);
  std::swap(size_, y.size_);
  std::swap(capacity_, y.capacity_);
}


// Metodi classe Stack.

inline
Stack::Stack(size_type capacity)
  : impl(capacity) {
}

inline
Stack::~Stack() {
}

inline Stack&
Stack::operator=(const Stack& y) {
  if (this != &y) {
    Stack temp(y);
    swap(temp);
  }
  return *this;
}

inline void
Stack::pop() {
  assert(impl.size_ > 0);
  --impl.size_;
  // Nota: invocazione esplicita del distruttore di T.
  // Distruggiamo l'oggetto, ma non deallochiamo la memoria grezza
  // corrispondente in vec_.
  impl.vec_[impl.size_].~T();
}

inline void
Stack::swap(Stack& y) {
  impl.swap(y.impl);
}


inline const T&
Stack::top() const {
  assert(impl.size_ > 0);
  return impl.vec_[impl.size_-1];
}

inline T&
Stack::top() {
  assert(impl.size_ > 0);
  return impl.vec_[impl.size_-1];
}

inline Stack::size_type
Stack::size() const {
  return impl.size_;
}

inline bool
Stack::is_empty() const {
  return size() == 0;
}

inline bool
Stack::OK() const {
  return impl.OK();
}

#endif // EXCEPTION_SAFE_STACK_INLINES_HH_INCLUDE_GUARD
