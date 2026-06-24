#include "DecisionTreeEngine.h"
#include <iostream>

// ======================================================

DecisionTreeEngine::DecisionTreeEngine()
{
}

// ======================================================

const std::vector<Nodo*>& DecisionTreeEngine::getNodos() const
{
    return nodos;
}

// ======================================================
// EXPANSIÓN DEL ÁRBOL
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo)
        return;

    Color jugador = nodo->turnoActual;

    // ==================================================
    // FILTRO DE ESTADO TERMINAL
    // ==================================================

    if (evaluator.estadoTerminal(*nodo, jugador))
        return;

    int hijos = 0;

    // ==================================================
    // ITERAR PIEZAS
    // ==================================================

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        // obtener movimientos base de la pieza
        auto movs = analyzer.obtenerMovimientosFicha(f, *nodo);

        for (const Posicion& p : movs)
        {
            // validar legalidad (evitar dejar rey en jaque)
            if (!analyzer.esMovimientoLegal(*nodo, f, p))
                continue;

            // simular estado resultante
            Nodo nuevo = analyzer.simularMovimiento(*nodo, f, p);

            // crear hijo
            Nodo* hijo = new Nodo(nuevo);

            // alternar turno
            hijo->turnoActual =
                (jugador == Color::Blanca)
                ? Color::Negra
                : Color::Blanca;

            nodo->agregarHijo(hijo);

            nodos.push_back(hijo);

            hijos++;
        }
    }

    std::cout << "[DTE] nodo expandido hijos=" << hijos << "\n";
}