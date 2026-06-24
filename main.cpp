#include <iostream>

#include "Arbol.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"

int main()
{
    Nodo* raiz = new Nodo();

    raiz->tablero = Tablero(3, 3);
    raiz->turnoActual = Color::Blanca;

    // Rey negro
    raiz->piezas.push_back(Ficha(1, TipoFicha::Rey, Color::Negra, {0, 2}));

    // Torre blanca atacante
    raiz->piezas.push_back(Ficha(2, TipoFicha::Torre, Color::Blanca, {2, 0}));

    // Torre blanca de control
    raiz->piezas.push_back(Ficha(3, TipoFicha::Peon, Color::Blanca, {2, 1}));
    // ARBOL
    // ======================================================
    Arbol arbol;
    arbol.setNodoInicial(raiz);


    // ======================================================
    // VISUALIZAR ARBOL
    // ======================================================

    std::cout << "\n=== NIVEL 1 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();
    arbol.resumenNivel();

    std::cout << "\n=== NIVEL 2 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();
    arbol.resumenNivel();

    
    std::cout << "\n=== NIVEL 3 ===\n";
    arbol.construirSiguienteNivel();
    //arbol.imprimirNivel();
    arbol.resumenNivel();

    std::cout << "\n=== NIVEL 4 ===\n";
    arbol.construirSiguienteNivel();
    //arbol.imprimirNivel();
    arbol.resumenNivel();
    
    
    
     std::cout << "\n=== NIVEL 5 ===\n";
    arbol.construirSiguienteNivel();
    //arbol.imprimirNivel();
    arbol.resumenNivel();
    


    
    


    return 0;
}