#include "DrawFichaEngine.h"

DrawFichaEngine::DrawFichaEngine()
{
}

void DrawFichaEngine::addFicha(
    const FichaVisual& ficha
)
{
    m_fichas.push_back(ficha);
}

int DrawFichaEngine::getCantidadFichas() const
{
    return static_cast<int>(
        m_fichas.size()
    );
}

const FichaVisual& DrawFichaEngine::getFicha(
    int index
) const
{
    return m_fichas[index];
}