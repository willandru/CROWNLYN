#include "TextureFichasLoader.h"

TextureFichasLoader::TextureFichasLoader()
{
    for (int c = 0; c < 2; c++)
        for (int t = 0; t < 6; t++)
            m_texturas[c][t] = nullptr;
}

TextureFichasLoader::~TextureFichasLoader()
{
    for (int c = 0; c < 2; c++)
        for (int t = 0; t < 6; t++)
            delete m_texturas[c][t];
}

void TextureFichasLoader::cargarTextura(
    Color color,
    TipoFicha tipo,
    const std::string& ruta
)
{
    ImagenManager*& slot = m_texturas[(int)color][(int)tipo];

    if (!slot)
    {
        slot = new ImagenManager();
        slot->cargar(ruta);
    }
}

void TextureFichasLoader::cargarBlancas()
{
    cargarTextura(Color::Blanca, TipoFicha::Torre,   "Debug/torre_blanca.png");
    cargarTextura(Color::Blanca, TipoFicha::Peon,    "Debug/peon_blanco.png");
    cargarTextura(Color::Blanca, TipoFicha::Alfil,   "Debug/alfil_blanco.png");
    cargarTextura(Color::Blanca, TipoFicha::Caballo, "Debug/caballo_blanco.png");
    cargarTextura(Color::Blanca, TipoFicha::Dama,    "Debug/dama_blanca.png");
    cargarTextura(Color::Blanca, TipoFicha::Rey,     "Debug/rey_blanco.png");
}

void TextureFichasLoader::cargarNegras()
{
    cargarTextura(Color::Negra, TipoFicha::Torre,   "Debug/torre_negra.png");
    cargarTextura(Color::Negra, TipoFicha::Peon,    "Debug/peon_negro.png");
    cargarTextura(Color::Negra, TipoFicha::Alfil,   "Debug/alfil_negro.png");
    cargarTextura(Color::Negra, TipoFicha::Caballo, "Debug/caballo_negro.png");
    cargarTextura(Color::Negra, TipoFicha::Dama,    "Debug/dama_negra.png");
    cargarTextura(Color::Negra, TipoFicha::Rey,     "Debug/rey_negro.png");
}

const ImagenManager* const* TextureFichasLoader::getTexturasBlancas() const
{
    return m_texturas[(int)Color::Blanca];
}

const ImagenManager* const* TextureFichasLoader::getTexturasNegras() const
{
    return m_texturas[(int)Color::Negra];
}

const ImagenManager* TextureFichasLoader::getTextura(
    TipoFicha tipo,
    Color color
) const
{
    return m_texturas[(int)color][(int)tipo];
}