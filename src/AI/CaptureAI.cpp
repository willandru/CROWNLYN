#include "CaptureAI.h"

#include "Nodo.h"
#include "Ficha.h"

#include <vector>
#include <cstdlib>

//==================================================
// PLAY
//==================================================

Nodo* CaptureAI::jugar(
    Nodo* actual
)
{
    if (!actual)
        return nullptr;

    if (actual->hijos.empty())
        return nullptr;

    //--------------------------------------------------
    // Buscar capturas
    //--------------------------------------------------

    std::vector<Nodo*> capturas;

    const int piezasActual =
        static_cast<int>(actual->piezas.size());

    for (Nodo* hijo : actual->hijos)
    {
        if (!hijo)
            continue;

        if (static_cast<int>(hijo->piezas.size()) < piezasActual)
        {
            capturas.push_back(hijo);
        }
    }

    //--------------------------------------------------
    // Si existen capturas, escoger una aleatoria
    //--------------------------------------------------

    if (!capturas.empty())
    {
        int indice =
            rand() % capturas.size();

        return capturas[indice];
    }

    //--------------------------------------------------
    // Si no hay capturas,
    // delegar en RandomAI
    //--------------------------------------------------

    return m_randomAI.jugar(actual);
}