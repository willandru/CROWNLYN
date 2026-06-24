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
    // TABLAS
    // =====================================

    void test_Tablas_MismoTipo();

    void test_NoTablas_TiposDistintos();

    // =====================================
    // DERROTA
    // =====================================

    void test_Derrota_BlancasSinPiezas();

    void test_NoDerrota_AmbosJugadores();

    // =====================================
    // SIN MOVIMIENTOS
    // =====================================

    void test_BlancoSinMovimientos();

    void test_NegroSinMovimientos();

    // =====================================
    // MATE
    // =====================================

    void test_Mate_Blanco();

    void test_Mate_Negro();

    // =====================================
    // TERMINALES
    // =====================================

    void test_EstadoTerminal_Tablas();

    void test_EstadoTerminal_Derrota();

    void test_EstadoTerminal_Mate();

    void test_EstadoTerminal_SinMovimientos();
};