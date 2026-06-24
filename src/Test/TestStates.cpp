#include "TestStates.h"

#include "StateEvaluator.h"
#include "Nodo.h"
#include "Ficha.h"

#include <iostream>

// =====================================================
// EJECUCIÓN
// =====================================================

void TestStates::ejecutar()
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "STATE EVALUATOR TESTS\n";
    std::cout << "=========================================\n";

    test_esTablas_true();
    test_esTablas_false();

    test_esDerrota_true();
    test_esDerrota_false();

    test_sinMovimientos_true();
    test_sinMovimientos_false();

    resumen();
}

// =====================================================
// VERIFICAR
// =====================================================

void TestStates::verificar(
    const std::string& nombre,
    bool resultado)
{
    total++;

    if (resultado)
    {
        pass++;

        std::cout
            << "[PASS] "
            << nombre
            << "\n";
    }
    else
    {
        std::cout
            << "[FAIL] "
            << nombre
            << "\n";
    }
}

// =====================================================
// RESUMEN
// =====================================================

void TestStates::resumen()
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "RESUMEN STATE EVALUATOR\n";
    std::cout << "=========================================\n";

    std::cout << "TOTAL : " << total << "\n";
    std::cout << "PASS  : " << pass << "\n";
    std::cout << "FAIL  : " << (total - pass) << "\n";

    std::cout << "=========================================\n";
}

// =====================================================
// esTablas() TRUE
// =====================================================

void TestStates::test_esTablas_true()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}
        ));

    StateEvaluator eval;

    verificar(
        "esTablas_true",
        eval.esTablas(estado));
}

// =====================================================
// esTablas() FALSE
// =====================================================

void TestStates::test_esTablas_false()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {2,2}
        ));

    StateEvaluator eval;

    verificar(
        "esTablas_false",
        !eval.esTablas(estado));
}

// =====================================================
// esDerrota() TRUE
// =====================================================

void TestStates::test_esDerrota_true()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Negra,
            {1,1}
        ));

    StateEvaluator eval;

    verificar(
        "esDerrota_true",
        eval.esDerrota(estado));
}

// =====================================================
// esDerrota() FALSE
// =====================================================

void TestStates::test_esDerrota_false()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {1,1}
        ));

    StateEvaluator eval;

    verificar(
        "esDerrota_false",
        !eval.esDerrota(estado));
}

// =====================================================
// sinMovimientos() TRUE
// =====================================================

void TestStates::test_sinMovimientos_true()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0,0}
        ));

    StateEvaluator eval;

    verificar(
        "sinMovimientos_true",
        eval.sinMovimientos(
            estado,
            Color::Blanca));
}

// =====================================================
// sinMovimientos() FALSE
// =====================================================

void TestStates::test_sinMovimientos_false()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Torre,
            Color::Blanca,
            {1,1}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Peon,
            Color::Negra,
            {2,2}
        ));

    StateEvaluator eval;

    verificar(
        "sinMovimientos_false",
        !eval.sinMovimientos(
            estado,
            Color::Blanca));
}