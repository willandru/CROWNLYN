#include "TestDecisionTreeEngine.h"

#include <iostream>

// =====================================================
// EJECUCIÓN
// =====================================================

void TestDecisionTreeEngine::ejecutar()
{
    total = 0;
    pass = 0;

    std::cout << "\n=========================================\n";
    std::cout << "DECISION TREE ENGINE TESTS\n";
    std::cout << "=========================================\n";

    // =====================================
    // EXPANSIÓN BÁSICA
    // =====================================

    test_NodoNull();

    test_NodoTerminal_NoGeneraHijos();

    test_NodoNoTerminal_GeneraHijos();

    // =====================================
    // CAMBIO DE TURNO
    // =====================================

    test_CambioTurno_BlancaANegra();

    test_CambioTurno_NegraABlanca();

    // =====================================
    // GENERACIÓN DE HIJOS
    // =====================================

    test_MultiplesHijos();

    test_CapturaGeneraMenosPiezas();

    // =====================================
    // FILTRO DE MOVIMIENTOS
    // =====================================

    test_NoGeneraMovimientoIlegal();

    test_SoloMovimientosLegales();

    // =====================================
    // BUGS DE REGRESIÓN
    // =====================================

    test_Bug_PeonBordeSuperior();

    test_Bug_PeonSinMovimientos();

    test_Bug_EstadoTerminalExpandido();

    // =====================================
    // INTEGRACIÓN
    // =====================================

    test_ExpandirUnaVez();

    test_ExpandirConCaptura();

    test_ExpandirConVariasOpciones();

    resumen();
}

// =====================================================
// UTILIDADES
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
    std::cout << "\n=========================================\n";
    std::cout << "RESUMEN DECISION TREE ENGINE\n";
    std::cout << "=========================================\n";

    std::cout << "TOTAL : " << total << "\n";
    std::cout << "PASS  : " << pass << "\n";
    std::cout << "FAIL  : " << (total - pass) << "\n";

    std::cout << "=========================================\n";
}

// =====================================================
// EXPANSIÓN BÁSICA
// =====================================================

void TestDecisionTreeEngine::test_NodoNull()
{
    verificar(
        "NodoNull",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_NodoTerminal_NoGeneraHijos()
{
    verificar(
        "NodoTerminal_NoGeneraHijos",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_NodoNoTerminal_GeneraHijos()
{
    verificar(
        "NodoNoTerminal_GeneraHijos",
        false);
}

// =====================================================
// CAMBIO DE TURNO
// =====================================================

void TestDecisionTreeEngine::test_CambioTurno_BlancaANegra()
{
    verificar(
        "CambioTurno_BlancaANegra",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_CambioTurno_NegraABlanca()
{
    verificar(
        "CambioTurno_NegraABlanca",
        false);
}

// =====================================================
// GENERACIÓN DE HIJOS
// =====================================================

void TestDecisionTreeEngine::test_MultiplesHijos()
{
    verificar(
        "MultiplesHijos",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_CapturaGeneraMenosPiezas()
{
    verificar(
        "CapturaGeneraMenosPiezas",
        false);
}

// =====================================================
// FILTRO DE MOVIMIENTOS
// =====================================================

void TestDecisionTreeEngine::test_NoGeneraMovimientoIlegal()
{
    verificar(
        "NoGeneraMovimientoIlegal",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_SoloMovimientosLegales()
{
    verificar(
        "SoloMovimientosLegales",
        false);
}

// =====================================================
// BUGS DE REGRESIÓN
// =====================================================

void TestDecisionTreeEngine::test_Bug_PeonBordeSuperior()
{
    verificar(
        "Bug_PeonBordeSuperior",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_Bug_PeonSinMovimientos()
{
    verificar(
        "Bug_PeonSinMovimientos",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_Bug_EstadoTerminalExpandido()
{
    verificar(
        "Bug_EstadoTerminalExpandido",
        false);
}

// =====================================================
// INTEGRACIÓN
// =====================================================

void TestDecisionTreeEngine::test_ExpandirUnaVez()
{
    verificar(
        "ExpandirUnaVez",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_ExpandirConCaptura()
{
    verificar(
        "ExpandirConCaptura",
        false);
}

// =====================================================

void TestDecisionTreeEngine::test_ExpandirConVariasOpciones()
{
    verificar(
        "ExpandirConVariasOpciones",
        false);
}