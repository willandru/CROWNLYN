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

    if (raiz)
        nodos.push_back(raiz);
}

// ======================================================

void Arbol::liberarNodo(Nodo* nodo)
{
    if (!nodo) return;

    for (Nodo* h : nodo->hijos)
        liberarNodo(h);

    delete nodo;
}

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
        if (!n) continue;

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

void Arbol::imprimirNivel() const
{
    std::cout << "\n=== NIVEL DEL ARBOL ===\n";

    int i = 0;

    for (const Nodo* n : nodos)
    {
        if (!n)
            continue;

        Color jugador = n->turnoActual;

        bool mate     = engine->esMate(*n, jugador);
        bool derrota  = engine->esDerrota(*n);
        bool sinMov   = engine->sinMovimientos(*n, jugador);
        bool jaque    = engine->estaEnJaque(*n, jugador);

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

        if (mate)
            std::cout << "MATE";
        else if (derrota)
            std::cout << "DERROTA";
        else if (sinMov)
            std::cout << "SIN_MOVIMIENTOS";
        else if (jaque)
            std::cout << "JAQUE";
        else
            std::cout << "NORMAL";

        std::cout << "\n";
        std::cout << "-----------------------\n";
    }

    std::cout << "=======================\n";
}

// ======================================================

void Arbol::resumenNivel() const
{
    std::cout << "\n=== RESUMEN NIVEL ===\n";

    int jaqueCount = 0;
    int mateCount = 0;
    int derrotaCount = 0;
    int sinMovCount = 0;

    for (const Nodo* n : nodos)
    {
        if (!n)
            continue;

        Color jugador = n->turnoActual;

        if (engine->estaEnJaque(*n, jugador))
            jaqueCount++;

        if (engine->esMate(*n, jugador))
            mateCount++;

        if (engine->esDerrota(*n))
            derrotaCount++;

        if (engine->sinMovimientos(*n, jugador))
            sinMovCount++;
    }

    std::cout << "Nodos: " << nodos.size() << "\n";
    std::cout << "Jaques: " << jaqueCount << "\n";
    std::cout << "Mates: " << mateCount << "\n";
    std::cout << "Derrotas: " << derrotaCount << "\n";
    std::cout << "Sin movimientos: " << sinMovCount << "\n";

    std::cout << "=====================\n";
}