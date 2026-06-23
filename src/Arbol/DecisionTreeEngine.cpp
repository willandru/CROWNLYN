#include "DecisionTreeEngine.h"
#include <iostream>

// ======================================================
// CONSTRUCTOR
// ======================================================

DecisionTreeEngine::DecisionTreeEngine()
{
    std::cout << "[DTE] DecisionTreeEngine constructor OK\n";
}

// ======================================================
// EXPANSIÓN DEL ÁRBOL
// ======================================================

void DecisionTreeEngine::expandirNodo(Nodo* nodo)
{

    if (!nodo)
    {
        std::cout << "[DTE_expandirNodo] nodo NULL -> return\n";
        return;
    }

    Color jugador = nodo->turnoActual;

    std::cout << "[DTE_expandirNodo] turno actual = "
              << (jugador == Color::Blanca ? "Blanca" : "Negra")
              << "\n";

    if (esMate(*nodo, jugador))
    {
        std::cout << "[DTE_expandirNodo] STOP: estado = MATE\n";
        return;
    }

    if (esDerrota(*nodo))
    {
        std::cout << "[DTE_expandirNodo] STOP: estado = DERROTA\n";
        return;
    }

    if (sinMovimientos(*nodo, jugador))
    {
        std::cout << "[DTE_expandirNodo] STOP: sin movimientos\n";
        return;
    }

    int hijos = 0;

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        std::cout << "[DTE_expandirNodo] pieza ID=" << f.getId() << "\n";

        auto movs = obtenerMovimientosFicha(f, *nodo);

        std::cout << "[DTE_expandirNodo] movs=" << movs.size() << "\n";

        for (const Posicion& p : movs)
        {
            std::cout << "[DTE_expandirNodo] test move -> ("
                      << p.x << "," << p.y << ")\n";

            if (!esMovimientoLegal(*nodo, f, p))
            {
                std::cout << "[DTE_expandirNodo] move ilegal\n";
                continue;
            }

            Nodo nuevo = simularMovimiento(*nodo, f, p);

            Nodo* hijo = new Nodo(nuevo);

            hijo->turnoActual =
                (jugador == Color::Blanca)
                ? Color::Negra
                : Color::Blanca;

            nodo->agregarHijo(hijo);

            hijos++;

            std::cout << "[DTE_expandirNodo] hijo creado = " << hijos << "\n";
        }
    }

    std::cout << "[DTE_expandirNodo] expandirNodo END hijos=" << hijos << "\n";
}

// ======================================================
// SIMULACIÓN
// ======================================================

Nodo DecisionTreeEngine::simularMovimiento(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    std::cout << "[DTE_simularMovimiento] simularMovimiento ID="
              << ficha.getId()
              << " -> (" << destino.x << "," << destino.y << ")\n";

    Nodo copia = estado;

    const int id = ficha.getId();

    for (auto it = copia.piezas.begin();
         it != copia.piezas.end();
         ++it)
    {
        if (it->getPosicion().x == destino.x &&
            it->getPosicion().y == destino.y)
        {
            std::cout << "[DTE_simularMovimiento] capture detected\n";

            if (it->getTipo() == TipoFicha::Rey)
            {
                std::cout << "[DTE_simularMovimiento] REY capturado -> abort\n";
                return estado;
            }

            copia.piezas.erase(it);
            break;
        }
    }

    for (Ficha& f : copia.piezas)
    {
        if (f.getId() == id)
        {
            f.setPosicion(destino);
            std::cout << "[DEBUG] piece moved\n";
            break;
        }
    }

    return copia;
}

// ======================================================
// MOVIMIENTOS POR PIEZA
// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerMovimientosFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    std::cout << "[DTE_obtenerMovimientosFicha] obtenerMovimientosFicha Tipo="
              << f.tipoToString() << "\n";

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
// ATAQUES
// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerAtaquesFicha(
    const Ficha& f,
    const Nodo& estado) const
{
    std::cout << "[DTE_obtenerAtaquesFicha] obtenerAtaquesFicha Tipo="
              << f.tipoToString() << "\n";

    switch (f.getTipo())
    {
        case TipoFicha::Torre:
            return Torre().getMovimientos(f, estado);

        case TipoFicha::Rey:
            return Rey().getMovimientos(f, estado);

        case TipoFicha::Peon:
            return Peon().getAtaques(f, estado);

        default:
            return {};
    }
}

// ======================================================
// LEGALIDAD
// ======================================================

