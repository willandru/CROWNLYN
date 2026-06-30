#pragma once

#include <vector>

#include "Posicion.h"

class Input;
class TableroBuilder;

class PlayFichaEngine
{
public:

    PlayFichaEngine();

    void setBuilder(
        TableroBuilder* builder
    );

    void update(
        const Input& input
    );

    bool hayFichaSeleccionada() const;

    int getFichaSeleccionada() const;

    const std::vector<Posicion>&
    getMovimientosPosibles() const;

private:

    int obtenerFichaEnMouse(
        float mouseX,
        float mouseY,
        Posicion& outPos
    );

    bool obtenerCasillaEnMouse(
        float mouseX,
        float mouseY,
        Posicion& outPos
    );

    bool estaDentroDelTablero(
        float mouseX,
        float mouseY
    ) const;

    bool esMovimientoPosible(
        const Posicion& pos
    ) const;

    void seleccionarFicha(
        int idFicha
    );

    void deseleccionarFicha();

    void moverFicha(
        const Posicion& destino
    );

private:

    TableroBuilder* m_builder = nullptr;

    int m_selectedId = -1;

    bool m_haySeleccion = false;

    Posicion m_posSeleccionada;

    std::vector<Posicion> m_movimientosPosibles;
};