#include <iostream>

#include "Arbol.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"

int main()
{
    // Nodo raíz
    Nodo* raiz = new Nodo();

    // Tablero 3x3 (configuración dinámica)
    raiz->tablero = Tablero(3, 3);

    // Turno inicial
    raiz->turnoActual = Color::Blanca;

    // Estado inicial

    // Rey negro en (0, 0)
    raiz->piezas.push_back(Ficha(TipoFicha::Rey, Color::Negra, {0, 0}));

    // Torre blanca en (2, 2)
    raiz->piezas.push_back(Ficha(TipoFicha::Torre, Color::Blanca, {2, 2}));

    // Peón blanco en (2, 1)
    raiz->piezas.push_back(Ficha(TipoFicha::Peon, Color::Blanca, {2, 1}));

    // Árbol
    Arbol arbol;
    arbol.setNodoInicial(raiz);

    // Expansión inicial
    arbol.construirSiguienteNivel();

    std::cout << "Crownlyn inicializado correctamente\n";

    return 0;
}