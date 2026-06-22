#pragma once

#include <vector>

#include "Nodo.h"
#include "Ficha.h"

class Arbol
{
public:
    Arbol();
    ~Arbol();

    void setNodoInicial(Nodo* raiz);

    void construirSiguienteNivel();
    void construirDesdeNodo(Nodo* nodo, int profundidadMax);

    const std::vector<Nodo*>& getNodos() const;

private:
    Nodo* raiz;
    std::vector<Nodo*> nodos;

    std::vector<Posicion> obtenerMovimientosFicha(const Ficha& f, const Nodo& estado) const;
    void expandirNodo(Nodo* nodo);
};