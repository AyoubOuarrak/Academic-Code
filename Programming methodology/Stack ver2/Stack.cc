#include "Stack.defs.hh"
#include <iostream>
#include <cassert>

Stack_Impl::~Stack_Impl() {
  // Distruggiamo gli elementi effettivamente presenti su vec_,
  // in ordine inverso rispetto a quello di costruzione.
  for (size_type i = size_; i-- > 0; )
    vec_[i].~T();
  // Deallochiamo la memoria.
  operator delete(vec_);
}

Stack::Stack(const Stack& y)
  : impl(y.impl.capacity_) {
  // Dopo avere allocato la memoria grezza necessaria,
  // utilizziamo la new di piazzamento per inizializzarla con le copie
  // degli elementi contenuti in y.
  for (size_type i = 0; i < y.impl.size_; ++i) {
    new (impl.vec_ + i) T(y.impl.vec_[i]);
    // E` importante che size_ venga aggiornato passo dopo passo:
    // in ogni momento deve dire con precisioni quanti sono gli elementi
    // effettivamente costruiti dentro a vec_.
    ++impl.size_;
  }
}

void
Stack::push(const T& elem) {
  if (impl.size_ < impl.capacity_) {
    // C'e` spazio a sufficienza:
    // new di piazzamento e incremento di size_.
    new (impl.vec_ + impl.size_) T(elem);
    ++impl.size_;
  }
  else {
    // Occorre riallocare lo Stack: creiamo un temporaneo e poi
    // facciamo lo scambio. In questo modo, se qualcosa va storto,
    // il temporaneo viene distrutto correttamente e lo Stack iniziale
    // non viene toccato.
    assert(impl.size_ == impl.capacity_);
    Stack temp(impl.capacity_ * 2 + 1);
    for (size_type i = 0; i < impl.size_; ++i)
      temp.push(impl.vec_[i]);
    temp.push(elem);
    swap(temp);
  }
}

bool
Stack_Impl::OK() const {
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
