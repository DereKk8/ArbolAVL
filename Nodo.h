#ifndef ARBOLAVL_NODO_H
#define ARBOLAVL_NODO_H
#include <iostream>
#include <list>

template< class T >
class Nodo
{
protected:
    T dato;
    Nodo<T> *hijoIzq;
    Nodo<T> *hijoDer;

public:
    Nodo();
    T& obtenerDato();
    void fijarDato(T& val);
    Nodo<T>*& obtenerHijoIzq();
    Nodo<T>*& obtenerHijoDer();
    void fijarHijoIzqNULL();
    void fijarHijoDerNULL();
    void fijarHijoIzq(Nodo<T> *izq);
    void fijarHijoDer(Nodo<T> *der);
    void limpiar();
    bool esHoja();
    unsigned int cantHijos();
};

#endif // ARBOLAVL_NODO_H