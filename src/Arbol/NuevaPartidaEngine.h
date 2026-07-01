#pragma once

class Arbol;
class Nodo;
class TableroBuilder;

class NuevaPartidaEngine
{
public:

    NuevaPartidaEngine();

    Nodo* crearPartida(
        Arbol& arbol,
        TableroBuilder& builder
    );
};