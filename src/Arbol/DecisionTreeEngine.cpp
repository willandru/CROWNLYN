#include "DecisionTreeEngine.h"

#include "Torre.h"
#include "Rey.h"
#include "Peon.h"

// ======================================================
// CONSTRUCTOR
// ======================================================

DecisionTreeEngine::DecisionTreeEngine() {}

// ======================================================
// EXPANSIÓN
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo) return;

    Color jugador = nodo->turnoActual;

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        auto movimientos = obtenerMovimientosFicha(f, *nodo);

        for (const Posicion& p : movimientos)
        {
            if (!esMovimientoLegal(*nodo, f, p))
                continue;

            Nodo* hijo = new Nodo(*nodo);

            *hijo = simularMovimiento(*nodo, f, p);

            hijo->turnoActual =
                (jugador == Color::Blanca)
                ? Color::Negra
                : Color::Blanca;

            nodo->agregarHijo(hijo);
        }
    }
}

// ======================================================
// MOVIMIENTOS
// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerMovimientosFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    switch (f.getTipo())
    {
        case TipoFicha::Torre:
            return Torre().getMovimientos(f, estado);

        case TipoFicha::Rey:
            return Rey().getMovimientos(f, estado);

        case TipoFicha::Peon:
            return Peon().getMovimientos(f, estado);

        default:
            return {};
    }
}

// ======================================================
// SIMULACIÓN (ID-BASED)
// ======================================================

Nodo DecisionTreeEngine::simularMovimiento(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo copia = estado;

    int id = ficha.getId();

    // 1. eliminar pieza en destino (si existe)
    for (auto it = copia.piezas.begin(); it != copia.piezas.end(); )
    {
        if (it->getPosicion().x == destino.x &&
            it->getPosicion().y == destino.y)
        {
            it = copia.piezas.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // 2. mover por ID
    for (Ficha& f : copia.piezas)
    {
        if (f.getId() == id)
        {
            f.setPosicion(destino);
            break;
        }
    }

    return copia;
}

// ======================================================
// VALIDACIÓN
// ======================================================

bool DecisionTreeEngine::esMovimientoLegal(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo simulado = simularMovimiento(estado, ficha, destino);
    return !estaEnJaque(simulado, ficha.getColor());
}

// ======================================================
// JAQUE
// ======================================================

bool DecisionTreeEngine::estaEnJaque(
    const Nodo& estado,
    Color color) const
{
    const Ficha* rey = encontrarRey(estado, color);
    if (!rey) return false;

    Color enemigo =
        (color == Color::Blanca)
        ? Color::Negra
        : Color::Blanca;

    return casillaAtacada(
        estado,
        rey->getPosicion().x,
        rey->getPosicion().y,
        enemigo);
}

// ======================================================
// ATAQUES
// ======================================================

bool DecisionTreeEngine::casillaAtacada(
    const Nodo& estado,
    int x,
    int y,
    Color porQuien) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != porQuien)
            continue;

        auto ataques = obtenerMovimientosFicha(f, estado);

        for (const Posicion& p : ataques)
        {
            if (p.x == x && p.y == y)
                return true;
        }
    }

    return false;
}

// ======================================================
// REY
// ======================================================

const Ficha* DecisionTreeEngine::encontrarRey(
    const Nodo& estado,
    Color color) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getTipo() == TipoFicha::Rey &&
            f.getColor() == color)
        {
            return &f;
        }
    }
    return nullptr;
}