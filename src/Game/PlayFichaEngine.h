#pragma once

#include <vector>

#include "Posicion.h"

class Renderer;
class Shader;
class Input;
class Tablero;
class ImagenManager;

enum class TipoFicha;

// =========================
// VISUAL PIECE
// =========================

struct FichaVisual
{
    TipoFicha tipo;
    Posicion pos;
    const ImagenManager* textura;
};

class PlayFichaEngine
{
public:
    PlayFichaEngine();

    void setTablero(Tablero* tablero);

    void addFicha(const FichaVisual& ficha);

    // por ahora no hace nada
    void update(const Input& input);

    void render(
        Renderer& renderer,
        Shader& shader
    );

    int seleccionarFicha(
        float mouseX,
        float mouseY
    );

private:
    Tablero* m_tablero;

    std::vector<FichaVisual> m_fichas;
    
    int m_selectedIndex;
};