#pragma once

#include <string>

class Tablero
{
public:

    Tablero();

    Tablero(
        int ancho,
        int alto
    );

    int getAncho() const;

    int getAlto() const;

    bool esValida(
        int x,
        int y
    ) const;

    void setRutaImagen(
        const std::string& ruta
    );

    const std::string& getRutaImagen() const;

private:

    int ancho;
    int alto;

    std::string m_rutaImagen;
};