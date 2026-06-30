#include "MoveExecutor.h"

#include "Nodo.h"
#include "Ficha.h"
#include "Tablero.h"

// ======================================================

bool MoveExecutor::ejecutarMovimiento(
    Nodo& nodo,
    int idFicha,
    const Posicion& destino
)
{
    Ficha* ficha = nodo.obtenerFichaPorId(idFicha);

    if (!ficha)
        return false;

    // validar tablero
    if (!nodo.tablero)
        return false;

    // evitar captura propia
    const Ficha* target = nodo.obtenerFichaEn(destino.x, destino.y);

    if (target && target->getColor() == ficha->getColor())
        return false;

    // eliminar captura
    if (hayFichaEn(nodo, destino))
        eliminarFichaEn(nodo, destino);

    // mover pieza
    ficha->setPosicion(destino);

    // cambiar turno
    nodo.turnoActual =
        (nodo.turnoActual == Color::Blanca)
        ? Color::Negra
        : Color::Blanca;

    return true;
}

// ======================================================

bool MoveExecutor::esMovimientoValido(
    const Nodo& nodo,
    int idFicha,
    const Posicion& destino
)
{
    const Ficha* ficha = nodo.obtenerFichaPorId(idFicha);

    if (!ficha)
        return false;

    if (!nodo.tablero)
        return false;

    const Ficha* target = nodo.obtenerFichaEn(destino.x, destino.y);

    if (target && target->getColor() == ficha->getColor())
        return false;

    return true;
}

// ======================================================

bool MoveExecutor::hayFichaEn(
    const Nodo& nodo,
    const Posicion& pos
)
{
    return nodo.hayFichaEn(pos.x, pos.y);
}

// ======================================================

void MoveExecutor::eliminarFichaEn(
    Nodo& nodo,
    const Posicion& pos
)
{
    for (auto it = nodo.piezas.begin(); it != nodo.piezas.end(); ++it)
    {
        if (it->getPosicion().x == pos.x &&
            it->getPosicion().y == pos.y)
        {
            nodo.piezas.erase(it);
            return;
        }
    }
}


Nodo* MoveExecutor::crearNodoMovimiento(
    const Nodo& origen,
    int idFicha,
    const Posicion& destino
)
{
    Nodo* nuevo = new Nodo(origen);

    ejecutarMovimiento(*nuevo, idFicha, destino);

    return nuevo;
}