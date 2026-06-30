#include "GameEngine.h"

#include "TableroBuilder.h"
#include "PlayFichaEngine.h"
#include "DrawGameEngine.h"
#include "Input.h"
#include "Renderer.h"
#include "Shader.h"
#include "Nodo.h"

// ======================================================

GameEngine::GameEngine()
{
    m_builder = new TableroBuilder();
    m_playEngine = new PlayFichaEngine();
    m_drawEngine = new DrawGameEngine();
}

// ======================================================

void GameEngine::init()
{
    Nodo* root = new Nodo();

    m_builder->setNodo(root);
    m_builder->crearTablero(8, 8);
    m_builder->crearConfiguracionInicial();

    m_playEngine->setBuilder(m_builder);
    m_drawEngine->setBuilder(m_builder);
}

// ======================================================

void GameEngine::update(const Input& input)
{
    m_playEngine->update(input);
}

// ======================================================

void GameEngine::render(Renderer& renderer, Shader& basic, Shader& texture)
{
    m_drawEngine->draw(renderer, basic, texture);
}