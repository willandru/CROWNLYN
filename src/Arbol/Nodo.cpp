#include "Nodo.h"

Nodo::Nodo()
{
    padre = nullptr;
    turnoActual = Color::Blanca;
    tablero = Tablero();
}

Nodo::Nodo(const Nodo& other)
{
    padre = nullptr;
    copiar(other);
}

Nodo::~Nodo()
{
    liberarHijos();
}

// ======================================================
// COPIA PROFUNDA DEL ESTADO
// ======================================================
void Nodo::copiar(const Nodo& other)
{
    piezas = other.piezas;

    hijos.clear();
    padre = nullptr;

    turnoActual = other.turnoActual;
    tablero = other.tablero;
}

// ======================================================
// HIJOS
// ======================================================
void Nodo::agregarHijo(Nodo* hijo)
{
    if (!hijo) return;

    hijo->padre = this;
    hijos.push_back(hijo);
}

void Nodo::liberarHijos()
{
    for (Nodo* h : hijos)
        delete h;

    hijos.clear();
}

// ======================================================
// BUSQUEDA POR POSICION
// ======================================================
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
    return obtenerFichaEn(x, y) != nullptr;
}

// ======================================================
// BUSQUEDA POR ID (CRÍTICO PARA EL ENGINE)
// ======================================================
const Ficha* Nodo::obtenerFichaPorId(int id) const
{
    for (const Ficha& f : piezas)
    {
        if (f.getId() == id)
            return &f;
    }
    return nullptr;
}

Ficha* Nodo::obtenerFichaPorId(int id)
{
    for (Ficha& f : piezas)
    {
        if (f.getId() == id)
            return &f;
    }
    return nullptr;
}