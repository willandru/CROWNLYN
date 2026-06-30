#pragma once

#include <vector>

#include "Ficha.h"

class Nodo;

class GameAnalyzer
{
public:
    bool estaEnJaque(const Nodo& estado, Color color) const;

    bool casillaAtacada(
        const Nodo& estado,
        int x,
        int y,
        Color atacante) const;

    Nodo simularMovimiento(
        const Nodo& estado,
        const Ficha& ficha,
        const Posicion& destino) const;

    bool esMovimientoLegal(
        const Nodo& estado,
        const Ficha& ficha,
        const Posicion& destino) const;

    bool tieneMovimientosLegales(
        const Nodo& estado,
        Color color) const;

    const Ficha* encontrarRey(
        const Nodo& estado,
        Color color) const;

    std::vector<Posicion> obtenerMovimientosFicha(
        const Ficha& f,
        const Nodo& estado) const;

    std::vector<Posicion> obtenerAtaquesFicha(
        const Ficha& f,
        const Nodo& estado) const;

    bool estadoInicialValido(const Nodo& estado) const;

    Color sugerirTurnoInicial(const Nodo& estado) const;

private:
    const Ficha* obtenerFichaEn(
        const Nodo& estado,
        int x,
        int y) const;
};