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

    void setArea(
        float x,
        float y,
        float width,
        float height
    );

    float getX() const;
    float getY() const;

    float getWidth() const;
    float getHeight() const;

    float getCellWidth() const;
    float getCellHeight() const;

    int getCasillaEn(
        float x,
        float y
    ) const;

private:

    int m_ancho;
    int m_alto;

    std::string m_rutaImagen;

    float m_x;
    float m_y;

    float m_width;
    float m_height;
};