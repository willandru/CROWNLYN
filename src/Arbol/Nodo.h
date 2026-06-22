#pragma once

#include <vector>

#include "Tablero.h"
#include "Ficha.h"

class Nodo
{
public:
    Nodo();
    Nodo(const Nodo& other);
    ~Nodo();

    Tablero tablero;
    Color turnoActual;

    std::vector<Ficha*> piezas;

    Nodo* padre;
    std::vector<Nodo*> hijos;

    void agregarHijo(Nodo* hijo);
    Nodo* clonar() const;

    const Ficha* obtenerFichaEn(int x, int y) const;
    bool hayFichaEn(int x, int y) const;

    void liberarHijos();

private:
    void copiar(const Nodo& other);
    Ficha* clonarFicha(const Ficha* f) const;
};