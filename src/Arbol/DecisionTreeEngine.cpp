#include "DecisionTreeEngine.h"
#include <iostream>

// ======================================================

DecisionTreeEngine::DecisionTreeEngine()
{
    std::cout << "[DTE] Engine iniciado\n";
}

// ======================================================

const std::vector<Nodo*>& DecisionTreeEngine::getNodos() const
{
    return nodos;
}

// ======================================================
// EXPANDIR NODO (UNA SOLA PASADA LIMPIA)
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo)
    {
        std::cout << "[DTE] nodo NULL\n";
        return;
    }

    Color jugador = nodo->turnoActual;

    std::cout << "\n[DTE] expandiendo nodo | piezas="
              << nodo->piezas.size()
              << " turno="
              << (jugador == Color::Blanca ? "Blanca" : "Negra")
              << "\n";

    if (evaluator.estadoTerminal(*nodo, jugador))
    {
        std::cout << "[DTE] nodo terminal -> skip\n";
        return;
    }

    int hijos = 0;

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        auto movs = analyzer.obtenerMovimientosFicha(f, *nodo);

        std::cout << "[DTE] pieza ID=" << f.getId()
                  << " movs=" << movs.size() << "\n";

        for (const Posicion& p : movs)
        {
            if (!analyzer.esMovimientoLegal(*nodo, f, p))
                continue;

            Nodo nuevo = analyzer.simularMovimiento(*nodo, f, p);

            Nodo* hijo = new Nodo(nuevo);

            hijo->turnoActual =
                (jugador == Color::Blanca)
                    ? Color::Negra
                    : Color::Blanca;

            nodo->agregarHijo(hijo);

            hijos++;
        }
    }

    std::cout << "[DTE] hijos generados=" << hijos << "\n";
}