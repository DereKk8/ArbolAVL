#include "ArbolAVL.h"
#include <iostream>
#include <queue>

template <class T>
ArbolAVL<T>::ArbolAVL() : raiz(NULL) {}

template <class T>
ArbolAVL<T>::ArbolAVL(T n) {
    Nodo<T>* nodo = new Nodo<T>;
    nodo->fijarDato(n);
    this->raiz = nodo;
}

template <class T>
ArbolAVL<T>::~ArbolAVL() {
    if (this->raiz != NULL) {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template <class T>
void ArbolAVL<T>::cambiarRaiz(Nodo<T>* nodo) {
    this->raiz = nodo;
}

template <class T>
Nodo<T>* ArbolAVL<T>::obtenerRaiz() {
    return this->raiz;
}

template <class T>
bool ArbolAVL<T>::esVacio() {
    return this->raiz == NULL;
}

template <class T>
T ArbolAVL<T>::datoRaiz() {
    return this->raiz->obtenerDato();
}

template <class T>
int ArbolAVL<T>::altura() {
    return this->esVacio() ? -1 : this->altura(this->obtenerRaiz());
}

template <class T>
int ArbolAVL<T>::altura(Nodo<T>* nodo) {
    if (nodo == NULL) return -1;
    if (nodo->esHoja()) return 0;
    int alt_izq = nodo->obtenerHijoIzq() ? altura(nodo->obtenerHijoIzq()) : -1;
    int alt_der = nodo->obtenerHijoDer() ? altura(nodo->obtenerHijoDer()) : -1;
    return (alt_izq > alt_der ? alt_izq : alt_der) + 1;
}

template <class T>
unsigned int ArbolAVL<T>::tamano() {
    return this->esVacio() ? 0 : this->tamano(this->obtenerRaiz());
}

template <class T>
unsigned int ArbolAVL<T>::tamano(Nodo<T>* nodo) {
    if (nodo->esHoja()) return 1;
    int tamano_izq = nodo->obtenerHijoIzq() ? tamano(nodo->obtenerHijoIzq()) : 0;
    int tamano_der = nodo->obtenerHijoDer() ? tamano(nodo->obtenerHijoDer()) : 0;
    return tamano_izq + tamano_der + 1;
}

template <class T>
bool ArbolAVL<T>::insertarNodo(T n) {
    if (this->raiz == NULL) {
        Nodo<T>* nodo = new Nodo<T>;
        nodo->fijarDato(n);
        this->raiz = nodo;
        return true;
    }
    Nodo<T>* nodo = this->raiz;
    Nodo<T>* padre = this->raiz;
    bool duplicado = false;
    while (nodo != NULL && !duplicado) {
        padre = nodo;
        if (n < nodo->obtenerDato()) nodo = nodo->obtenerHijoIzq();
        else if (n > nodo->obtenerDato()) nodo = nodo->obtenerHijoDer();
        else duplicado = true;
    }
    if (!duplicado) {
        Nodo<T>* nuevo = new Nodo<T>;
        nuevo->fijarDato(n);
        if (n > padre->obtenerDato()) padre->fijarHijoDer(nuevo);
        else padre->fijarHijoIzq(nuevo);
        balancear(n, &(this->raiz));
        return true;
    }
    return false;
}


template <class T>
bool ArbolAVL<T>::deleteNodo(T n) {
    if (this->esVacio()) return false;

    Nodo<T>* padre = nullptr;
    Nodo<T>* nodo = this->raiz;
    while (nodo != nullptr && nodo->obtenerDato() != n) {
        padre = nodo;
        if (n < nodo->obtenerDato()) nodo = nodo->obtenerHijoIzq();
        else nodo = nodo->obtenerHijoDer();
    }

    if (nodo == nullptr) return false;

    if (nodo->obtenerHijoIzq() == nullptr && nodo->obtenerHijoDer() == nullptr) {
        if (nodo == this->raiz) this->raiz = nullptr;
        else if (padre->obtenerHijoIzq() == nodo) padre->fijarHijoIzq(nullptr);
        else padre->fijarHijoDer(nullptr);
        delete nodo;
    } else if (nodo->obtenerHijoIzq() == nullptr || nodo->obtenerHijoDer() == nullptr) {
        Nodo<T>* child = nodo->obtenerHijoIzq() ? nodo->obtenerHijoIzq() : nodo->obtenerHijoDer();
        if (nodo == this->raiz) this->raiz = child;
        else if (padre->obtenerHijoIzq() == nodo) padre->fijarHijoIzq(child);
        else padre->fijarHijoDer(child);
        delete nodo;
    } else {
        Nodo<T>* successor = nodo->obtenerHijoDer();
        Nodo<T>* successorPadre = nodo;
        while (successor->obtenerHijoIzq() != nullptr) {
            successorPadre = successor;
            successor = successor->obtenerHijoIzq();
        }
        nodo->fijarDato(successor->obtenerDato());
        if (successorPadre->obtenerHijoIzq() == successor) successorPadre->fijarHijoIzq(successor->obtenerHijoDer());
        else successorPadre->fijarHijoDer(successor->obtenerHijoDer());
        delete successor;
    }

    balancear(n, &(this->raiz));
    return true;
}

template <class T>
void ArbolAVL<T>::balancear(T val, Nodo<T>** nodo) {
    if (*nodo == nullptr) return;

    if (val < (*nodo)->obtenerDato()) {
        balancear(val, &((*nodo)->obtenerHijoIzq()));
    } else if (val > (*nodo)->obtenerDato()) {
        balancear(val, &((*nodo)->obtenerHijoDer()));
    }

    int alturaHijoIzq = altura((*nodo)->obtenerHijoIzq());
    int alturaHijoDer = altura((*nodo)->obtenerHijoDer());

    if (alturaHijoIzq - alturaHijoDer > 1) {
        if (altura((*nodo)->obtenerHijoIzq()->obtenerHijoIzq()) >= altura((*nodo)->obtenerHijoIzq()->obtenerHijoDer())) {
            *nodo = giroDerecha(*nodo);
        } else {
            *nodo = giroIzquierdaDerecha(*nodo);
        }
    } else if (alturaHijoDer - alturaHijoIzq > 1) {
        if (altura((*nodo)->obtenerHijoDer()->obtenerHijoDer()) >= altura((*nodo)->obtenerHijoDer()->obtenerHijoIzq())) {
            *nodo = giroIzquierda(*nodo);
        } else {
            *nodo = giroDerechaIzquierda(*nodo);
        }
    }
}

template <class T>
Nodo<T>* ArbolAVL<T>::giroDerecha(Nodo<T>*& padre) {
    Nodo<T>* n_padre = padre->obtenerHijoIzq();
    padre->fijarHijoIzq(n_padre->obtenerHijoDer());
    n_padre->fijarHijoDer(padre);
    return n_padre;
}

template <class T>
Nodo<T>* ArbolAVL<T>::giroIzquierda(Nodo<T>*& padre) {
    Nodo<T>* n_padre = padre->obtenerHijoDer();
    padre->fijarHijoDer(n_padre->obtenerHijoIzq());
    n_padre->fijarHijoIzq(padre);
    return n_padre;
}

template <class T>
Nodo<T>* ArbolAVL<T>::giroIzquierdaDerecha(Nodo<T>*& padre) {
    Nodo<T>** nodo = &(padre->obtenerHijoIzq());
    padre->fijarHijoIzq(giroIzquierda(*nodo));
    return giroDerecha(padre);
}

template <class T>
Nodo<T>* ArbolAVL<T>::giroDerechaIzquierda(Nodo<T>*& padre) {
    Nodo<T>** nodo = &(padre->obtenerHijoDer());
    padre->fijarHijoDer(giroDerecha(*nodo));
    return giroIzquierda(padre);
}

template <class T>
bool ArbolAVL<T>::buscar(T n) {
    Nodo<T>* nodo = this->raiz;
    while (nodo != NULL) {
        if (n < nodo->obtenerDato()) nodo = nodo->obtenerHijoIzq();
        else if (n > nodo->obtenerDato()) nodo = nodo->obtenerHijoDer();
        else return true;
    }
    return false;
}

template <class T>
void ArbolAVL<T>::inOrden() {
    if (!this->esVacio()) this->inOrden(this->raiz);
}

template <class T>
void ArbolAVL<T>::inOrden(Nodo<T>* nodo) {
    if (nodo != NULL) {
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato() << " ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolAVL<T>::preOrden() {
    if (!this->esVacio()) this->preOrden(this->raiz);
}

template <class T>
void ArbolAVL<T>::preOrden(Nodo<T>* nodo) {
    if (nodo != NULL) {
        std::cout << nodo->obtenerDato() << " ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolAVL<T>::posOrden() {
    if (!this->esVacio()) this->posOrden(this->raiz);
}

template <class T>
void ArbolAVL<T>::posOrden(Nodo<T>* nodo) {
    if (nodo != NULL) {
        this->posOrden(nodo->obtenerHijoIzq());
        this->posOrden(nodo->obtenerHijoDer());
        std::cout << nodo->obtenerDato() << " ";
    }
}

template <class T>
void ArbolAVL<T>::nivelOrden() {
    if (!this->esVacio()) {
        std::queue<Nodo<T>*> aux;
        aux.push(this->obtenerRaiz());
        while (!aux.empty()) {
            std::cout << aux.front()->obtenerDato() << " ";
            if (aux.front()->obtenerHijoIzq() != NULL) aux.push(aux.front()->obtenerHijoIzq());
            if (aux.front()->obtenerHijoDer() != NULL) aux.push(aux.front()->obtenerHijoDer());
            aux.pop();
        }
    }
}

template <class T>
Nodo<T>* ArbolAVL<T>::extremo_izq() {
    Nodo<T>* nodo = this->raiz;
    while (nodo->obtenerHijoIzq() != NULL) nodo = nodo->obtenerHijoIzq();
    return nodo;
}

template <class T>
Nodo<T>* ArbolAVL<T>::extremo_der() {
    Nodo<T>* nodo = this->raiz;
    while (nodo->obtenerHijoDer() != NULL) nodo = nodo->obtenerHijoDer();
    return nodo;
}

// Explicit template instantiation
template class ArbolAVL<int>;