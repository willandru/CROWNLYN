#include "DecisionTreeEngine.h"

#include "Torre.h"
#include "Rey.h"
#include "Peon.h"

// ======================================================
// CONSTRUCTOR
// ======================================================

DecisionTreeEngine::DecisionTreeEngine()
{
}

// ======================================================
// EXPANSIÓN DEL ÁRBOL
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo) return;

    Color jugador = nodo->turnoActual;

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        std::vector<Posicion> movimientos =
            obtenerMovimientosFicha(f, *nodo);

        for (const Posicion& p : movimientos)
        {
            // FILTRO DE LEGALIDAD (clave)
            if (!esMovimientoLegal(*nodo, f, p))
                continue;

            // CREAR HIJO
            Nodo* hijo = new Nodo(*nodo);

            // APLICAR MOVIMIENTO
            for (Ficha& hf : hijo->piezas)
            {
                if (hf.getPosicion().x == f.getPosicion().x &&
                    hf.getPosicion().y == f.getPosicion().y)
                {
                    hf.setPosicion(p);
                    break;
                }
            }

            // CAMBIO DE TURNO
            hijo->turnoActual =
                (jugador == Color::Blanca)
                ? Color::Negra
                : Color::Blanca;

            // CONEXIÓN
            nodo->agregarHijo(hijo);
        }
    }
}

// ======================================================
// MOVIMIENTOS POR PIEZA
// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerMovimientosFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    switch (f.getTipo())
    {
        case TipoFicha::Torre:
        {
            Torre t;
            return t.getMovimientos(f, estado);
        }

        case TipoFicha::Rey:
        {
            Rey r;
            return r.getMovimientos(f, estado);
        }

        case TipoFicha::Peon:
        {
            Peon p;
            return p.getMovimientos(f, estado);
        }

        default:
            return {};
    }
}

// ======================================================
// SIMULACIÓN DE ESTADO
// ======================================================

Nodo DecisionTreeEngine::simularMovimiento(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo copia = estado;

    for (Ficha& f : copia.piezas)
    {
        if (f.getPosicion().x == ficha.getPosicion().x &&
            f.getPosicion().y == ficha.getPosicion().y)
        {
            f.setPosicion(destino);
            break;
        }
    }

    return copia;
}

// ======================================================
// VALIDACIÓN DE MOVIMIENTO
// ======================================================

bool DecisionTreeEngine::esMovimientoLegal(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Color jugador = ficha.getColor();

    Nodo simulado = simularMovimiento(estado, ficha, destino);

    return !estaEnJaque(simulado, jugador);
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
// CASILLAS ATACADAS
// ======================================================

bool DecisionTreeEngine::casillaAtacada(
    const Nodo& estado,
    int x,
    int y,
    Color porQuien) const
{
    Torre torre;
    Rey rey;
    Peon peon;

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != porQuien)
            continue;

        std::vector<Posicion> ataques;

        switch (f.getTipo())
        {
            case TipoFicha::Torre:
                ataques = torre.getMovimientos(f, estado);
                break;

            case TipoFicha::Rey:
                ataques = rey.getMovimientos(f, estado);
                break;

            case TipoFicha::Peon:
                ataques = peon.getAtaques(f, estado);
                break;

            default:
                continue;
        }

        for (const Posicion& p : ataques)
        {
            if (p.x == x && p.y == y)
                return true;
        }
    }

    return false;
}

// ======================================================
// ENCONTRAR REY
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