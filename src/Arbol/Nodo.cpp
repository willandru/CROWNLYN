#include "Nodo.h"

Nodo::Nodo()
{
    padre = nullptr;
    turnoActual = Color::Blanca;
}

Nodo::Nodo(const Nodo& other)
{
    padre = nullptr;
    copiar(other);
}

void Nodo::copiar(const Nodo& other)
{
    piezas = other.piezas;
    turnoActual = other.turnoActual;

    hijos.clear();
    padre = nullptr;

    tablero = other.tablero;
}

void Nodo::agregarHijo(Nodo* hijo)
{
    if (!hijo) return;

    hijo->padre = this;
    hijos.push_back(hijo);
}

const Ficha* Nodo::obtenerFichaEn(int x, int y) const
{
    for (const Ficha& f : piezas)
        if (f.getPosicion().x == x && f.getPosicion().y == y)
            return &f;

    return nullptr;
}

bool Nodo::hayFichaEn(int x, int y) const
{
    return obtenerFichaEn(x, y) != nullptr;
}

const Ficha* Nodo::obtenerFichaPorId(int id) const
{
    for (const Ficha& f : piezas)
        if (f.getId() == id)
            return &f;

    return nullptr;
}

Ficha* Nodo::obtenerFichaPorId(int id)
{
    for (Ficha& f : piezas)
        if (f.getId() == id)
            return &f;

    return nullptr;
}