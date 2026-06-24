#include "TestGameAnalyzer.h"

#include <iostream>

// =====================================================
// EJECUCIÓN
// =====================================================

void TestGameAnalyzer::ejecutar()
{
    total = 0;
    pass = 0;

    std::cout << "\n=========================================\n";
    std::cout << "GAME ANALYZER TESTS\n";
    std::cout << "=========================================\n";

    // =====================================
    // VALIDACIÓN DE ESTADOS
    // =====================================

    test_EstadoInicialValido();
    test_EstadoInicialInvalido_SinNegras();
    test_EstadoInicialInvalido_AmbosEnJaque();

    // =====================================
    // JAQUE
    // =====================================

    test_BlancoEnJaque();
    test_NegroEnJaque();
    test_SinJaque();

    // =====================================
    // MOVIMIENTOS
    // =====================================

    test_BlancoTieneMovimientos();
    test_BlancoSinMovimientos();

    test_NegroTieneMovimientos();
    test_NegroSinMovimientos();

    // =====================================
    // TURNO INICIAL
    // =====================================

    test_SugerirTurno_Blanco();
    test_SugerirTurno_Negro();

    resumen();
}

// =====================================================
// UTILIDADES
// =====================================================

void TestGameAnalyzer::verificar(
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

void TestGameAnalyzer::resumen()
{
    std::cout << "\n=========================================\n";
    std::cout << "RESUMEN GAME ANALYZER\n";
    std::cout << "=========================================\n";

    std::cout << "TOTAL : " << total << "\n";
    std::cout << "PASS  : " << pass << "\n";
    std::cout << "FAIL  : " << (total - pass) << "\n";

    std::cout << "=========================================\n";
}

// =====================================================
// VALIDACIÓN DE ESTADOS
// =====================================================

void TestGameAnalyzer::test_EstadoInicialValido()
{
    verificar(
        "EstadoInicialValido",
        false);
}

// =====================================================

void TestGameAnalyzer::test_EstadoInicialInvalido_SinNegras()
{
    verificar(
        "EstadoInicialInvalido_SinNegras",
        false);
}

// =====================================================

void TestGameAnalyzer::test_EstadoInicialInvalido_AmbosEnJaque()
{
    verificar(
        "EstadoInicialInvalido_AmbosEnJaque",
        false);
}

// =====================================================
// JAQUE
// =====================================================

void TestGameAnalyzer::test_BlancoEnJaque()
{
    verificar(
        "BlancoEnJaque",
        false);
}

// =====================================================

void TestGameAnalyzer::test_NegroEnJaque()
{
    verificar(
        "NegroEnJaque",
        false);
}

// =====================================================

void TestGameAnalyzer::test_SinJaque()
{
    verificar(
        "SinJaque",
        false);
}

// =====================================================
// MOVIMIENTOS
// =====================================================

void TestGameAnalyzer::test_BlancoTieneMovimientos()
{
    verificar(
        "BlancoTieneMovimientos",
        false);
}

// =====================================================

void TestGameAnalyzer::test_BlancoSinMovimientos()
{
    verificar(
        "BlancoSinMovimientos",
        false);
}

// =====================================================

void TestGameAnalyzer::test_NegroTieneMovimientos()
{
    verificar(
        "NegroTieneMovimientos",
        false);
}

// =====================================================

void TestGameAnalyzer::test_NegroSinMovimientos()
{
    verificar(
        "NegroSinMovimientos",
        false);
}

// =====================================================
// TURNO INICIAL
// =====================================================

void TestGameAnalyzer::test_SugerirTurno_Blanco()
{
    verificar(
        "SugerirTurno_Blanco",
        false);
}

// =====================================================

void TestGameAnalyzer::test_SugerirTurno_Negro()
{
    verificar(
        "SugerirTurno_Negro",
        false);
}