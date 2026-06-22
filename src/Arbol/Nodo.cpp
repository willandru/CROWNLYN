#include "Nodo.h"

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

    for (Ficha* f : piezas)
    {
        delete f;
    }
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
    piezas.clear();

    for (Ficha* f : other.piezas)
    {
        piezas.push_back(clonarFicha(f));
    }

    hijos.clear();
}

Ficha* Nodo::clonarFicha(const Ficha* f) const
{
    return new Ficha(*f);
}

bool Nodo::hayFichaEn(int x, int y) const
{
    for (Ficha* f : piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return true;
    }
    return false;
}

const Ficha* Nodo::obtenerFichaEn(int x, int y) const
{
    for (Ficha* f : piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return f;
    }
    return nullptr;
}

void Nodo::liberarHijos()
{
    for (Nodo* h : hijos)
    {
        delete h;
    }
    hijos.clear();
}