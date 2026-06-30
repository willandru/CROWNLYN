#include "MoveGenerator.h"

#include "Nodo.h"
#include "Ficha.h"

#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Dama.h"
#include "Rey.h"

// ======================================================

std::vector<Posicion> MoveGenerator::getMovimientos(
    const Ficha& ficha,
    const Nodo& nodo
)
{
    switch (ficha.getTipo())
    {
        case TipoFicha::Peon:
            return Peon().getMovimientos(ficha, nodo);

        case TipoFicha::Torre:
            return Torre().getMovimientos(ficha, nodo);

        case TipoFicha::Caballo:
            return Caballo().getMovimientos(ficha, nodo);

        case TipoFicha::Alfil:
            return Alfil().getMovimientos(ficha, nodo);

        case TipoFicha::Dama:
            return Dama().getMovimientos(ficha, nodo);

        case TipoFicha::Rey:
            return Rey().getMovimientos(ficha, nodo);
    }

    return {};
}

// ======================================================

std::vector<Posicion> MoveGenerator::getAtaques(
    const Ficha& ficha,
    const Nodo& nodo
)
{
    switch (ficha.getTipo())
    {
        case TipoFicha::Peon:
            return Peon().getAtaques(ficha, nodo);

        case TipoFicha::Torre:
            return Torre().getAtaques(ficha, nodo);

        case TipoFicha::Caballo:
            return Caballo().getAtaques(ficha, nodo);

        case TipoFicha::Alfil:
            return Alfil().getAtaques(ficha, nodo);

        case TipoFicha::Dama:
            return Dama().getAtaques(ficha, nodo);

        case TipoFicha::Rey:
            return Rey().getAtaques(ficha, nodo);
    }

    return {};
}