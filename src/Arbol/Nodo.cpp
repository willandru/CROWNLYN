#include "Nodo.h"
#include "Ficha.h"
#include "Tablero.h"

// ======================================================

Nodo::Nodo()
{
    padre = nullptr;
    tablero = nullptr;
    turnoActual = Color::Blanca;
}

// ======================================================

Nodo::Nodo(const Nodo& other)
{
    copiar(other);
}

// ======================================================

void Nodo::copiar(const Nodo& other)
{
    piezas = other.piezas;

    hijos.clear();

    padre = nullptr;

    // IMPORTANTE:
    // no copiar ownership del tablero
    tablero = other.tablero;

    turnoActual = other.turnoActual;
}

// ======================================================

void Nodo::agregarHijo(Nodo* hijo)
{
    if (!hijo)
        return;

    hijo->padre = this;
    hijos.push_back(hijo);
}

// ======================================================

const Ficha* Nodo::obtenerFichaEn(int x, int y) const
{
    for (const auto& f : piezas)
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

bool Nodo::hayFichaEn(int x, int y) const
{
    return obtenerFichaEn(x, y) != nullptr;
}

// ======================================================

const Ficha* Nodo::obtenerFichaPorId(int id) const
{
    for (const auto& f : piezas)
    {
        if (f.getId() == id)
            return &f;
    }

    return nullptr;
}

// ======================================================

Ficha* Nodo::obtenerFichaPorId(int id)
{
    for (auto& f : piezas)
    {
        if (f.getId() == id)
            return &f;
    }

    return nullptr;
}

// ======================================================

bool Nodo::esValida(int x, int y) const
{
    if (!tablero)
    {
        return false;
    }

    return tablero->esValida(x, y);
}