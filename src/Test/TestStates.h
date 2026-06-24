#pragma once

#include <string>

class TestStates
{
public:

    void ejecutar();

private:

    int total = 0;
    int pass = 0;

    void verificar(
        const std::string& nombre,
        bool resultado);

    void resumen();

    // =====================================
    // GAME ANALYZER
    // =====================================

    void test_EstadoInicialValido();
    void test_EstadoInicialInvalido_SinNegras();

    // =====================================
    // STATE EVALUATOR
    // =====================================

    void test_Tablas_MismoTipo();
    void test_NoTablas_TiposDistintos();

    void test_BlancoSinMovimientos();
    void test_NegroSinMovimientos();

    void test_EstadoTerminal_SinMovimientos();

    // =====================================
    // ENGINE
    // =====================================

    void test_NodoTerminal_NoGeneraHijos();

    void test_NodoNoTerminal_GeneraHijos();
};