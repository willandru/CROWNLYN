#include "Arbol.h"
#include "DecisionTreeEngine.h"

// ======================================================

Arbol::Arbol()
{
    raiz = nullptr;
    engine = new DecisionTreeEngine();
}

// ======================================================

Arbol::~Arbol()
{
    eliminarSubarbol();
    delete engine;
}

// ======================================================

void Arbol::setNodoInicial(Nodo* r)
{
    eliminarSubarbol();

    raiz = r;

    if (!raiz)
        return;

    if (raiz->piezas.empty())
        return;

    nodos.push_back(raiz);
}

// ======================================================

void Arbol::liberarNodo(Nodo* nodo)
{
    if (!nodo)
        return;

    for (Nodo* h : nodo->hijos)
        liberarNodo(h);

    nodo->hijos.clear();
    delete nodo;
}

// ======================================================

void Arbol::eliminarSubarbol()
{
    liberarNodo(raiz);
    raiz = nullptr;
    nodos.clear();
}

// ======================================================

const std::vector<Nodo*>& Arbol::getNodos() const
{
    return nodos;
}

// ======================================================

void Arbol::construirSiguienteNivel()
{
    std::vector<Nodo*> nuevos;

    for (Nodo* n : nodos)
    {
        if (!n)
            continue;

        size_t before = n->hijos.size();

        engine->expandirNodo(n);

        size_t after = n->hijos.size();

        for (Nodo* h : n->hijos)
        {
            if (h)
                nuevos.push_back(h);
        }
    }

    nodos = std::move(nuevos);
}

// ======================================================

void Arbol::construirDesdeNodo(Nodo* nodo, int profundidadMax)
{
    eliminarSubarbol();

    raiz = nodo;

    if (!raiz)
        return;

    nodos.push_back(raiz);

    for (int i = 0; i < profundidadMax; i++)
        construirSiguienteNivel();
}

// ======================================================

void Arbol::imprimirNivel() const
{
    std::cout << "\n=== NIVEL DEL ARBOL ===\n";

    int i = 0;

    for (const Nodo* n : nodos)
    {
        if (!n)
            continue;

        std::cout << "Nodo " << i++ << "\n";
        std::cout << "Piezas: " << n->piezas.size() << "\n";

        for (const Ficha& f : n->piezas)
        {
            std::cout
                << "  Pieza Tipo: " << f.tipoToString()
                << " Color: " << (f.getColor() == Color::Blanca ? "Blanca" : "Negra")
                << " Pos(" << f.getPosicion().x << "," << f.getPosicion().y << ")\n";
        }

        std::cout << "Estado: ";
        std::cout << (n->piezas.empty() ? "VACIO" : "OK");
        std::cout << "\n-----------------------\n";
    }

    std::cout << "=======================\n";
}

// ======================================================

void Arbol::resumenNivel() const
{
    std::cout << "\n=== RESUMEN NIVEL ===\n";

    std::cout << "Nodos: " << nodos.size() << "\n";

    int vacios = 0;

    for (const Nodo* n : nodos)
        if (!n || n->piezas.empty())
            vacios++;

    std::cout << "Nodos vacios: " << vacios << "\n";

    std::cout << "=====================\n";
}