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
        if (!n) continue;

        // ======================================================
        // FILTRO DEBUG: SOLO NODOS CON REY EN (1,1)
        // ======================================================

        bool match = false;

        for (const Ficha& f : n->piezas)
        {
            if (f.getTipo() == TipoFicha::Rey &&
                f.getPosicion().x == 1 &&
                f.getPosicion().y == 1)
            {
                match = true;
                break;
            }
        }

        if (!match)
            continue;

        // ======================================================

        Color jugador = n->turnoActual;

        bool mate   = engine->esMate(*n, jugador);
        bool tablas = engine->esAhogado(*n, jugador);
        bool jaque  = engine->estaEnJaque(*n, jugador);

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
        if (mate) std::cout << "MATE";
        else if (tablas) std::cout << "TABLAS";
        else if (jaque) std::cout << "JAQUE";
        else std::cout << "NORMAL";

        std::cout << "\n";
    }

    

    std::cout << "=======================\n";
}