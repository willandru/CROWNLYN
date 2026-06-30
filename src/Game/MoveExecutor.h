#pragma once

#include "Posicion.h"

class Nodo;
class Ficha;

class MoveExecutor
{
public:
    static bool ejecutarMovimiento(
        Nodo& nodo,
        int idFicha,
        const Posicion& destino
    );

    static bool esMovimientoValido(
        const Nodo& nodo,
        int idFicha,
        const Posicion& destino
    );

    static Nodo* crearNodoMovimiento(
        const Nodo& origen,
        int idFicha,
        const Posicion& destino
    );

private:
    static bool hayFichaEn(
        const Nodo& nodo,
        const Posicion& pos
    );

    static void eliminarFichaEn(
        Nodo& nodo,
        const Posicion& pos
    );
};