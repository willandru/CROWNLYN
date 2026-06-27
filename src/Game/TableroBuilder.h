#pragma once

#include "Tablero.h"
#include "DrawFichaEngine.h"
#include "TextureFichasLoader.h"

class TableroBuilder
{
public:

    TableroBuilder();

    void crearTablero(
        int ancho,
        int alto,
        float x = 300.0f,
        float y = 30.0f,
        float w = 450.0f,
        float h = 450.0f
    );

    void agregarFicha(
        TipoFicha tipo,
        Color color,
        const Posicion& pos
    );

    void agregarTorre();

    void clear();

    const Tablero& getTablero() const;

    DrawFichaEngine& getFichaEngine();

    TextureFichasLoader& getTextureLoader();

private:

    Tablero m_tablero;

    DrawFichaEngine m_fichaEngine;

    TextureFichasLoader m_loader;

    int m_nextId;
};