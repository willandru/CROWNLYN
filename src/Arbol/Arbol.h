#pragma once

#include <vector>
#include "Nodo.h"

class Arbol
{
public:
    Arbol();
    ~Arbol();

    void setNodoInicial(Nodo* raiz);
    Nodo* getNodoInicial() const;

    void construirSiguienteNivel();

    const std::vector<Nodo*>& getNodosDelNivelActual() const;

private:
    Nodo* raiz;

    // niveles del árbol (cada nivel = turno)
    std::vector<std::vector<Nodo*>> niveles;

    int nivelActual;

    void expandirNodo(Nodo* nodo, std::vector<Nodo*>& siguienteNivel);
};