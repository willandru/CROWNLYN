#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveExecutor.h"

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

void DecisionTreeEngine::expandirNodo(
    Nodo* nodo
)
{
    if (!nodo)
        return;

    //==================================================
    // VALIDACIÓN DE ESTADO
    //==================================================

    if (
        m_evaluator.estadoTerminal(
            *nodo,
            nodo->turnoActual
        )
    )
    {
        return;
    }

    //==================================================
    // RECORRER PIEZAS DEL TURNO ACTUAL
    //==================================================

    for (const Ficha& ficha : nodo->piezas)
    {
        if (ficha.getColor() != nodo->turnoActual)
            continue;

        //==================================================
        // GENERAR MOVIMIENTOS
        //==================================================

        std::vector<Posicion> movimientos =
            MoveGenerator::getMovimientos(
                ficha,
                *nodo
            );

        //==================================================
        // CREAR HIJOS
        //==================================================

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



void DecisionTreeEngine::imprimirRama(
    const Nodo* nodo
) const
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
            << "Nodo "
            << n
            << " | turno: "
            << (n->turnoActual == Color::Blanca ? "Blancas" : "Negras")
            << " | piezas: "
            << n->piezas.size()
            << " | hijos: "
            << n->hijos.size()
            << '\n';
    }

    std::cout << "==============================\n";
}