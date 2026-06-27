#pragma once

class Tablero;
class DrawFichaEngine;
class ImagenManager;

class TableroBuilder
{
public:

    // crea tablero base (ej: 3x3)
    TableroBuilder(
        Tablero& tablero,
        DrawFichaEngine& fichaEngine
    );

    // coloca una torre fija en (0,2)
    void agregarTorre();

private:

    Tablero& m_tablero;
    DrawFichaEngine& m_fichaEngine;

    ImagenManager* m_torreTexture;
};