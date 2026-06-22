#pragma once

#include <vector>

#include "Ficha.h"

class Rey : public Ficha
{
public:
    Rey(Color color, Posicion pos);
    ~Rey() override;

    std::vector<Posicion> getMovimientos(const Nodo& estado) const override;

private:
    bool esValida(const Nodo& estado, int x, int y) const;
    bool esCasillaOcupada(const Nodo& estado, int x, int y) const;
    bool esCaptura(const Nodo& estado, int x, int y, const Ficha* piezaOrigen) const;
};