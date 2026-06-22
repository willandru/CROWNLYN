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
// SET ROOT
// ======================================================

void Arbol::setNodoInicial(Nodo* r)
{
    eliminarSubarbol();

    raiz = r;

    if (raiz)
        nodos.push_back(raiz);
}

// ======================================================
// LIBERACIÓN SEGURA (DFS)
// ======================================================

void Arbol::liberarNodo(Nodo* nodo)
{
    if (!nodo) return;

    for (Nodo* h : nodo->hijos)
        liberarNodo(h);

    delete nodo;
}

// ======================================================
// LIMPIEZA TOTAL
// ======================================================

void Arbol::eliminarSubarbol()
{
    if (raiz)
    {
        liberarNodo(raiz);
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

        // IMPORTANTE: evitar acumulación previa
        // (si expandes varias veces sin reset, esto es crítico)
        n->hijos.clear();

        engine.expandirNodo(n);

        for (Nodo* h : n->hijos)
        {
            if (h)
                nuevosNodos.push_back(h);
        }
    }

    nodos = std::move(nuevosNodos);
}

// ======================================================
// MULTINIVEL
// ======================================================

void Arbol::construirDesdeNodo(Nodo* nodo, int profundidadMax)
{
    eliminarSubarbol();

    raiz = nodo;

    if (raiz)
        nodos.push_back(raiz);

    for (int i = 0; i < profundidadMax; i++)
        construirSiguienteNivel();
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
        if (!n) continue;

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