#pragma once

#include <vector>

#include "Nodo.h"

struct Turno
{
    std::vector<Nodo*> nodos;
};

class Arbol
{
public:
    Arbol();
    ~Arbol();

    void construir(Nodo* raiz, int profundidadMaxima);

    const std::vector<Turno>& getTurnos() const;

    void liberar();

private:
    std::vector<Turno> turnos;

    void expandirTurno(Turno& turnoActual, int profundidad);
};