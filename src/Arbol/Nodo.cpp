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

void Nodo::copiar(const Nodo& other)
{
    piezas = other.piezas;
    hijos.clear();
    padre = nullptr;

    turnoActual = other.turnoActual;
    tablero = other.tablero;
}

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