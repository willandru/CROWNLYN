#pragma once

#include <vector>
#include "Ficha.h"

class DrawFichaEngine
{
public:

    DrawFichaEngine();

    void addFicha(
        const Ficha& ficha
    );

    int getCantidadFichas() const;

    Ficha& getFicha(
        int index
    );

    const Ficha& getFicha(
        int index
    ) const;

    void clear();

private:

    std::vector<Ficha> m_fichas;
};