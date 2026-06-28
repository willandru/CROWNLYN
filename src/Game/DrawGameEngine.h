#pragma once

class Renderer;
class Shader;

class TableroBuilder;
class DrawTableroEngine;

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

    void draw(
        Renderer& renderer,
        Shader& basicShader,
        Shader& textureShader
    );

private:

    TableroBuilder* m_builder;

    DrawTableroEngine* m_tableroEngine;
};