bool DecisionTreeEngine::esMovimientoLegal(
    const Nodo& estado,
    const Ficha& ficha,
    const Posicion& destino) const
{
    std::cout << "[DTE_esMovimientoLegal] esMovimientoLegal ID="
              << ficha.getId() << "\n";

    Nodo sim = simularMovimiento(estado, ficha, destino);

    bool ok = !estaEnJaque(sim, ficha.getColor());

    std::cout << "[DTE_esMovimientoLegal] legal = " << ok << "\n";

    return ok;
}

// ======================================================
// JAQUE
// ======================================================

bool DecisionTreeEngine::estaEnJaque(
    const Nodo& estado,
    Color color) const
{

    const Ficha* rey = encontrarRey(estado, color);

    if (!rey)
    {
        std::cout << "[DTE_estaEnJaque] REY missing\n";
        return false;
    }

    Color enemigo =
        (color == Color::Blanca)
        ? Color::Negra
        : Color::Blanca;

    bool atk = casillaAtacada(
        estado,
        rey->getPosicion().x,
        rey->getPosicion().y,
        enemigo);

    std::cout << "[DTE_estaEnJaque] jaque = " << atk << "\n";

    return atk;
}

// ======================================================
// CASILLA ATACADA
// ======================================================

bool DecisionTreeEngine::casillaAtacada(
    const Nodo& estado,
    int x,
    int y,
    Color atacante) const
{
    std::cout << "[DTE_casillaAtacada] casillaAtacada (" << x << "," << y << ")\n";

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != atacante)
            continue;

        auto ataques = obtenerAtaquesFicha(f, estado);

        for (const Posicion& p : ataques)
        {
            if (p.x == x && p.y == y)
            {
                std::cout << "[DTE_casillaAtacada] ATTACK HIT\n";
                return true;
            }
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
            std::cout << "[DTE_encontrarRey] rey found\n";
            return &f;
        }
    }

    std::cout << "[DTE_encontrarRey] rey NOT found\n";
    return nullptr;
}

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

bool DecisionTreeEngine::tieneMovimientosLegales(
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
            {
                std::cout << "[DTE_tieneMovimientosLegales] legal move found\n";
                return true;
            }
        }
    }

    std::cout << "[DTE_tieneMovimientosLegales] no legal moves\n";
    return false;
}

// ======================================================
// MATE
// ======================================================

bool DecisionTreeEngine::esMate(
    const Nodo& estado,
    Color color) const
{
    bool r = estaEnJaque(estado, color)
          && !tieneMovimientosLegales(estado, color);

    std::cout << "[DTE_esMate] esMate = " << r << "\n";

    return r;
}

// ======================================================
// DERROTA
// ======================================================

bool DecisionTreeEngine::esDerrota(
    const Nodo& estado) const
{
    int b = 0, n = 0;

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() == Color::Blanca) b++;
        else n++;
    }

    std::cout << "[DTE_esDerrota] piezas B=" << b << " N=" << n << "\n";

    bool r = (b == 0 && n > 0);

    std::cout << "[DTE_esDerrota] esDerrota = " << r << "\n";

    return r;
}

// ======================================================
// SIN MOVIMIENTOS
// ======================================================

bool DecisionTreeEngine::sinMovimientos(
    const Nodo& estado,
    Color color) const
{
    bool r = !tieneMovimientosFisicos(estado, color);

    std::cout << "[DTE_sinMovimientos] sinMovimientos = " << r << "\n";

    return r;
}

// ======================================================
// MOVIMIENTOS FÍSICOS
// ======================================================

bool DecisionTreeEngine::tieneMovimientosFisicos(
    const Nodo& estado,
    Color color) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() != color)
            continue;

        auto movs = obtenerMovimientosFicha(f, estado);

        if (!movs.empty())
        {
            std::cout << "[DTE_tieneMoviFisic] movement exists\n";
            return true;
        }
    }

    std::cout << "[DTE_tieneMoviFisic] no physical moves\n";
    return false;
}

// ======================================================
// UTILIDAD
// ======================================================

bool DecisionTreeEngine::casillaOcupadaPorColor(
    const Nodo& estado,
    int x,
    int y,
    Color color) const
{
    
    for (const Ficha& f : estado.piezas)
    {
        if (f.getPosicion().x == x &&
            f.getPosicion().y == y &&
            f.getColor() == color)
        {
            std::cout << "[DTE_casillaOcupadaPorColor] casillaOcupadaPorColor\n";
            return true;
        }
    }

    return false;
}