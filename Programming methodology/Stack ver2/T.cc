#include "T.hh"

#include <cassert>
#include <stdexcept>
#include <iostream>

int T::num_current_objects = 0;

void
T::register_object(int id) {
  if (num_current_objects == max_num_objects) {
    std::cerr << "TROPPI OGGETTI!!!!" << std::endl;
    throw std::invalid_argument("Troppi oggetti!");
  }
  else {
    std::cerr << "   Creato id = " << id
	      << " (attualmente ne abbiamo " << (num_current_objects+1) << ")"
	      << std::endl;
    ++num_current_objects;
  }
}

void
T::unregister_object(int id) {
  assert(num_current_objects > 0);
  --num_current_objects;
  std::cerr << "   Distrutto id = " << id
	    << " (ve ne sono ancora " << num_current_objects << ")"
	    << std::endl;
}

int
T::next_id() {
  static int next_id_ = 0;
  return next_id_++;
}

T::T()
  : id_(next_id()), s_() {
  register_object(id_);
}

T::T(const T& y)
  : id_(next_id()), s_(y.s_) {
  register_object(id_);
}

T::T(const char* s)
  : id_(next_id()), s_(s) {
  register_object(id_);
}

T&
T::operator=(const T& y) {
  s_ = y.s_;
  return *this;
}

T::~T() {
  try {
    // unregister_object() scrive su std::cerr.
    // Questa operazione di output, fatta a solo scopo didattico,
    // se non opportunamente mascherata dal try/catch potrebbe
    // causare comportamento scorretto in presenza di eccezioni.
    unregister_object(id_);
  }
  catch (...) {
    // I distruttori non devono MAI lasciar propagare eventuali
    // eccezioni da loro generate.
  }
}

bool
operator==(const T& x, const T& y) {
  return x.s_ == y.s_;
}

