#include "Nodo.h"

// ======================================================
// CONSTRUCTOR
// ======================================================

Nodo::Nodo()
{
    padre = nullptr;
    turnoActual = Color::Blanca;
    tablero = Tablero();
}

// ======================================================
// COPIA CONSTRUCTORA
// ======================================================

Nodo::Nodo(const Nodo& other)
{
    padre = nullptr;
    copiar(other);
}

// ======================================================
// COPIA INTERNA (SIN ROMPER ÁRBOL)
// ======================================================

void Nodo::copiar(const Nodo& other)
{
    piezas = other.piezas;

    // ❗ NO copiar hijos (el árbol controla estructura)
    hijos.clear();

    padre = nullptr;

    turnoActual = other.turnoActual;
    tablero = other.tablero;
}

// ======================================================
// AGREGAR HIJO (RELACIÓN PADRE-HIJO)
// ======================================================

void Nodo::agregarHijo(Nodo* hijo)
{
    if (!hijo) return;

    hijo->padre = this;
    hijos.push_back(hijo);
}

// ======================================================
// BUSCAR FICHA POR POSICIÓN
// ======================================================

const Ficha* Nodo::obtenerFichaEn(int x, int y) const
{
    for (const Ficha& f : piezas)
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
// CHECK RÁPIDO
// ======================================================

bool Nodo::hayFichaEn(int x, int y) const
{
    return obtenerFichaEn(x, y) != nullptr;
}

// ======================================================
// BUSCAR POR ID (CONST)
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

// ======================================================
// BUSCAR POR ID (MODIFICABLE)
// ======================================================

Ficha* Nodo::obtenerFichaPorId(int id)
{
    for (Ficha& f : piezas)
    {
        if (f.getId() == id)
            return &f;
    }
    return nullptr;
}