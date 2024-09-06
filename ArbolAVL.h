#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "Nodo.h"
#include <iostream>
#include <queue>

template <class T>
class ArbolAVL {
protected:
    Nodo<T> *raiz;

public:
    ArbolAVL();
    ArbolAVL(T val);
    ~ArbolAVL();

    bool esVacio();
    T datoRaiz();
    Nodo<T>* obtenerRaiz();
    void cambiarRaiz(Nodo<T>* nodo);
    int altura();
    int altura(Nodo<T>* nodo);
    unsigned int tamano();
    unsigned tamano(Nodo<T>* nodo);
    bool insertarNodo(T n);
    bool deleteNodo(T n);
    bool buscar(T n);
    void preOrden();
    void preOrden(Nodo<T>* nodo);
    void inOrden();
    void inOrden(Nodo<T>* nodo);
    void posOrden();
    void posOrden(Nodo<T>* nodo);
    void nivelOrden();
    Nodo<T>* extremo_izq();
    Nodo<T>* extremo_der();

    void balancear(T val, Nodo<T>** nodo);
    Nodo<T>* giroDerecha(Nodo<T> *&padre);
    Nodo<T>* giroIzquierda(Nodo<T> *&padre);
    Nodo<T> * giroIzquierdaDerecha(Nodo<T> *&padre);
    Nodo<T> * giroDerechaIzquierda(Nodo<T> *&padre);
};

#endif // ARBOLAVL_H