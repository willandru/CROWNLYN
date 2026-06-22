#include <iostream>

#include "Arbol.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"

int main()
{
    // 1. Nodo raíz
    Nodo* raiz = new Nodo();

    // 2. Tablero 3x3
    raiz->tablero = Tablero(3, 3);

    // 3. Turno inicial
    raiz->turnoActual = Color::Blanca;

    // 4. Crear piezas iniciales con posición (conceptual del sistema)

    // Rey negro en (1,3)
    Ficha reyNegro(TipoFicha::Rey, Color::Negra);
    reyNegro.setPosicion({1, 3});

    // Torre blanca en (3,1)
    Ficha torreBlanca(TipoFicha::Torre, Color::Blanca);
    torreBlanca.setPosicion({3, 1});

    // Peón blanco en (3,2)
    Ficha peonBlanco(TipoFicha::Peon, Color::Blanca);
    peonBlanco.setPosicion({3, 2});

    // 5. Insertar estado inicial en el nodo
    raiz->piezas.push_back(reyNegro);
    raiz->piezas.push_back(torreBlanca);
    raiz->piezas.push_back(peonBlanco);

    // 6. Crear árbol
    Arbol arbol;
    arbol.setNodoInicial(raiz);

    // 7. Expandir árbol inicial
    arbol.construirSiguienteNivel();

    std::cout << "Crownlyn inicializado correctamente (tablero 3x3)\n";

    return 0;
}