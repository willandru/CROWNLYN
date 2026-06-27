#pragma once

#include <vector>

#include "Posicion.h"

class ImagenManager;

enum class TipoFicha;

struct FichaVisual
{
    TipoFicha tipo;
    Posicion pos;
    const ImagenManager* textura;
};

class DrawFichaEngine
{
public:

    DrawFichaEngine();

    void addFicha(
        const FichaVisual& ficha
    );

    int getCantidadFichas() const;

    const FichaVisual& getFicha(
        int index
    ) const;

private:

    std::vector<FichaVisual> m_fichas;
};