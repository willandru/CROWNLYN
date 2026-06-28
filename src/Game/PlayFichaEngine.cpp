#include "PlayFichaEngine.h"

#include "Input.h"

#include "TableroBuilder.h"
#include "DrawFichaEngine.h"
#include "Tablero.h"
#include "Ficha.h"

PlayFichaEngine::PlayFichaEngine()
{
    m_builder = nullptr;

    m_selectedIndex = -1;

    m_haySeleccion = false;

    m_posSeleccionada = {0, 0};
}

void PlayFichaEngine::setBuilder(
    TableroBuilder* builder
)
{
    m_builder = builder;
}

void PlayFichaEngine::update(
    const Input& input
)
{
    if (!m_builder)
        return;

    if (!input.leftMouseClicked())
        return;

    float mx =
        static_cast<float>(
            input.mouseX()
        );

    float my =
        static_cast<float>(
            input.mouseY()
        );

    Posicion posFicha;
    Posicion posCasilla;

    int ficha =
        obtenerFichaEnMouse(
            mx,
            my,
            posFicha
        );

    if (ficha != -1)
    {
        seleccionarFicha(
            ficha
        );

        return;
    }

    if (!hayFichaSeleccionada())
        return;

    if (
        obtenerCasillaEnMouse(
            mx,
            my,
            posCasilla
        )
    )
    {
        moverFicha(
            posCasilla
        );
    }
}

bool PlayFichaEngine::hayFichaSeleccionada() const
{
    return m_haySeleccion;
}

int PlayFichaEngine::getFichaSeleccionada() const
{
    return m_selectedIndex;
}

int PlayFichaEngine::obtenerFichaEnMouse(
    float mouseX,
    float mouseY,
    Posicion& outPos
)
{
    const Tablero& tablero =
        m_builder->getTablero();

    DrawFichaEngine& fichaEngine =
        m_builder->getFichaEngine();

    float cellW =
        tablero.getCellWidth();

    float cellH =
        tablero.getCellHeight();

    for (
        int i = 0;
        i < fichaEngine.getCantidadFichas();
        i++
    )
    {
        const Ficha& ficha =
            fichaEngine.getFicha(i);

        float x =
            tablero.getX()
            + ficha.getPosicion().x * cellW;

        float y =
            tablero.getY()
            + ficha.getPosicion().y * cellH;

        if (
            mouseX >= x &&
            mouseX < x + cellW &&
            mouseY >= y &&
            mouseY < y + cellH
        )
        {
            outPos =
                ficha.getPosicion();

            return i;
        }
    }

    return -1;
}

bool PlayFichaEngine::obtenerCasillaEnMouse(
    float mouseX,
    float mouseY,
    Posicion& outPos
)
{
    const Tablero& tablero =
        m_builder->getTablero();

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

bool PlayFichaEngine::estaDentroDelTablero(
    float mouseX,
    float mouseY
) const
{
    return
        m_builder
            ->getTablero()
            .getCasillaEn(
                mouseX,
                mouseY
            ) != -1;
}

void PlayFichaEngine::seleccionarFicha(
    int index
)
{
    m_selectedIndex =
        index;

    m_haySeleccion =
        true;

    m_posSeleccionada =
        m_builder
            ->getFichaEngine()
            .getFicha(index)
            .getPosicion();
}

void PlayFichaEngine::deseleccionarFicha()
{
    m_selectedIndex =
        -1;

    m_haySeleccion =
        false;
}

void PlayFichaEngine::moverFicha(
    const Posicion& destino
)
{
    if (!m_haySeleccion)
        return;

    Ficha& ficha =
        m_builder
            ->getFichaEngine()
            .getFicha(
                m_selectedIndex
            );

    ficha.setPosicion(
        destino
    );

    deseleccionarFicha();
}