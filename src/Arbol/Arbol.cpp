#include "Arbol.h"

Arbol::Arbol()
{
    raiz = nullptr;
    nivelActual = 0;
}

Arbol::~Arbol()
{
    if (raiz)
    {
        delete raiz;
        raiz = nullptr;
    }

    for (auto& nivel : niveles)
    {
        for (Nodo* n : nivel)
        {
            delete n;
        }
    }
}

void Arbol::setNodoInicial(Nodo* raiz)
{
    this->raiz = raiz;

    niveles.clear();
    niveles.push_back({raiz});
    nivelActual = 0;
}

Nodo* Arbol::getNodoInicial() const
{
    return raiz;
}

const std::vector<Nodo*>& Arbol::getNodosDelNivelActual() const
{
    return niveles[nivelActual];
}

void Arbol::construirSiguienteNivel()
{
    if (nivelActual >= (int)niveles.size()) return;

    std::vector<Nodo*> siguienteNivel;

    for (Nodo* nodo : niveles[nivelActual])
    {
        expandirNodo(nodo, siguienteNivel);
    }

    if (!siguienteNivel.empty())
    {
        niveles.push_back(siguienteNivel);
        nivelActual++;
    }
}

void Arbol::expandirNodo(Nodo* nodo, std::vector<Nodo*>& siguienteNivel)
{
    if (!nodo) return;

    // aquí irá la lógica futura:
    // - recorrer piezas del nodo
    // - generar movimientos
    // - clonar nodos
    // - cambiar turno
    // - agregar hijos

    nodo->agregarHijo(nullptr); // placeholder estructural
}