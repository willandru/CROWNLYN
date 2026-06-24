#include <iostream>

#include "Arbol.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"

#include "GameAnalyzer.h"

int main()
{
    Nodo* raiz = new Nodo();

    raiz->tablero = Tablero(3, 3);
    raiz->turnoActual = Color::Blanca;

    // Rey negro
    raiz->piezas.push_back(Ficha(1, TipoFicha::Peon, Color::Blanca, {0, 0}));
    // Rey negro
    raiz->piezas.push_back(Ficha(1, TipoFicha::Torre, Color::Negra, {0, 1}));


    // ======================================================
    // VALIDACIÓN DE ESTADO INICIAL (NUEVO)
    // ======================================================

    GameAnalyzer analyzer;

    if (!analyzer.estadoInicialValido(*raiz))
    {
        std::cout << "[INIT] Estado inválido (sin ambos bandos). Abortando.\n";
        return 0;
    }

    Color turnoCorregido = analyzer.sugerirTurnoInicial(*raiz);
    raiz->turnoActual = turnoCorregido;

    std::cout << "[INIT] Turno inicial asignado: "
              << (turnoCorregido == Color::Blanca ? "Blanca" : "Negra")
              << "\n";




    // ARBOL
    // ======================================================
    Arbol arbol;
    arbol.setNodoInicial(raiz);


    // ======================================================
    // VISUALIZAR ARBOL
    // ======================================================

    std::cout << "\n=== NIVEL 1 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();
    arbol.resumenNivel();

    std::cout << "\n=== NIVEL 2 ===\n";
    arbol.construirSiguienteNivel();
    arbol.imprimirNivel();
    arbol.resumenNivel();

    
    std::cout << "\n=== NIVEL 3 ===\n";
    arbol.construirSiguienteNivel();
    //arbol.imprimirNivel();
    arbol.resumenNivel();

    /*
    std::cout << "\n=== NIVEL 4 ===\n";
    arbol.construirSiguienteNivel();
    //arbol.imprimirNivel();
    arbol.resumenNivel();
    
    
    
     std::cout << "\n=== NIVEL 5 ===\n";
    arbol.construirSiguienteNivel();
    //arbol.imprimirNivel();
    arbol.resumenNivel();
    */
    


    
    


    return 0;
}