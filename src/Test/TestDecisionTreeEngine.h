#pragma once

#include <string>

class TestDecisionTreeEngine
{
public:

    void ejecutar();

private:

    int total = 0;
    int pass  = 0;

    void verificar(
        const std::string& nombre,
        bool resultado);

    void resumen();

    // =====================================
    // EXPANSIÓN
    // =====================================

    void test_expandirNodo_null();

    void test_nodoTerminal_noGeneraHijos();

    void test_nodoConMovimientos_generaHijos();

    void test_cambioTurno();

    void test_hijoGenerado();
};