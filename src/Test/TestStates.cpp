#include "TestStates.h"

#include <iostream>

#include "Nodo.h"
#include "Ficha.h"

#include "GameAnalyzer.h"
#include "StateEvaluator.h"
#include "DecisionTreeEngine.h"

using namespace std;

// ======================================================

void TestStates::ejecutar()
{
    cout << "\n";
    cout << "=========================================\n";
    cout << "TEST STATES\n";
    cout << "=========================================\n";

    test_EstadoInicialValido();

    test_EstadoInicialInvalido_SinNegras();

    test_Tablas_MismoTipo();

    test_NoTablas_TiposDistintos();

    test_BlancoSinMovimientos();

    test_NegroSinMovimientos();

    test_EstadoTerminal_SinMovimientos();

    test_NodoTerminal_NoGeneraHijos();

    test_NodoNoTerminal_GeneraHijos();

    resumen();
}

// ======================================================

void TestStates::verificar(
    const string& nombre,
    bool resultado)
{
    total++;

    if (resultado)
    {
        pass++;

        cout
            << "[PASS] "
            << nombre
            << "\n";
    }
    else
    {
        cout
            << "[FAIL] "
            << nombre
            << "\n";
    }
}

// ======================================================

void TestStates::resumen()
{
    cout << "\n";
    cout << "=========================================\n";
    cout << "RESUMEN\n";
    cout << "=========================================\n";

    cout << "TOTAL : " << total << "\n";
    cout << "PASS  : " << pass << "\n";
    cout << "FAIL  : " << (total - pass) << "\n";

    cout << "=========================================\n";
}

// ======================================================

void TestStates::test_EstadoInicialValido()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {1,1}));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {2,2}));

    GameAnalyzer analyzer;

    verificar(
        "EstadoInicialValido",
        analyzer.estadoInicialValido(estado));
}

// ======================================================

void TestStates::test_EstadoInicialInvalido_SinNegras()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {1,1}));

    GameAnalyzer analyzer;

    verificar(
        "EstadoInicialInvalido_SinNegras",
        !analyzer.estadoInicialValido(estado));
}

// ======================================================

void TestStates::test_Tablas_MismoTipo()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {1,1}));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}));

    StateEvaluator evaluator;

    verificar(
        "Tablas_MismoTipo",
        evaluator.esTablas(estado));
}

// ======================================================

void TestStates::test_NoTablas_TiposDistintos()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {1,1}));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {2,2}));

    StateEvaluator evaluator;

    verificar(
        "NoTablas_TiposDistintos",
        !evaluator.esTablas(estado));
}

// ======================================================

void TestStates::test_BlancoSinMovimientos()
{
    Nodo estado;

    estado.turnoActual = Color::Blanca;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {0,1}));

    StateEvaluator evaluator;

    verificar(
        "BlancoSinMovimientos",
        evaluator.sinMovimientos(
            estado,
            Color::Blanca));
}

// ======================================================

void TestStates::test_NegroSinMovimientos()
{
    Nodo estado;

    estado.turnoActual = Color::Negra;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Torre,
            Color::Blanca,
            {0,1}));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}));

    StateEvaluator evaluator;

    verificar(
        "NegroSinMovimientos",
        evaluator.sinMovimientos(
            estado,
            Color::Negra));
}

// ======================================================

void TestStates::test_EstadoTerminal_SinMovimientos()
{
    Nodo estado;

    estado.turnoActual = Color::Blanca;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {0,1}));

    StateEvaluator evaluator;

    verificar(
        "EstadoTerminal_SinMovimientos",
        evaluator.estadoTerminal(
            estado,
            Color::Blanca));
}

// ======================================================

void TestStates::test_NodoTerminal_NoGeneraHijos()
{
    Nodo* raiz = new Nodo();

    raiz->turnoActual = Color::Blanca;

    raiz->piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}));

    raiz->piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {0,1}));

    DecisionTreeEngine engine;

    engine.expandirNodo(raiz);

    verificar(
        "NodoTerminal_NoGeneraHijos",
        raiz->hijos.empty());

    delete raiz;
}

// ======================================================

void TestStates::test_NodoNoTerminal_GeneraHijos()
{
    Nodo* raiz = new Nodo();

    raiz->turnoActual = Color::Negra;

    raiz->piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}));

    raiz->piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {0,1}));

    DecisionTreeEngine engine;

    engine.expandirNodo(raiz);

    verificar(
        "NodoNoTerminal_GeneraHijos",
        !raiz->hijos.empty());

    for (Nodo* h : raiz->hijos)
        delete h;

    delete raiz;
}