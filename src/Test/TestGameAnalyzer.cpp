#include "TestGameAnalyzer.h"

#include "GameAnalyzer.h"
#include "Nodo.h"
#include "Ficha.h"

#include <iostream>

// =====================================================
// EJECUCIÓN
// =====================================================

void TestGameAnalyzer::ejecutar()
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "GAME ANALYZER TESTS\n";
    std::cout << "=========================================\n";

    test_EncontrarRey_Blanco();
    test_EncontrarRey_Negro();
    test_EncontrarRey_NoExiste();

    test_EstadoInicialValido();
    test_EstadoInicialInvalido_SinNegras();

    test_BlancoEnJaque();
    test_SinJaque();

    resumen();
}

// =====================================================
// VERIFICAR
// =====================================================

void TestGameAnalyzer::verificar(
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

void TestGameAnalyzer::resumen()
{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "RESUMEN GAME ANALYZER\n";
    std::cout << "=========================================\n";

    std::cout << "TOTAL : " << total << "\n";
    std::cout << "PASS  : " << pass << "\n";
    std::cout << "FAIL  : " << (total - pass) << "\n";

    std::cout << "=========================================\n";
}

// =====================================================
// ENCONTRAR REY BLANCO
// =====================================================

void TestGameAnalyzer::test_EncontrarRey_Blanco()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Rey,
            Color::Blanca,
            {0, 0}
        ));

    GameAnalyzer analyzer;

    const Ficha* rey =
        analyzer.encontrarRey(
            estado,
            Color::Blanca);

    verificar(
        "EncontrarRey_Blanco",
        rey != nullptr);
}

// =====================================================
// ENCONTRAR REY NEGRO
// =====================================================

void TestGameAnalyzer::test_EncontrarRey_Negro()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Rey,
            Color::Negra,
            {0, 0}
        ));

    GameAnalyzer analyzer;

    const Ficha* rey =
        analyzer.encontrarRey(
            estado,
            Color::Negra);

    verificar(
        "EncontrarRey_Negro",
        rey != nullptr);
}

// =====================================================
// ENCONTRAR REY NO EXISTE
// =====================================================

void TestGameAnalyzer::test_EncontrarRey_NoExiste()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Peon,
            Color::Blanca,
            {0, 0}
        ));

    GameAnalyzer analyzer;

    const Ficha* rey =
        analyzer.encontrarRey(
            estado,
            Color::Blanca);

    verificar(
        "EncontrarRey_NoExiste",
        rey == nullptr);
}

// =====================================================
// ESTADO INICIAL VÁLIDO
// =====================================================

void TestGameAnalyzer::test_EstadoInicialValido()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Rey,
            Color::Blanca,
            {0, 0}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Rey,
            Color::Negra,
            {2, 2}
        ));

    GameAnalyzer analyzer;

    verificar(
        "EstadoInicialValido",
        analyzer.estadoInicialValido(
            estado));
}

// =====================================================
// ESTADO INICIAL INVÁLIDO
// =====================================================

void TestGameAnalyzer::test_EstadoInicialInvalido_SinNegras()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Rey,
            Color::Blanca,
            {0, 0}
        ));

    GameAnalyzer analyzer;

    verificar(
        "EstadoInicialInvalido_SinNegras",
        !analyzer.estadoInicialValido(
            estado));
}

// =====================================================
// BLANCO EN JAQUE
// =====================================================

void TestGameAnalyzer::test_BlancoEnJaque()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Rey,
            Color::Blanca,
            {0, 0}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {0, 2}
        ));

    GameAnalyzer analyzer;

    verificar(
        "BlancoEnJaque",
        analyzer.estaEnJaque(
            estado,
            Color::Blanca));
}

// =====================================================
// SIN JAQUE
// =====================================================

void TestGameAnalyzer::test_SinJaque()
{
    Nodo estado;

    estado.piezas.push_back(
        Ficha(
            1,
            TipoFicha::Rey,
            Color::Blanca,
            {0, 0}
        ));

    estado.piezas.push_back(
        Ficha(
            2,
            TipoFicha::Torre,
            Color::Negra,
            {2, 2}
        ));

    GameAnalyzer analyzer;

    verificar(
        "SinJaque",
        !analyzer.estaEnJaque(
            estado,
            Color::Blanca));
}