#pragma once

#include <vector>

#include "Ficha.h"

class Torre : public Ficha
{
public:
    Torre(Color color, Posicion pos);
    ~Torre() override;

    std::vector<Posicion> getMovimientos(const Nodo& estado) const override;

private:
    bool esValida(const Nodo& estado, int x, int y) const;
    bool esCasillaOcupada(const Nodo& estado, int x, int y) const;
    bool esCaptura(const Nodo& estado, int x, int y, const Ficha* piezaOrigen) const;
};