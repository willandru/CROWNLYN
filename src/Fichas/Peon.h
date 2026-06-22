#pragma once

#include <vector>

#include "Ficha.h"

class Peon : public Ficha
{
public:
    Peon(Color color, Posicion pos);
    ~Peon() override;

    std::vector<Posicion> getMovimientos(const Nodo& estado) const override;

private:
    bool esValida(const Nodo& estado, int x, int y) const;
    bool esCasillaOcupada(const Nodo& estado, int x, int y) const;
    bool esCaptura(const Nodo& estado, int x, int y, const Ficha* piezaOrigen) const;
};