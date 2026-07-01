#pragma once

#include "Nodo.h"
#include "TextureFichasLoader.h"

class Tablero;

class TableroBuilder
{
public:

    TableroBuilder();

    //==================================================
    // NODO OBJETIVO
    //==================================================

    void setNodo(
        Nodo* nodo
    );

    Nodo* getNodo();

    const Nodo* getNodo() const;

    //==================================================
    // CONSTRUCCIÓN DEL TABLERO
    //==================================================

    void crearTablero(
        int ancho,
        int alto,
        float x = 300.0f,
        float y = 30.0f,
        float w = 450.0f,
        float h = 450.0f
    );

    void clear();

    //==================================================
    // CONSTRUCCIÓN DE PIEZAS
    //==================================================

    void agregarFicha(
        TipoFicha tipo,
        Color color,
        const Posicion& pos
    );

    void agregarFilaPeones(
        Color color
    );

    void agregarPiezasIniciales(
        Color color
    );

    void crearConfiguracionInicial();

    void avanzarNodo(
        Nodo* nodo
    );

    //==================================================
    // RECURSOS
    //==================================================

    TextureFichasLoader&
    getTextureLoader();

    const TextureFichasLoader&
    getTextureLoader() const;

    

private:

    Nodo* m_nodo = nullptr;

    TextureFichasLoader m_loader;

    int m_nextId = 0;
};