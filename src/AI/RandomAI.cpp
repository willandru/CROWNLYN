#include "RandomAI.h"

#include "Nodo.h"
#include "Ficha.h"
#include "MoveGenerator.h"
#include "MoveExecutor.h"

#include <vector>
#include <random>

//==================================================
// IA SIMPLE ALEATORIA
//==================================================

Nodo* RandomAI::jugar(Nodo* nodo)
{
    if (!nodo)
        return nullptr;

    //==================================================
    // 1. RECOLECTAR MOVIMIENTOS LEGALES
    //==================================================

    std::vector<std::pair<int, Posicion>> movimientos;

    for (const Ficha& ficha : nodo->piezas)
    {
        if (ficha.getColor() != nodo->turnoActual)
            continue;

        auto posibles =
            MoveGenerator::getMovimientos(ficha, *nodo);

        for (const Posicion& destino : posibles)
        {
            movimientos.push_back(
                { ficha.getId(), destino }
            );
        }
    }

    //==================================================
    // 2. SI NO HAY MOVIMIENTOS
    //==================================================

    if (movimientos.empty())
        return nullptr;

    //==================================================
    // 3. SELECCIÓN ALEATORIA
    //==================================================

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> dist(
        0,
        movimientos.size() - 1
    );

    auto elegido =
        movimientos[dist(gen)];

    int idFicha = elegido.first;
    const Posicion& destino = elegido.second;

    //==================================================
    // 4. CREAR NUEVO ESTADO
    //==================================================

    Nodo* nuevo =
        MoveExecutor::crearNodoMovimiento(
            *nodo,
            idFicha,
            destino
        );

    return nuevo;
}