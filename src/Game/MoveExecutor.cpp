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
    //--------------------------------------------------
    // VALIDAR TABLERO
    //--------------------------------------------------

    if (!nodo.tablero)
        return false;

    //--------------------------------------------------
    // OBTENER FICHA
    //--------------------------------------------------

    Ficha* ficha =
        nodo.obtenerFichaPorId(idFicha);

    if (!ficha)
        return false;

    //--------------------------------------------------
    // VALIDAR TURNO
    //--------------------------------------------------

    if (
        ficha->getColor() !=
        nodo.turnoActual
    )
    {
        return false;
    }

    //--------------------------------------------------
    // VALIDAR DESTINO
    //--------------------------------------------------

    const Ficha* target =
        nodo.obtenerFichaEn(
            destino.x,
            destino.y
        );

    if (
        target &&
        target->getColor() ==
        ficha->getColor()
    )
    {
        return false;
    }

    //--------------------------------------------------
    // CAPTURA
    //--------------------------------------------------

    if (
        hayFichaEn(
            nodo,
            destino
        )
    )
    {
        eliminarFichaEn(
            nodo,
            destino
        );

        // IMPORTANTE:
        // erase() invalida punteros del vector.
        ficha =
            nodo.obtenerFichaPorId(
                idFicha
            );

        if (!ficha)
            return false;
    }

    //--------------------------------------------------
    // MOVER FICHA
    //--------------------------------------------------

    ficha->setPosicion(
        destino
    );

    //--------------------------------------------------
    // CAMBIAR TURNO
    //--------------------------------------------------

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
    if (!nodo.tablero)
        return false;

    const Ficha* ficha =
        nodo.obtenerFichaPorId(
            idFicha
        );

    if (!ficha)
        return false;

    const Ficha* target =
        nodo.obtenerFichaEn(
            destino.x,
            destino.y
        );

    if (
        target &&
        target->getColor() ==
        ficha->getColor()
    )
    {
        return false;
    }

    return true;
}

// ======================================================

bool MoveExecutor::hayFichaEn(
    const Nodo& nodo,
    const Posicion& pos
)
{
    return nodo.hayFichaEn(
        pos.x,
        pos.y
    );
}

// ======================================================

void MoveExecutor::eliminarFichaEn(
    Nodo& nodo,
    const Posicion& pos
)
{
    for (
        auto it = nodo.piezas.begin();
        it != nodo.piezas.end();
        ++it
    )
    {
        if (
            it->getPosicion().x == pos.x &&
            it->getPosicion().y == pos.y
        )
        {
            nodo.piezas.erase(it);
            return;
        }
    }
}

// ======================================================

Nodo* MoveExecutor::crearNodoMovimiento(
    const Nodo& origen,
    int idFicha,
    const Posicion& destino
)
{
    Nodo* nuevo =
        new Nodo(origen);

    if (
        !ejecutarMovimiento(
            *nuevo,
            idFicha,
            destino
        )
    )
    {
        delete nuevo;
        return nullptr;
    }

    return nuevo;
}