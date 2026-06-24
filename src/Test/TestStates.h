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
    // ESTABLAS()
    // =====================================

    void test_esTablas_true();

    void test_esTablas_false();

    // =====================================
    // ESDERROTA()
    // =====================================

    void test_esDerrota_true();

    void test_esDerrota_false();

    // =====================================
    // SINMOVIMIENTOS()
    // =====================================

    void test_sinMovimientos_true();

    void test_sinMovimientos_false();
};