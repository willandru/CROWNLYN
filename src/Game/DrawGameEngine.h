#pragma once

class Renderer;
class Shader;

class TableroBuilder;
class DrawTableroEngine;
class PlayFichaEngine;

class DrawGameEngine
{
public:

    DrawGameEngine();

    void setBuilder(
        TableroBuilder* builder
    );

    void setTableroEngine(
        DrawTableroEngine* engine
    );

    void setPlayEngine(
        PlayFichaEngine* engine
    );

    void draw(
        Renderer& renderer,
        Shader& basicShader,
        Shader& textureShader
    );

private:

    TableroBuilder* m_builder = nullptr;

    DrawTableroEngine* m_tableroEngine = nullptr;

    PlayFichaEngine* m_playEngine = nullptr;
};