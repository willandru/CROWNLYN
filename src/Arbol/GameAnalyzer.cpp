#include "GameAnalyzer.h"

#include "Torre.h"
#include "Rey.h"
#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Dama.h"

// ======================================================
// UTILIDAD: PIEZA EN CASILLA
// ======================================================

const Ficha* GameAnalyzer::obtenerFichaEn(
    const Nodo& estado,
    int x,
    int y) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getPosicion().x == x &&
            f.getPosicion().y == y)
        {
            return &f;
        }
    }
    return nullptr;
}

// ======================================================
// ENCONTRAR REY
// ======================================================

const Ficha* GameAnalyzer::encontrarRey(
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
// SIMULACIÓN DE MOVIMIENTO
// ======================================================

Nodo GameAnalyzer::simularMovimiento(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo copia = estado;

    const int id = ficha.getId();

    // eliminar pieza capturada si existe
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
// ATAQUES POR PIEZA
// ======================================================

std::vector<Posicion> GameAnalyzer::obtenerAtaquesFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    switch (f.getTipo())
    {
        case TipoFicha::Torre:
            return Torre().getAtaques(f, estado);

        case TipoFicha::Rey:
            return Rey().getAtaques(f, estado);

        case TipoFicha::Peon:
            return Peon().getAtaques(f, estado);

        case TipoFicha::Caballo:
            return Caballo().getAtaques(f, estado);

        case TipoFicha::Alfil:
            return Alfil().getAtaques(f, estado);

        case TipoFicha::Dama:
            return Dama().getAtaques(f, estado);

        default:
            return {};
    }
}

// ======================================================
// MOVIMIENTOS POR PIEZA
// ======================================================

std::vector<Posicion> GameAnalyzer::obtenerMovimientosFicha(
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

        case TipoFicha::Caballo:
            return Caballo().getMovimientos(f, estado);

        case TipoFicha::Alfil:
            return Alfil().getMovimientos(f, estado);

        case TipoFicha::Dama:
            return Dama().getMovimientos(f, estado);

        default:
            return {};
    }
}

// ======================================================
// CASILLA ATACADA
// ======================================================

bool GameAnalyzer::casillaAtacada(
    const Nodo& estado,
    int x,
    int y,
    Color atacante) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != atacante)
            continue;

        auto ataques = obtenerAtaquesFicha(f, estado);

        for (const Posicion& p : ataques)
        {
            if (p.x == x && p.y == y)
                return true;
        }
    }

    return false;
}

// ======================================================
// JAQUE
// ======================================================

bool GameAnalyzer::estaEnJaque(
    const Nodo& estado,
    Color color) const
{
    const Ficha* rey = encontrarRey(estado, color);

    if (!rey)
        return false;

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
// MOVIMIENTO LEGAL
// ======================================================

bool GameAnalyzer::esMovimientoLegal(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo sim = simularMovimiento(estado, ficha, destino);

    return !estaEnJaque(sim, ficha.getColor());
}

// ======================================================
// MOVIMIENTOS LEGALES DE UNA PIEZA
// ======================================================

bool GameAnalyzer::tieneMovimientosLegales(
    const Nodo& estado,
    Color color) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != color)
            continue;

        auto movs = obtenerMovimientosFicha(f, estado);

        for (const Posicion& p : movs)
        {
            if (esMovimientoLegal(estado, f, p))
                return true;
        }
    }

    return false;
}