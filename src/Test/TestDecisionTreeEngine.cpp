#include "TestDecisionTreeEngine.h"

#include "DecisionTreeEngine.h"
#include "Nodo.h"
#include "Ficha.h"

#include <iostream>

// =====================================================
// COLORES ANSI
// =====================================================

static constexpr const char* RESET   = "\033[0m";
static constexpr const char* VERDE   = "\033[32m";
static constexpr const char* ROJO    = "\033[31m";
static constexpr const char* CYAN    = "\033[36m";
static constexpr const char* TITLE    = "\033[93m";

// =====================================================

void TestDecisionTreeEngine::ejecutar()
{
    std::cout << "\n";

    std::cout << TITLE;
    std::cout << "=========================================\n";
    std::cout << "DECISION TREE ENGINE TESTS\n";
    std::cout << "=========================================\n";
    std::cout << RESET;

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

        std::cout
            << VERDE
            << "[PASS] "
            << RESET
            << nombre
            << "\n";
    }
    else
    {
        std::cout
            << ROJO
            << "[FAIL] "
            << RESET
            << nombre
            << "\n";
    }
}

// =====================================================

void TestDecisionTreeEngine::resumen()
{
    int fail = total - pass;

    std::cout << "\n";

    std::cout << CYAN;
    std::cout << "=========================================\n";
    std::cout << "RESUMEN DECISION TREE ENGINE\n";
    std::cout << "=========================================\n";
    std::cout << RESET;

    std::cout
        << "TOTAL : "
        << total
        << "\n";

    std::cout
        << VERDE
        << "PASS  : "
        << pass
        << RESET
        << "\n";

    std::cout
        << ROJO
        << "FAIL  : "
        << fail
        << RESET
        << "\n";

    std::cout << CYAN;
    std::cout << "=========================================\n";
    std::cout << RESET;
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

    nodo.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0, 0}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2, 2}));

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
            {1, 1}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2, 2}));

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
            {1, 1}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2, 2}));

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
            {1, 1}));

    nodo.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2, 2}));

    engine.expandirNodo(&nodo);

    verificar(
        "hijoGenerado",
        nodo.hijos.size() > 0);
}