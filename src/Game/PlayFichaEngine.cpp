#include "PlayFichaEngine.h"

#include "Input.h"
#include "TableroBuilder.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"

// ======================================================

PlayFichaEngine::PlayFichaEngine()
{
    m_builder = nullptr;
    m_selectedId = -1;
    m_haySeleccion = false;
    m_posSeleccionada = { 0, 0 };
}

// ======================================================

void PlayFichaEngine::setBuilder(
    TableroBuilder* builder
)
{
    m_builder = builder;
}

// ======================================================

void PlayFichaEngine::update(
    const Input& input
)
{
    if (!m_builder)
        return;

    const Nodo* nodo =
        m_builder->getNodo();

    if (!nodo)
        return;

    if (!nodo->tablero)
        return;

    if (!input.leftMouseClicked())
        return;

    float mx =
        static_cast<float>(input.mouseX());

    float my =
        static_cast<float>(input.mouseY());

    Posicion posFicha;
    Posicion posCasilla;

    int idFicha =
        obtenerFichaEnMouse(
            mx,
            my,
            posFicha
        );

    // ==================================================
    // Seleccionar ficha
    // ==================================================

    if (idFicha != -1)
    {
        seleccionarFicha(idFicha);
        return;
    }

    // ==================================================
    // No hay selección
    // ==================================================

    if (!m_haySeleccion)
        return;

    // ==================================================
    // Intentar mover
    // ==================================================

    if (
        obtenerCasillaEnMouse(
            mx,
            my,
            posCasilla
        )
    )
    {
        moverFicha(posCasilla);
    }
}

// ======================================================

bool PlayFichaEngine::hayFichaSeleccionada() const
{
    return m_haySeleccion;
}

// ======================================================

int PlayFichaEngine::getFichaSeleccionada() const
{
    return m_selectedId;
}

// ======================================================

int PlayFichaEngine::obtenerFichaEnMouse(
    float mouseX,
    float mouseY,
    Posicion& outPos
)
{
    const Nodo* nodo =
        m_builder->getNodo();

    if (!nodo || !nodo->tablero)
        return -1;

    const Tablero& tablero =
        *nodo->tablero;

    const std::vector<Ficha>& piezas =
        nodo->piezas;

    const float cellW =
        tablero.getCellWidth();

    const float cellH =
        tablero.getCellHeight();

    for (const Ficha& f : piezas)
    {
        float x =
            tablero.getX() +
            f.getPosicion().x * cellW;

        float y =
            tablero.getY() +
            f.getPosicion().y * cellH;

        if (
            mouseX >= x &&
            mouseX < x + cellW &&
            mouseY >= y &&
            mouseY < y + cellH
        )
        {
            outPos =
                f.getPosicion();

            return f.getId();
        }
    }

    return -1;
}

// ======================================================

bool PlayFichaEngine::obtenerCasillaEnMouse(
    float mouseX,
    float mouseY,
    Posicion& outPos
)
{
    const Nodo* nodo =
        m_builder->getNodo();

    if (!nodo || !nodo->tablero)
        return false;

    const Tablero& tablero =
        *nodo->tablero;

    int id =
        tablero.getCasillaEn(
            mouseX,
            mouseY
        );

    if (id == -1)
        return false;

    outPos.x =
        id % tablero.getAncho();

    outPos.y =
        id / tablero.getAncho();

    return true;
}

// ======================================================

bool PlayFichaEngine::estaDentroDelTablero(
    float mouseX,
    float mouseY
) const
{
    const Nodo* nodo =
        m_builder->getNodo();

    if (!nodo || !nodo->tablero)
        return false;

    return
        nodo->tablero->getCasillaEn(
            mouseX,
            mouseY
        ) != -1;
}

// ======================================================

void PlayFichaEngine::seleccionarFicha(
    int idFicha
)
{
    m_selectedId =
        idFicha;

    m_haySeleccion =
        true;

    const Nodo* nodo =
        m_builder->getNodo();

    const Ficha* ficha =
        nodo->obtenerFichaPorId(
            idFicha
        );

    if (ficha)
    {
        m_posSeleccionada =
            ficha->getPosicion();
    }
}

// ======================================================

void PlayFichaEngine::deseleccionarFicha()
{
    m_selectedId = -1;
    m_haySeleccion = false;
}

// ======================================================

void PlayFichaEngine::moverFicha(
    const Posicion& destino
)
{
    if (!m_haySeleccion)
        return;

    Nodo* nodo =
        m_builder->getNodo();

    Ficha* ficha =
        nodo->obtenerFichaPorId(
            m_selectedId
        );

    if (!ficha)
        return;

    ficha->setPosicion(destino);

    deseleccionarFicha();
}