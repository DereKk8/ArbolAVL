#include <iostream>
#include "ArbolAVL.h"


int main() {
    ArbolAVL<int> arbol;

    // Insert nodes
    arbol.insertarNodo(10);
    arbol.insertarNodo(20);
    arbol.insertarNodo(5);
    arbol.insertarNodo(6);
    arbol.insertarNodo(15);

    // Print tree in different orders
    std::cout << "In-Order: ";
    arbol.inOrden();
    std::cout << std::endl;

    std::cout << "Pre-Order: ";
    arbol.preOrden();
    std::cout << std::endl;

    std::cout << "Post-Order: ";
    arbol.posOrden();
    std::cout << std::endl;

    std::cout << "Level-Order: ";
    arbol.nivelOrden();
    std::cout << std::endl;

    // Search for nodes
    std::cout << "Buscar 15: " << (arbol.buscar(15) ? "Encontrado" : "No encontrado") << std::endl;
    std::cout << "Buscar 25: " << (arbol.buscar(25) ? "Encontrado" : "No encontrado") << std::endl;

    // Get height and size of the tree
    std::cout << "Altura del arbol: " << arbol.altura() << std::endl;
    std::cout << "Tamano del arbol: " << arbol.tamano() << std::endl;

    // Get leftmost and rightmost nodes
    Nodo<int>* extremoIzq = arbol.extremo_izq();
    if (extremoIzq != nullptr) {
        std::cout << "Nodo extremo izquierdo: " << extremoIzq->obtenerDato() << std::endl;
    } else {
        std::cout << "Nodo extremo izquierdo: NULL" << std::endl;
    }

    Nodo<int>* extremoDer = arbol.extremo_der();
    if (extremoDer != nullptr) {
        std::cout << "Nodo extremo derecho: " << extremoDer->obtenerDato() << std::endl;
    } else {
        std::cout << "Nodo extremo derecho: NULL" << std::endl;
    }



    arbol.deleteNodo(20);
    //arbol.deleteNodo(5);

    // Print tree after deletions
    std::cout << "In-Order after deletions: ";
    arbol.inOrden();
    std::cout << std::endl;

    testRotations();




    return 0;
}