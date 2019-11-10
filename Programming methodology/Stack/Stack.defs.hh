#ifndef EXCEPTION_SAFE_STACK_DEFS_HH_INCLUDE_GUARD
#define EXCEPTION_SAFE_STACK_DEFS_HH_INCLUDE_GUARD 1

#include <cstddef>
#include "T.hh"

//! Una pila espandibile.
/*!
  Una struttura dati pila che si espande automaticamente al bisogno.
  L'implementazione assicura il livello <EM>strong</EM> di correttezza
  rispetto alle eccezioni, sotto le seguenti condizioni:
   - il tipo T fornisce il costruttore di default e l'operatore
     di assegnamento per copia;
   - il distruttore di T non lancia eccezioni;
   - l'operatore di assegnamento di T e` exception safe;
*/
class Stack {
public:
  //! Un tipo intero senza segno adatto per le dimensioni.
  typedef std::size_t size_type;

  //! Costruttore di default.
  explicit Stack(size_type capacity = 16);

  //! Costruttore di copia.
  Stack(const Stack& y);

  //! Assegnamento.
  Stack& operator=(const Stack& y);

  //! Distruttore (non lancia eccezioni).
  ~Stack();

  //! Scambio efficiente e senza eccezioni.
  void swap(Stack& y);

  //! Mette una copia di \p elem in cima alla pila.
  void push(const T& elem);

  //! Rimuove il primo elemento della pila.
  void pop();

  //! Test di stack vuoto.
  bool is_empty() const;

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
  //! Puntatore alla memoria che contiene la pila.
  T* vec_;

  /*! \brief
    La capacita' attuale della pila (ovvero, il numero di elementi
    allocati a partire dall'indirizzo \p vec_).
  */
  size_type capacity_;

  /*! \brief
    La dimensione attuale della pila (ovvero, il numero di elementi
    significativi memorizzati in \p vec_).
  */
  size_type size_;

  //! Funzione di supporto per la gestione corretta dell'allocazione risorse.
  static T* make_copy(const T* src,
		      size_type src_size,
		      size_type dst_capacity);
};

#include "Stack.inlines.hh"

#endif // EXCEPTION_SAFE_STACK_DEFS_HH_INCLUDE_GUARD
