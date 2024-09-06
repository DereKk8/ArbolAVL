#include "Nodo.h"

template<class T>
Nodo<T>::Nodo() {
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template<class T>
T& Nodo<T>::obtenerDato() {
    return this->dato;
}

template<class T>
void Nodo<T>::fijarDato(T& val) {
    this->dato = val;
}

template <class T>
void Nodo<T>::limpiar() {
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template<class T>
Nodo<T>*& Nodo<T>::obtenerHijoIzq() {
    return this->hijoIzq;
}

template<class T>
Nodo<T>*& Nodo<T>::obtenerHijoDer() {
    return this->hijoDer;
}

template<class T>
void Nodo<T>::fijarHijoIzq(Nodo<T> *izq) {
    this->hijoIzq = izq;
}

template<class T>
void Nodo<T>::fijarHijoDer(Nodo<T> *der) {
    this->hijoDer = der;
}

template<class T>
void Nodo<T>::fijarHijoIzqNULL() {
    this->hijoIzq = nullptr;
}

template<class T>
void Nodo<T>::fijarHijoDerNULL() {
    this->hijoDer = nullptr;
}

template <class T>
bool Nodo<T>::esHoja() {
    return this->hijoDer == NULL && this->hijoIzq == NULL;
}

template <class T>
unsigned int Nodo<T>::cantHijos() {
    int cant = 0;
    if (this->hijoDer != NULL) {
        cant++;
    }
    if (this->hijoIzq != NULL) {
        cant++;
    }
    return cant;
}

// Explicit template instantiation
template class Nodo<int>;