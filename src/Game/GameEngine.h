#pragma once

class Renderer;
class Shader;
class Input;

class TableroBuilder;
class PlayFichaEngine;
class DrawGameEngine;

class GameEngine
{
public:
    GameEngine();

    void init();

    void update(const Input& input);

    void render(Renderer& renderer, Shader& basic, Shader& texture);

private:

    TableroBuilder* m_builder;

    PlayFichaEngine* m_playEngine;

    DrawGameEngine* m_drawEngine;
};