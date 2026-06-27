#include "DrawFichaEngine.h"

DrawFichaEngine::DrawFichaEngine()
{
}

void DrawFichaEngine::addFicha(const Ficha& ficha)
{
    m_fichas.push_back(ficha);
}

int DrawFichaEngine::getCantidadFichas() const
{
    return static_cast<int>(m_fichas.size());
}

const Ficha& DrawFichaEngine::getFicha(int index) const
{
    return m_fichas[index];
}

void DrawFichaEngine::clear()
{
    m_fichas.clear();
}