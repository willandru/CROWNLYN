#pragma once

#include <string>
#include "ImagenManager.h"
#include "Ficha.h"

class TextureFichasLoader
{
public:

    TextureFichasLoader();
    ~TextureFichasLoader();

    void cargarBlancas();
    void cargarNegras();

    // acceso por fila (color completo)
    const ImagenManager* const* getTexturasBlancas() const;
    const ImagenManager* const* getTexturasNegras() const;

    // acceso directo (tipo + color)
    const ImagenManager* getTextura(
        TipoFicha tipo,
        Color color
    ) const;

private:

    ImagenManager* m_texturas[2][6];

    void cargarTextura(
        Color color,
        TipoFicha tipo,
        const std::string& ruta
    );
};