#include "TestSuite.h"

#include "TestGameAnalyzer.h"
#include "TestStates.h"
#include "TestDecisionTreeEngine.h"

#include <iostream>

// =====================================================
// EJECUCIÓN COMPLETA
// =====================================================

void TestSuite::ejecutar()
{
    imprimirCabecera();

    TestGameAnalyzer gameAnalyzer;
    gameAnalyzer.ejecutar();

    TestStates states;
    states.ejecutar();

    TestDecisionTreeEngine engine;
    engine.ejecutar();

    imprimirPie();
}

// =====================================================
// CABECERA
// =====================================================

void TestSuite::imprimirCabecera() const
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "         CROWNLYN TEST SUITE\n";
    std::cout << "=========================================\n";
}

// =====================================================
// PIE
// =====================================================

void TestSuite::imprimirPie() const
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "       FIN CROWNLYN TEST SUITE\n";
    std::cout << "=========================================\n";
}