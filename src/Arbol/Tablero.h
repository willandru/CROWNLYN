#pragma once

class Tablero
{
public:
    Tablero();
    Tablero(int ancho, int alto);

    int getAncho() const;
    int getAlto() const;

    void setDimensiones(int ancho, int alto);

    bool esValida(int x, int y) const;

private:
    int ancho;
    int alto;
};