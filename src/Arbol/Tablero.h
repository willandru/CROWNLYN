#pragma once

class Tablero
{
public:
    Tablero(int ancho, int alto);

    int getAncho() const;
    int getAlto() const;

    bool esValida(int x, int y) const;

private:
    int ancho;
    int alto;
};