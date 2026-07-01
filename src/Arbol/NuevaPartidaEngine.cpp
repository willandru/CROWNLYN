#include "NuevaPartidaEngine.h"

#include "Arbol.h"
#include "Nodo.h"
#include "TableroBuilder.h"

NuevaPartidaEngine::NuevaPartidaEngine()
{
}

Nodo* NuevaPartidaEngine::crearPartida(
    Arbol& arbol,
    TableroBuilder& builder
)
{
    Nodo* nodoRaiz = new Nodo();

    builder.setNodo(
        nodoRaiz
    );

    builder.crearTablero(
        8,
        8
    );

    builder.crearConfiguracionInicial();

    nodoRaiz->turnoActual =
        Color::Blanca;

    arbol.setNodoInicial(
        nodoRaiz
    );

    return nodoRaiz;
}