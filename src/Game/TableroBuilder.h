#pragma once

#include "Ficha.h"

class Tablero;
class DrawFichaEngine;
class TextureFichasLoader;

class TableroBuilder
{
public:
    TableroBuilder(
        Tablero& tablero,
        DrawFichaEngine& fichaEngine,
        TextureFichasLoader& loader
    );

    void agregarTorre();

private:
    Tablero& m_tablero;
    DrawFichaEngine& m_fichaEngine;
    TextureFichasLoader& m_loader;
};