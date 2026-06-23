#include "DecisionTreeEngine.h"

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
    if (!nodo)
        return;

    Color jugador = nodo->turnoActual;

    if (esMate(*nodo, jugador) ||
        esDerrota(*nodo) ||
        sinMovimientos(*nodo, jugador))
    {
        return;
    }

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != jugador)
            continue;

        auto movs = obtenerMovimientosFicha(f, *nodo);

        for (const Posicion& p : movs)
        {
            if (!esMovimientoLegal(*nodo, f, p))
                continue;

            Nodo nuevo = simularMovimiento(*nodo, f, p);

            Nodo* hijo = new Nodo(nuevo);

            hijo->turnoActual =
                (jugador == Color::Blanca)
                ? Color::Negra
                : Color::Blanca;

            nodo->agregarHijo(hijo);
        }
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

    const int id = ficha.getId();

    for (auto it = copia.piezas.begin();
         it != copia.piezas.end();
         ++it)
    {
        if (it->getPosicion().x == destino.x &&
            it->getPosicion().y == destino.y)
        {
            if (it->getTipo() == TipoFicha::Rey)
                return estado;

            copia.piezas.erase(it);
            break;
        }
    }

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
// MOVIMIENTOS POR PIEZA
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
// ATAQUES
// ======================================================

std::vector<Posicion> DecisionTreeEngine::obtenerAtaquesFicha(
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
    Nodo sim = simularMovimiento(
        estado,
        ficha,
        destino);

    return !estaEnJaque(
        sim,
        ficha.getColor());
}

// ======================================================
// JAQUE
// ======================================================

bool DecisionTreeEngine::estaEnJaque(
    const Nodo& estado,
    Color color) const
{
    const Ficha* rey =
        encontrarRey(
            estado,
            color);

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
// CASILLA ATACADA
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

        auto ataques =
            obtenerAtaquesFicha(
                f,
                estado);

        for (const Posicion& p : ataques)
        {
            if (p.x == x &&
                p.y == y)
            {
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
            return &f;
        }
    }

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

        auto movs =
            obtenerMovimientosFicha(
                f,
                estado);

        for (const Posicion& p : movs)
        {
            if (esMovimientoLegal(
                    estado,
                    f,
                    p))
            {
                return true;
            }
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
    return estaEnJaque(
               estado,
               color)
        &&
           !tieneMovimientosLegales(
               estado,
               color);
}

// ======================================================
// DERROTA
// ======================================================

bool DecisionTreeEngine::esDerrota(
    const Nodo& estado) const
{
    int blancas = 0;
    int negras  = 0;

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() == Color::Blanca)
            ++blancas;
        else
            ++negras;
    }

    return blancas == 0 &&
           negras > 0;
}

// ======================================================
// SIN MOVIMIENTOS
// ======================================================

bool DecisionTreeEngine::sinMovimientos(
    const Nodo& estado,
    Color color) const
{
    return !tieneMovimientosFisicos(estado, color);
}

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
            return true;
    }

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
            return true;
        }
    }

    return false;
}