#include "Arbol.h"

// ======================================================
// CONSTRUCTOR / DESTRUCTOR
// ======================================================

Arbol::Arbol()
{
    raiz = nullptr;
}

Arbol::~Arbol()
{
    eliminarSubarbol();
}

// ======================================================
// INICIALIZACIÓN
// ======================================================

void Arbol::setNodoInicial(Nodo* r)
{
    raiz = r;
    nodos.clear();

    if (raiz)
    {
        nodos.push_back(raiz);
    }
}

void Arbol::agregarNodo(Nodo* nodo)
{
    if (!nodo) return;
    nodos.push_back(nodo);
}

// ======================================================
// LIMPIEZA TOTAL
// ======================================================

void Arbol::eliminarSubarbol()
{
    if (raiz)
    {
        delete raiz;
        raiz = nullptr;
    }

    nodos.clear();
}

// ======================================================
// ACCESO
// ======================================================

const std::vector<Nodo*>& Arbol::getNodos() const
{
    return nodos;
}

// ======================================================
// EXPANSIÓN DE UN NIVEL
// ======================================================

void Arbol::construirSiguienteNivel()
{
    std::vector<Nodo*> nuevosNodos;
    nuevosNodos.reserve(nodos.size() * 4);

    for (Nodo* n : nodos)
    {
        if (!n) continue;

        // genera hijos dentro del nodo
        engine.expandirNodo(n);

        // recolecta hijos generados
        for (Nodo* h : n->hijos)
        {
            nuevosNodos.push_back(h);
        }

        // IMPORTANTE:
        // NO limpiar hijos aquí, porque rompes la estructura del árbol
    }

    nodos = nuevosNodos;
}

// ======================================================
// EXPANSIÓN MULTINIVEL
// ======================================================

void Arbol::construirDesdeNodo(Nodo* nodo, int profundidadMax)
{
    raiz = nodo;
    nodos.clear();

    if (raiz)
    {
        nodos.push_back(raiz);
    }

    for (int i = 0; i < profundidadMax; i++)
    {
        construirSiguienteNivel();
    }
}

// ======================================================
// DEBUG
// ======================================================

void Arbol::imprimirNivel() const
{
    std::cout << "\n=== NIVEL DEL ARBOL ===\n";

    int i = 0;

    for (const Nodo* n : nodos)
    {
        std::cout << "Nodo " << i++ << "\n";

        std::cout << "Piezas: " << n->piezas.size() << "\n";

        for (const Ficha& f : n->piezas)
        {
            std::cout
                << "  Pieza Tipo: " << (int)f.getTipo()
                << " Color: " << (f.getColor() == Color::Blanca ? "Blanca" : "Negra")
                << " Pos(" << f.getPosicion().x << "," << f.getPosicion().y << ")\n";
        }
    }

    std::cout << "=======================\n";
}