#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveExecutor.h"
#include "NodeEncoder.h"

#include <iostream>
#include <vector>

//==================================================
// CONSTRUCTOR
//==================================================

DecisionTreeEngine::DecisionTreeEngine()
{
}

//==================================================
// EXPANSIÓN DE NODO
//==================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo)
        return;

    // Estado terminal
    if (m_evaluator.estadoTerminal(*nodo, nodo->turnoActual))
        return;

    // Seguridad básica contra explosión del árbol
    if (nodo->hijos.size() > 200)
        return;

    //==================================================
    // GENERACIÓN DE MOVIMIENTOS
    //==================================================

    for (const Ficha& ficha : nodo->piezas)
    {
        if (ficha.getColor() != nodo->turnoActual)
            continue;

        auto movimientos =
            MoveGenerator::getMovimientos(ficha, *nodo);

        for (const Posicion& destino : movimientos)
        {
            Nodo* hijo =
                MoveExecutor::crearNodoMovimiento(
                    *nodo,
                    ficha.getId(),
                    destino
                );

            if (!hijo)
                continue;

            nodo->agregarHijo(hijo);
        }
    }
}

//==================================================
// IMPRESIÓN DE RAMA
//==================================================

void DecisionTreeEngine::imprimirRama(const Nodo* nodo) const
{
    if (!nodo)
        return;

    std::vector<const Nodo*> rama;

    const Nodo* actual = nodo;

    while (actual)
    {
        rama.push_back(actual);
        actual = actual->padre;
    }

    std::cout << "\n==============================\n";
    std::cout << "RAMA ACTUAL\n";
    std::cout << "==============================\n";

    for (auto it = rama.rbegin(); it != rama.rend(); ++it)
    {
        const Nodo* n = *it;

        std::cout
            << "Nodo: " << n
            << " | turno: "
            << (n->turnoActual == Color::Blanca ? "Blancas" : "Negras")
            << " | piezas: " << n->piezas.size()
            << " | hijos: " << n->hijos.size()
            << '\n';

        //==================================================
        // BITBOARD COMPLETO
        //==================================================

        uint64_t bb = NodeEncoder::obtenerBitboardCompleto(*n);

        std::cout
            << "[BB] "
            << NodeEncoder::bitboardToHex(bb)
            << '\n';

        //==================================================
        // MOVIMIENTO (padre -> hijo)
        //==================================================

        if (n->padre)
        {
            std::cout
                << "Move: "
                << NodeEncoder::obtenerMovimiento(*n->padre, *n)
                << '\n';
        }
        else
        {
            std::cout << "Move: ROOT\n";
        }

        std::cout << "------------------------------\n";
    }

    std::cout << "==============================\n";
}