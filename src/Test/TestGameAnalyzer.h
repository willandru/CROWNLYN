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
    // REYES
    // =====================================

    void test_EncontrarRey_Blanco();

    void test_EncontrarRey_Negro();

    void test_EncontrarRey_NoExiste();

    // =====================================
    // ESTADO INICIAL
    // =====================================

    void test_EstadoInicialValido();

    void test_EstadoInicialInvalido_SinNegras();

    // =====================================
    // JAQUE
    // =====================================

    void test_BlancoEnJaque();

    void test_SinJaque();
};