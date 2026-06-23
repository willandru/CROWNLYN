#include "DecisionTreeEngine.h"
#include <iostream>

// ======================================================

DecisionTreeEngine::DecisionTreeEngine() {}

// ======================================================
// EXPANSIÓN DEL NODO
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{
    if (!nodo)
    {
        std::cout << "[EXPAND] NULL\n";
        return;
    }

    std::cout << "\n[EXPAND] piezas=" << nodo->piezas.size()
              << " turno=" << (nodo->turnoActual == Color::Blanca ? "Blanca" : "Negra") << "\n";

    Color jugador = nodo->turnoActual;

    int hijos = 0;
    int procesadas = 0;

    for (const Ficha& f : nodo->piezas)
    {
        std::cout << "\n[PIEZA] ID=" << f.getId()
                  << " tipo=" << (int)f.getTipo()
                  << " color=" << (f.getColor() == Color::Blanca ? "B" : "N") << "\n";

        if (f.getColor() != jugador)
        {
            std::cout << "  skip turno\n";
            continue;
        }

        procesadas++;

        auto movs = obtenerMovimientosFicha(f, *nodo);

        std::cout << "[MOV] ID=" << f.getId()
                  << " movs=" << movs.size() << "\n";

        for (const Posicion& p : movs)
        {
            std::cout << "   -> probando (" << p.x << "," << p.y << ")\n";

            Nodo nuevo = simularMovimiento(*nodo, f, p);

            if (!esNodoValido(nuevo))
            {
                std::cout << "   X nodo invalido\n";
                continue;
            }

            if (estaEnJaque(nuevo, jugador))
            {
                std::cout << "   X en jaque\n";
                continue;
            }

            Nodo* hijo = new Nodo(nuevo);
            hijo->turnoActual = (jugador == Color::Blanca) ? Color::Negra : Color::Blanca;

            nodo->agregarHijo(hijo);
            hijos++;

            std::cout << "   + hijo creado\n";
        }
    }

    std::cout << "\n[EXPAND FIN] procesadas=" << procesadas
              << " hijos=" << hijos << "\n";
}

// ======================================================
// SIMULACIÓN SEGURA
// ======================================================

Nodo DecisionTreeEngine::simularMovimiento(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    Nodo copia = estado;

    std::cout << "[SIM] ID=" << ficha.getId()
              << " -> (" << destino.x << "," << destino.y << ")\n";

    // eliminar SOLO pieza enemiga en destino
    for (auto it = copia.piezas.begin(); it != copia.piezas.end(); )
    {
        if (it->getPosicion().x == destino.x &&
            it->getPosicion().y == destino.y)
        {
            if (it->getColor() != ficha.getColor())
            {
                std::cout << "[SIM] captura\n";
                it = copia.piezas.erase(it);
                continue;
            }
        }
        ++it;
    }

    // mover pieza original
    bool ok = false;

    for (Ficha& f : copia.piezas)
    {
        if (f.getId() == ficha.getId())
        {
            f.setPosicion(destino);
            ok = true;
            break;
        }
    }

    if (!ok)
    {
        std::cout << "[SIM] ERROR pieza perdida ID=" << ficha.getId() << "\n";
        copia.piezas.clear();
    }

    return copia;
}

// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerMovimientosFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    std::cout << "[MOV] ID=" << f.getId() << "\n";

    switch (f.getTipo())
    {
        case TipoFicha::Torre:   return Torre().getMovimientos(f, estado);
        case TipoFicha::Alfil:   return Alfil().getMovimientos(f, estado);
        case TipoFicha::Dama:    return Dama().getMovimientos(f, estado);
        case TipoFicha::Caballo: return Caballo().getMovimientos(f, estado);
        case TipoFicha::Rey:     return Rey().getMovimientos(f, estado);
        case TipoFicha::Peon:    return Peon().getMovimientos(f, estado);
        default: return {};
    }
}

// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerAtaquesFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    switch (f.getTipo())
    {
        case TipoFicha::Torre:   return Torre().getAtaques(f, estado);
        case TipoFicha::Alfil:   return Alfil().getAtaques(f, estado);
        case TipoFicha::Dama:    return Dama().getAtaques(f, estado);
        case TipoFicha::Caballo: return Caballo().getAtaques(f, estado);
        case TipoFicha::Rey:     return Rey().getAtaques(f, estado);
        case TipoFicha::Peon:    return Peon().getAtaques(f, estado);
        default: return {};
    }
}

// ======================================================

bool DecisionTreeEngine::estaEnJaque(
    const Nodo& estado,
    Color color) const
{
    const Ficha* rey = encontrarRey(estado, color);

    if (!rey)
    {
        std::cout << "[CHECK] rey missing\n";
        return true;
    }

    Color enemigo = (color == Color::Blanca) ? Color::Negra : Color::Blanca;

    bool atk = casillaAtacada(
        estado,
        rey->getPosicion().x,
        rey->getPosicion().y,
        enemigo);

    std::cout << "[CHECK] rey (" << rey->getPosicion().x
              << "," << rey->getPosicion().y
              << ") -> " << (atk ? "EN JAQUE" : "LIBRE") << "\n";

    return atk;
}

// ======================================================

bool DecisionTreeEngine::casillaAtacada(
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
            if (p.x == x && p.y == y)
                return true;
    }

    return false;
}

// ======================================================

const Ficha* DecisionTreeEngine::encontrarRey(
    const Nodo& estado,
    Color color) const
{
    for (const Ficha& f : estado.piezas)
        if (f.getTipo() == TipoFicha::Rey && f.getColor() == color)
            return &f;

    return nullptr;
}

// ======================================================

bool DecisionTreeEngine::esNodoValido(const Nodo& estado) const
{
    return !estado.piezas.empty();
}