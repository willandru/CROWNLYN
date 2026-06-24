#pragma once

#include <string>

class TestGameAnalyzer
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
    // VALIDACIÓN DE ESTADOS
    // =====================================

    void test_EstadoInicialValido();

    void test_EstadoInicialInvalido_SinNegras();

    void test_EstadoInicialInvalido_AmbosEnJaque();

    // =====================================
    // JAQUE
    // =====================================

    void test_BlancoEnJaque();

    void test_NegroEnJaque();

    void test_SinJaque();

    // =====================================
    // MOVIMIENTOS
    // =====================================

    void test_BlancoTieneMovimientos();

    void test_BlancoSinMovimientos();

    void test_NegroTieneMovimientos();

    void test_NegroSinMovimientos();

    // =====================================
    // TURNO INICIAL
    // =====================================

    void test_SugerirTurno_Blanco();

    void test_SugerirTurno_Negro();
};