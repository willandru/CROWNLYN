#include <iostream>

#include "Arbol.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"

int main()
{
    Nodo* raiz = new Nodo();

    // Estado del mundo
    raiz->tablero = Tablero(3, 3);
    raiz->turnoActual = Color::Blanca;

    // piezas iniciales
    raiz->piezas.push_back(Ficha(TipoFicha::Rey,   Color::Negra,  {0, 2}));
    raiz->piezas.push_back(Ficha(TipoFicha::Torre, Color::Blanca, {2, 0}));
    raiz->piezas.push_back(Ficha(TipoFicha::Peon,  Color::Blanca, {2, 1}));

    Arbol arbol;
    arbol.setNodoInicial(raiz);

    std::cout << "\n=== NIVEL 1 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();

    std::cout << "\n=== NIVEL 2 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();

    std::cout << "\n=== NIVEL 3 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();

    return 0;
}