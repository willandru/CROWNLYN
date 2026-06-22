#include "Arbol.h"

// Fichas (MODELO B - funciones externas)
#include "Torre.h"
#include "Rey.h"
#include "Peon.h"

#include <iostream>

Arbol::Arbol()
{
    raiz = nullptr;
}

Arbol::~Arbol()
{
    if (raiz)
        delete raiz;
}

void Arbol::setNodoInicial(Nodo* r)
{
    raiz = r;
    nodos.clear();

    if (raiz)
        nodos.push_back(raiz);
}

const std::vector<Nodo*>& Arbol::getNodos() const
{
    return nodos;
}

void Arbol::construirSiguienteNivel()
{
    std::vector<Nodo*> nuevosNodos;

    for (Nodo* n : nodos)
    {
        expandirNodo(n);

        for (Nodo* h : n->hijos)
        {
            nuevosNodos.push_back(h);
        }
    }

    nodos = nuevosNodos;
}

void Arbol::construirDesdeNodo(Nodo* nodo, int profundidadMax)
{
    raiz = nodo;
    nodos.clear();
    nodos.push_back(nodo);

    for (int i = 0; i < profundidadMax; i++)
    {
        construirSiguienteNivel();
    }
}

void Arbol::expandirNodo(Nodo* nodo)
{
    if (!nodo) return;

    for (const Ficha& f : nodo->piezas)
    {
        if (f.getColor() != nodo->turnoActual)
            continue;

        std::vector<Posicion> movimientos = obtenerMovimientosFicha(f, *nodo);

        for (const Posicion& p : movimientos)
        {
            Nodo* hijo = nodo->clonar();

            for (Ficha& hf : hijo->piezas)
            {
                if (hf.getPosicion().x == f.getPosicion().x &&
                    hf.getPosicion().y == f.getPosicion().y)
                {
                    hf.setPosicion(p);
                    break;
                }
            }

            hijo->turnoActual = (nodo->turnoActual == Color::Blanca)
                                ? Color::Negra
                                : Color::Blanca;

            nodo->agregarHijo(hijo);
        }
    }
}

std::vector<Posicion> Arbol::obtenerMovimientosFicha(const Ficha& f, const Nodo& estado) const
{
    switch (f.getTipo())
    {
        case TipoFicha::Torre:
        {
            Torre t;
            return t.getMovimientos(f, estado);
        }

        case TipoFicha::Rey:
        {
            Rey r;
            return r.getMovimientos(f, estado);
        }

        case TipoFicha::Peon:
        {
            Peon p;
            return p.getMovimientos(f, estado);
        }

        default:
            return {};
    }
}

void Arbol::imprimirNivel() const
{
    std::cout << "\n=== NIVEL ACTUAL DEL ARBOL ===\n";

    int idxNodo = 0;

    for (const Nodo* n : nodos)
    {
        std::cout << "\nNodo " << idxNodo++ << "\n";
        std::cout << "Turno: " << (n->turnoActual == Color::Blanca ? "Blanca" : "Negra") << "\n";
        std::cout << "Piezas: " << n->piezas.size() << "\n";

        int idx = 0;
        for (const Ficha& f : n->piezas)
        {
            std::cout << "  Pieza " << idx++
                      << " Tipo: " << (int)f.getTipo()
                      << " Color: " << (f.getColor() == Color::Blanca ? "Blanca" : "Negra")
                      << " Pos(" << f.getPosicion().x << "," << f.getPosicion().y << ")\n";
        }

        std::cout << "Hijos: " << n->hijos.size() << "\n";
    }

    std::cout << "==============================\n";
}