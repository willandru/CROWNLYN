#pragma once

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

    void seleccionarFicha(
        int index
    );

    void deseleccionarFicha();

    void moverFicha(
        const Posicion& destino
    );

private:

    TableroBuilder* m_builder;

    int m_selectedIndex;

    bool m_haySeleccion;

    Posicion m_posSeleccionada;
};