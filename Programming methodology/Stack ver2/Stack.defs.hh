#ifndef EXCEPTION_SAFE_STACK_DEFS_HH_INCLUDE_GUARD
#define EXCEPTION_SAFE_STACK_DEFS_HH_INCLUDE_GUARD 1

#include <cstddef>
#include "T.hh"

//! Classe che si occupa dell'allocazione delle risorse per lo Stack.
class Stack_Impl {
public:
  //! Un tipo intero senza segno adatto per le dimensioni.
  typedef std::size_t size_type;

  /*! \brief
    Alloca la memoria sufficiente a contenere \p capacity elementi di tipo T.
  */
  explicit Stack_Impl(size_type capacity);

  /*! \brief
    Distrugge il numero di elementi di tipo T specificato da \p size_
    e quindi dealloca la memoria.
  */
  ~Stack_Impl();

  //! Scambia le rappresentazioni senza lanciare eccezioni.
  void swap(Stack_Impl& y);

  //! Controlla l'invariante della classe.
  bool OK() const;

  //! Punta alla memoria allocata per \p capacity_ elementi di tipo T.
  T* vec_;
  //! Numero di elementi di tipo T attualmente costruiti in \p vec_.
  size_type size_;
  //! Capacita` massima di \p vec_.
  size_type capacity_;

private:
  // Privato e non implementato: la copia non e` consentita.
  Stack_Impl(const Stack_Impl&);
  // Privato e non implementato: l'assegnamento non e` consentito.
  Stack_Impl& operator=(const Stack_Impl&);
};

//! Una pila espandibile.
class Stack {
public:
  //! Utilizzo il tipo definito in Stack_Impl.
  typedef Stack_Impl::size_type size_type;

  //! Costruttore di default.
  Stack(size_type capacity = 16);

  //! Costruttore di copia.
  Stack(const Stack& y);

  //! Assegnamento.
  Stack& operator=(const Stack& y);

  //! Distruttore.
  ~Stack();

  //! Scambio efficiente e senza eccezioni.
  void swap(Stack& y);

  //! Mette una copia di \p elem in cima alla pila.
  void push(const T& elem);

  //! Elimina il primo elemento della pila.
  /*!
    Si assume che la pila non sia vuota. In caso di pila vuota
    il comportamento e` indefinito.
  */
  void pop();

  //! Accesso in lettura/scrittura al primo elemento.
  /*!
    Si assume che la pila non sia vuota. In caso di pila vuota
    il comportamento e` indefinito.
  */
  T& top();

  //! Accesso in sola lettura al primo elemento.
  /*!
    Si assume che la pila non sia vuota. In caso di pila vuota
    il comportamento e` indefinito.
  */
  const T& top() const;

  //! Test di stack vuoto.
  bool is_empty() const;

  //! Numero di elementi sullo stack.
  size_type size() const;

  //! Controlla l'invariante della classe.
  /*!
    \return
    <CODE>true</CODE> se l'invariante di classe e` soddisfatta;
    <CODE>false</CODE>, altrimenti.

    Utile per il debugging.
  */
  bool OK() const;

private:
  //! L'implementazione dello Stack.
  Stack_Impl impl;
};


#include "Stack.inlines.hh"

#endif // EXCEPTION_SAFE_STACK_DEFS_HH_INCLUDE_GUARD
