#include "DecisionTreeEngine.h"

#include "Torre.h"
#include "Rey.h"
#include "Peon.h"

// ======================================================
// CONSTRUCTOR
// ======================================================

DecisionTreeEngine::DecisionTreeEngine() {}

// ======================================================
// EXPANSIÓN (OPTIMIZADA)
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo) return;

    Color jugador = nodo->turnoActual;

    // si es mate no expandir
    if (esMate(*nodo, jugador))
        return;

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        // 1 sola generación de movimientos
        std::vector<Posicion> movs = obtenerMovimientosFicha(f, *nodo);

        for (const Posicion& p : movs)
        {
            // validación usando simulación directa
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
// MOVIMIENTOS (UNA SOLA FUENTE)
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
// SIMULACIÓN
// ======================================================

Nodo DecisionTreeEngine::simularMovimiento(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo copia = estado;

    int id = ficha.getId();

    // eliminar captura
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

    // mover pieza
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
// MOVIMIENTO LEGAL (NO DUPLICA MOVIMIENTOS)
// ======================================================

bool DecisionTreeEngine::esMovimientoLegal(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo sim = simularMovimiento(estado, ficha, destino);
    return !estaEnJaque(sim, ficha.getColor());
}

// ======================================================
// JAQUE (SIN REGENERAR MOVIMIENTOS EXTRA)
// ======================================================

bool DecisionTreeEngine::estaEnJaque(
    const Nodo& estado,
    Color color) const
{
    const Ficha* rey = encontrarRey(estado, color);

    if (!rey)
        return false;

    Color enemigo = (color == Color::Blanca)
        ? Color::Negra
        : Color::Blanca;

    return casillaAtacada(
        estado,
        rey->getPosicion().x,
        rey->getPosicion().y,
        enemigo);
}

// ======================================================
// ATAQUE A CASILLA (REUTILIZA MOVIMIENTOS YA EXISTENTES)
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

        // REUTILIZA MISMO GENERADOR (NO OTRO SISTEMA)
        std::vector<Posicion> movs = obtenerMovimientosFicha(f, estado);

        for (const Posicion& p : movs)
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

// ======================================================
// MOVIMIENTOS LEGALES (NO DUPLICA SIMULACIÓN)
// ======================================================

bool DecisionTreeEngine::tieneMovimientosLegales(
    const Nodo& estado,
    Color color) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != color)
            continue;

        std::vector<Posicion> movs = obtenerMovimientosFicha(f, estado);

        for (const Posicion& p : movs)
        {
            if (esMovimientoLegal(estado, f, p))
                return true;
        }
    }

    return false;
}

// ======================================================
// MATE
// ======================================================

bool DecisionTreeEngine::esMate(
    const Nodo& estado,
    Color color) const
{
    return estaEnJaque(estado, color)
        && !tieneMovimientosLegales(estado, color);
}