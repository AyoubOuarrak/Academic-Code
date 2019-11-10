#include <iostream>

template <typename T>
template <typename U>
T*
Stack<T>::make_copy(const U* src, size_type src_size, size_type dst_capacity) {
  assert(dst_capacity >= src_size);
  // Allochiamo la risorsa.
  T* dst = new T[dst_capacity];
  try {
    // Proviamo a copiare gli elementi da `src' a `dest'.
    for (size_type i = 0; i < src_size; ++i)
      dst[i] = src[i];
  }
  catch (...) {
    // Qualcosa e` andato storto.
    // Deallochiamo la risorsa ...
    delete[] dst;
    // ... e rilanciamo l'eccezione per essere neutrali.
    throw;
  }
  return dst;
}

template <typename T>
bool
Stack<T>::OK() const {
  if (capacity_ == 0) {
#ifndef NDEBUG
    std::cerr << "Lo Stack e` dichiarato avere una capacita` nulla!"
	      << std::endl;
#endif // NDEBUG
    return false;
  }
  if (size_ > capacity_) {
#ifndef NDEBUG
    std::cerr << "Lo Stack e` dichiarato avere una dimensione "
	      << "superiore alla capacita`!" << std::endl;
#endif // NDEBUG
    return false;
  }
  if (vec_ == 0) {
#ifndef NDEBUG
    std::cerr << "Non vi sono risorse allocate per lo Stack!"
	      << std::endl;
#endif // NDEBUG
    return false;
  }
  // Tutto ok.
  return true;
}
