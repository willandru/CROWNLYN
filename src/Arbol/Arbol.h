#pragma once

#include <vector>
#include <iostream>

#include "Nodo.h"
#include "DecisionTreeEngine.h"

class Arbol
{
public:
    Arbol();
    ~Arbol();

    void setNodoInicial(Nodo* raiz);

    void eliminarSubarbol();

    void construirSiguienteNivel();
    void construirDesdeNodo(Nodo* nodo, int profundidadMax);

    const std::vector<Nodo*>& getNodos() const;

    void imprimirNivel() const;
    void resumenNivel() const;

private:
    void liberarNodo(Nodo* nodo);

private:
    Nodo* raiz = nullptr;

    // FRONTIER (nivel actual)
    std::vector<Nodo*> nodos;

    DecisionTreeEngine* engine = nullptr;
};