#include "Nodo.h"

Nodo::Nodo()
{
    padre = nullptr;
    turnoActual = Color::Blanca;
    profundidad = 0;
}

Nodo::Nodo(const Nodo& other)
{
    padre = nullptr;
    tablero = other.tablero;
    turnoActual = other.turnoActual;
    profundidad = other.profundidad;

    copiarPiezas(other);

    hijos.clear();
}

Nodo::~Nodo()
{
    liberarHijos();
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

void Nodo::liberarHijos()
{
    for (Nodo* h : hijos)
    {
        delete h;
    }
    hijos.clear();
}

void Nodo::copiarPiezas(const Nodo& other)
{
    piezas = other.piezas;
}

bool Nodo::hayFichaEn(int x, int y) const
{
    for (const Ficha& f : piezas)
    {
        // Nota: aquí asume que Ficha tendrá posición más adelante
        // si no existe aún, este método se conecta después
    }
    return false;
}

const Ficha* Nodo::obtenerFichaEn(int x, int y) const
{
    for (const Ficha& f : piezas)
    {
        // placeholder hasta que Ficha incluya posición
    }
    return nullptr;
}