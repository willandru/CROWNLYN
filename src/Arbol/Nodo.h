#pragma once

#include <vector>
#include "Ficha.h"
#include "Tablero.h"

class Nodo
{
public:
    Nodo();
    Nodo(const Nodo& other);

    ~Nodo() = default;

    void agregarHijo(Nodo* hijo);

    const Ficha* obtenerFichaEn(int x, int y) const;
    bool hayFichaEn(int x, int y) const;

    const Ficha* obtenerFichaPorId(int id) const;
    Ficha* obtenerFichaPorId(int id);

private:
    void copiar(const Nodo& other);

public:
    std::vector<Ficha> piezas;
    std::vector<Nodo*> hijos;
    Nodo* padre;

    Color turnoActual;
    Tablero tablero;
};