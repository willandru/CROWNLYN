#include "Arbol.h"
#include "DecisionTreeEngine.h"

// ======================================================
// CONSTRUCTOR
// ======================================================

Arbol::Arbol()
{
    raiz = nullptr;
    engine = new DecisionTreeEngine();
}

// ======================================================
// DESTRUCTOR
// ======================================================

Arbol::~Arbol()
{
    eliminarSubarbol();
    delete engine;
}

// ======================================================
// DEFINIR RAÍZ
// ======================================================

void Arbol::setNodoInicial(Nodo* r)
{
    eliminarSubarbol();

    raiz = r;

    if (!raiz)
        return;

    nodos.push_back(raiz);
}

// ======================================================
// LIBERACIÓN RECURSIVA
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
// ELIMINAR TODO EL ÁRBOL
// ======================================================

void Arbol::eliminarSubarbol()
{
    if (raiz)
        liberarNodo(raiz);

    raiz = nullptr;
    nodos.clear();
}

// ======================================================
// NIVEL ACTUAL
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
    std::vector<Nodo*> nuevos;

    for (Nodo* n : nodos)
    {
        if (!n)
            continue;

        engine->expandirNodo(n);

        for (Nodo* h : n->hijos)
        {
            if (h)
                nuevos.push_back(h);
        }
    }

    nodos = std::move(nuevos);
}

// ======================================================
// CONSTRUCCIÓN DESDE RAÍZ
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
// DEBUG NIVEL
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
                << "  Tipo: " << f.tipoToString()
                << " Color: " << (f.getColor() == Color::Blanca ? "Blanca" : "Negra")
                << " Pos(" << f.getPosicion().x << "," << f.getPosicion().y << ")\n";
        }

        std::cout << "Estado: "
                  << (n->piezas.empty() ? "VACIO" : "OK")
                  << "\n-----------------------\n";
    }

    std::cout << "=======================\n";
}

// ======================================================
// RESUMEN NIVEL
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