#include "Nodo.h"

// Piezas
#include "Torre.h"
#include "Rey.h"
#include "Peon.h"

Nodo::Nodo()
{
    padre = nullptr;
    turnoActual = Color::Blanca;
}

Nodo::Nodo(const Nodo& other)
{
    padre = nullptr;
    tablero = other.tablero;
    turnoActual = other.turnoActual;

    copiar(other);
}

Nodo::~Nodo()
{
    liberarHijos();
    piezas.clear();
}

void Nodo::agregarHijo(Nodo* hijo)
{
    if (!hijo) return;

    hijo->padre = this;
    hijos.push_back(hijo);
}

Nodo* Nodo::clonar() const
{
    return new Nodo(*this);
}

void Nodo::copiar(const Nodo& other)
{
    piezas = other.piezas;
    hijos.clear();
}

const Ficha* Nodo::obtenerFichaEn(int x, int y) const
{
    for (const Ficha& f : piezas)
    {
        if (f.getPosicion().x == x && f.getPosicion().y == y)
            return &f;
    }
    return nullptr;
}

bool Nodo::hayFichaEn(int x, int y) const
{
    for (const Ficha& f : piezas)
    {
        if (f.getPosicion().x == x && f.getPosicion().y == y)
            return true;
    }
    return false;
}

void Nodo::liberarHijos()
{
    for (Nodo* h : hijos)
    {
        delete h;
    }
    hijos.clear();
}

// ===============================
// JAQUE
// ===============================

const Ficha* Nodo::encontrarRey(Color color) const
{
    for (const Ficha& f : piezas)
    {
        if (f.getTipo() == TipoFicha::Rey && f.getColor() == color)
            return &f;
    }
    return nullptr;
}

bool Nodo::casillaAtacada(int x, int y, Color porQuien) const
{
    Torre torre;
    Rey rey;
    Peon peon;

    for (const Ficha& f : piezas)
    {
        if (f.getColor() != porQuien)
            continue;

        std::vector<Posicion> ataques;

        switch (f.getTipo())
        {
            case TipoFicha::Torre:
                ataques = torre.getMovimientos(f, *this);
                break;

            case TipoFicha::Rey:
                ataques = rey.getMovimientos(f, *this);
                break;

            case TipoFicha::Peon:
                ataques = peon.getAtaques(f, *this);
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

bool Nodo::estaEnJaque(Color color) const
{
    const Ficha* rey = encontrarRey(color);
    if (!rey) return false;

    Color enemigo = (color == Color::Blanca) ? Color::Negra : Color::Blanca;

    Posicion pos = rey->getPosicion();

    return casillaAtacada(pos.x, pos.y, enemigo);
}