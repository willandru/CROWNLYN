#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveExecutor.h"

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