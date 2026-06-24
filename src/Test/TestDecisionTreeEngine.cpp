#include "TestDecisionTreeEngine.h"

#include "DecisionTreeEngine.h"
#include "Nodo.h"
#include "Ficha.h"

#include <iostream>

// =====================================================

void TestDecisionTreeEngine::ejecutar()
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "DECISION TREE ENGINE TESTS\n";
    std::cout << "=========================================\n";

    test_expandirNodo_null();

    test_nodoTerminal_noGeneraHijos();

    test_nodoConMovimientos_generaHijos();

    test_cambioTurno();

    test_hijoGenerado();

    resumen();
}

// =====================================================

void TestDecisionTreeEngine::verificar(
    const std::string& nombre,
    bool resultado)
{
    total++;

    if (resultado)
    {
        pass++;
        std::cout << "[PASS] " << nombre << "\n";
    }
    else
    {
        std::cout << "[FAIL] " << nombre << "\n";
    }
}

// =====================================================

void TestDecisionTreeEngine::resumen()
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "RESUMEN DECISION TREE ENGINE\n";
    std::cout << "=========================================\n";

    std::cout << "TOTAL : " << total << "\n";
    std::cout << "PASS  : " << pass << "\n";
    std::cout << "FAIL  : " << (total - pass) << "\n";

    std::cout << "=========================================\n";
}

// =====================================================
// NULL
// =====================================================

void TestDecisionTreeEngine::test_expandirNodo_null()
{
    DecisionTreeEngine engine;

    engine.expandirNodo(nullptr);

    verificar(
        "expandirNodo_null",
        true);
}

// =====================================================
// TERMINAL
// =====================================================

void TestDecisionTreeEngine::test_nodoTerminal_noGeneraHijos()
{
    DecisionTreeEngine engine;

    Nodo nodo;

    nodo.turnoActual = Color::Blanca;

    // estado terminal por tablas
    nodo.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}));

    engine.expandirNodo(&nodo);

    verificar(
        "nodoTerminal_noGeneraHijos",
        nodo.hijos.empty());
}

// =====================================================
// GENERA HIJOS
// =====================================================

void TestDecisionTreeEngine::test_nodoConMovimientos_generaHijos()
{
    DecisionTreeEngine engine;

    Nodo nodo;

    nodo.turnoActual = Color::Blanca;

    nodo.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Torre,
            Color::Blanca,
            {1,1}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}));

    engine.expandirNodo(&nodo);

    verificar(
        "nodoConMovimientos_generaHijos",
        !nodo.hijos.empty());
}

// =====================================================
// CAMBIO DE TURNO
// =====================================================

void TestDecisionTreeEngine::test_cambioTurno()
{
    DecisionTreeEngine engine;

    Nodo nodo;

    nodo.turnoActual = Color::Blanca;

    nodo.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Torre,
            Color::Blanca,
            {1,1}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}));

    engine.expandirNodo(&nodo);

    bool ok = false;

    if (!nodo.hijos.empty())
    {
        ok =
            nodo.hijos[0]->turnoActual
            == Color::Negra;
    }

    verificar(
        "cambioTurno",
        ok);
}

// =====================================================
// HIJO GENERADO
// =====================================================

void TestDecisionTreeEngine::test_hijoGenerado()
{
    DecisionTreeEngine engine;

    Nodo nodo;

    nodo.turnoActual = Color::Blanca;

    nodo.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Torre,
            Color::Blanca,
            {1,1}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}));

    engine.expandirNodo(&nodo);

    verificar(
        "hijoGenerado",
        nodo.hijos.size() > 0);
}