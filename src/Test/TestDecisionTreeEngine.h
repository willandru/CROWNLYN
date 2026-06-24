#pragma once

#include <string>

class TestDecisionTreeEngine
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
    // EXPANSIÓN BÁSICA
    // =====================================

    void test_NodoNull();

    void test_NodoTerminal_NoGeneraHijos();

    void test_NodoNoTerminal_GeneraHijos();

    // =====================================
    // CAMBIO DE TURNO
    // =====================================

    void test_CambioTurno_BlancaANegra();

    void test_CambioTurno_NegraABlanca();

    // =====================================
    // GENERACIÓN DE HIJOS
    // =====================================

    void test_MultiplesHijos();

    void test_CapturaGeneraMenosPiezas();

    // =====================================
    // FILTRO DE MOVIMIENTOS
    // =====================================

    void test_NoGeneraMovimientoIlegal();

    void test_SoloMovimientosLegales();

    // =====================================
    // BUGS DE REGRESIÓN
    // =====================================

    void test_Bug_PeonBordeSuperior();

    void test_Bug_PeonSinMovimientos();

    void test_Bug_EstadoTerminalExpandido();

    // =====================================
    // INTEGRACIÓN
    // =====================================

    void test_ExpandirUnaVez();

    void test_ExpandirConCaptura();

    void test_ExpandirConVariasOpciones();
};