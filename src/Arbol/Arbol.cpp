#include "Arbol.h"
#include "Ficha.h"

Arbol::Arbol()
{
}

Arbol::~Arbol()
{
    liberar();
}

void Arbol::construir(Nodo* raiz, int profundidadMaxima)
{
    liberar();

    if (!raiz || profundidadMaxima <= 0)
        return;

    Turno primerTurno;
    primerTurno.nodos.push_back(raiz);

    turnos.push_back(primerTurno);

    expandirTurno(turnos[0], profundidadMaxima);
}

void Arbol::expandirTurno(Turno& turnoActual, int profundidad)
{
    if (profundidad <= 0)
        return;

    Turno siguienteTurno;

    for (Nodo* nodo : turnoActual.nodos)
    {
        for (Ficha* f : nodo->piezas)
        {
            std::vector<Posicion> movs = f->getMovimientos(*nodo);

            for (const Posicion& p : movs)
            {
                Nodo* hijo = nodo->clonar();

                // mover ficha en el hijo
                for (Ficha* fh : hijo->piezas)
                {
                    if (fh->getPosicion().x == f->getPosicion().x &&
                        fh->getPosicion().y == f->getPosicion().y)
                    {
                        fh->setPosicion(p);
                        break;
                    }
                }

                hijo->agregarHijo(hijo);
                siguienteTurno.nodos.push_back(hijo);
            }
        }
    }

    turnos.push_back(siguienteTurno);

    expandirTurno(turnos.back(), profundidad - 1);
}

const std::vector<Turno>& Arbol::getTurnos() const
{
    return turnos;
}

void Arbol::liberar()
{
    for (Turno& t : turnos)
    {
        for (Nodo* n : t.nodos)
        {
            delete n;
        }
        t.nodos.clear();
    }

    turnos.clear();
}