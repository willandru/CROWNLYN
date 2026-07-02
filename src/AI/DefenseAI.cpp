#include "DefenseAI.h"

#include "Nodo.h"
#include "Ficha.h"
#include "DecisionTreeEngine.h"

#include <limits>

//==================================================
// PLAY
//==================================================

Nodo* DefenseAI::jugar(
    Nodo* actual
)
{
    if (!actual)
        return nullptr;

    //--------------------------------------------------
    // Expandir dos niveles
    //--------------------------------------------------

    DecisionTreeEngine tree;

    tree.expandirProfundidad(
        actual,
        2
    );

    //--------------------------------------------------

    if (actual->hijos.empty())
        return nullptr;

    Nodo* mejorMovimiento = nullptr;

    int mejorRiesgo =
        std::numeric_limits<int>::max();

    //--------------------------------------------------
    // Analizar cada movimiento propio
    //--------------------------------------------------

    for (Nodo* hijo : actual->hijos)
    {
        if (!hijo)
            continue;

        //--------------------------------------------------
        // Riesgo de este movimiento
        //--------------------------------------------------

        int peorCaso = 0;

        //--------------------------------------------------
        // Analizar todas las respuestas rivales
        //--------------------------------------------------

        for (Nodo* respuesta : hijo->hijos)
        {
            if (!respuesta)
                continue;

            int riesgo = 0;

            //--------------------------------------------------
            // Revisar si desapareció alguna pieza propia
            //--------------------------------------------------

            for (const Ficha& ficha : hijo->piezas)
            {
                if (ficha.getColor() != actual->turnoActual)
                    continue;

                if (!respuesta->obtenerFichaPorId(
                        ficha.getId()))
                {
                    riesgo++;
                }
            }

            //--------------------------------------------------

            if (riesgo > peorCaso)
            {
                peorCaso = riesgo;
            }
        }

        //--------------------------------------------------
        // Conservar el movimiento más seguro
        //--------------------------------------------------

        if (peorCaso < mejorRiesgo)
        {
            mejorRiesgo = peorCaso;
            mejorMovimiento = hijo;
        }
    }

    //--------------------------------------------------
    // Existe un movimiento completamente seguro
    //--------------------------------------------------

    if (mejorMovimiento &&
        mejorRiesgo == 0)
    {
        return mejorMovimiento;
    }

    //--------------------------------------------------
    // Ningún movimiento es completamente seguro.
    // Delegar en CaptureAI.
    //--------------------------------------------------

    return m_captureAI.jugar(actual);
}