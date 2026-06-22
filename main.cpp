#include <iostream>

#include "Arbol.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Rey.h"
#include "Torre.h"
#include "Peon.h"

int main()
{
    // 1. Nodo raíz
    Nodo* raiz = new Nodo();

    // 2. Tablero 3x3
    raiz->tablero = Tablero(3, 3);

    // 3. Turno inicial
    raiz->turnoActual = Color::Blanca;

    // 4. Crear piezas iniciales (estado base)

    // Rey negro en (1,0)
    Rey* reyNegro = new Rey(Color::Negra, {1, 0});
    raiz->piezas.push_back(reyNegro);

    // Torre blanca en (2,2)
    Torre* torreBlanca = new Torre(Color::Blanca, {2, 2});
    raiz->piezas.push_back(torreBlanca);

    // Peón blanco en (2,1)
    Peon* peonBlanco = new Peon(Color::Blanca, {2, 1});
    raiz->piezas.push_back(peonBlanco);

    // 5. Construcción del árbol
    Arbol arbol;
    arbol.construir(raiz, 1);

    std::cout << "Crownlyn inicializado correctamente (tablero 3x3)\n";

    return 0;
}