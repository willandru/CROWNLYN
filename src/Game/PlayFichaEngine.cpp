#include "Input.h"
#include "TableroBuilder.h"
#include "Nodo.h"
#include "Tablero.h"
#include "Ficha.h"
#include "PlayFichaEngine.h"
#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveExecutor.h"
#include <iostream>

PlayFichaEngine::PlayFichaEngine()
{
    m_builder = nullptr;

    m_selectedId = -1;

    m_haySeleccion = false;

    m_posSeleccionada = {0,0};
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

    Nodo* nodo =
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
    Posicion posDestino;

    int idFicha =
        obtenerFichaEnMouse(
            mx,
            my,
            posFicha
        );

    //--------------------------------------------------
    // NO HAY SELECCIÓN
    //--------------------------------------------------

    if (!m_haySeleccion)
    {
        if (idFicha != -1)
        {
            seleccionarFicha(idFicha);
        }

        return;
    }

    //--------------------------------------------------
    // CLICK SOBRE UNA FICHA
    //--------------------------------------------------

    if (idFicha != -1)
    {
        Ficha* ficha =
            nodo->obtenerFichaPorId(idFicha);

        if (!ficha)
            return;

        //--------------------------------------------------
        // MISMA FICHA -> DESELECCIONAR
        //--------------------------------------------------

        if (idFicha == m_selectedId)
        {
            deseleccionarFicha();
            return;
        }

        //--------------------------------------------------
        // OTRA FICHA DEL MISMO COLOR -> CAMBIAR SELECCIÓN
        //--------------------------------------------------

        if (ficha->getColor() == nodo->turnoActual)
        {
            seleccionarFicha(idFicha);
            return;
        }

        //--------------------------------------------------
        // FICHA ENEMIGA
        // intentar capturar moviendo a su casilla
        //--------------------------------------------------

        moverFicha(
            ficha->getPosicion()
        );

        return;
    }

    //--------------------------------------------------
    // CLICK EN CASILLA VACÍA
    //--------------------------------------------------

    if (!obtenerCasillaEnMouse(
            mx,
            my,
            posDestino))
    {
        deseleccionarFicha();
        return;
    }

    moverFicha(posDestino);
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
    Nodo* nodo =
        m_builder->getNodo();

    if (!nodo)
        return;

    Ficha* ficha =
        nodo->obtenerFichaPorId(idFicha);

    if (!ficha)
        return;

    //--------------------------------------------------
    // SOLO PUEDE MOVER EL COLOR DEL TURNO
    //--------------------------------------------------

    if (
        ficha->getColor() !=
        nodo->turnoActual
    )
    {
        return;
    }

    //--------------------------------------------------

    m_selectedId = idFicha;

    m_haySeleccion = true;

    m_posSeleccionada =
        ficha->getPosicion();

    m_movimientosPosibles =
        MoveGenerator::getMovimientos(
            *ficha,
            *nodo
        );
}
// ======================================================

void PlayFichaEngine::deseleccionarFicha()
{
    m_selectedId = -1;

    m_haySeleccion = false;

    m_movimientosPosibles.clear();
}
// ======================================================

// ======================================================

void PlayFichaEngine::moverFicha(
    const Posicion& destino
)
{
    //--------------------------------------------------
    // Debe existir una selección
    //--------------------------------------------------

    if (!m_haySeleccion)
        return;

    //--------------------------------------------------
    // Debe ser un movimiento legal
    //--------------------------------------------------

    if (!esMovimientoPosible(destino))
        return;

    //--------------------------------------------------
    // Nodo actual
    //--------------------------------------------------

    Nodo* actual =
        m_builder->getNodo();

    if (!actual)
        return;

    //--------------------------------------------------
    // Crear el nuevo estado
    //--------------------------------------------------

    Nodo* hijo =
        MoveExecutor::crearNodoMovimiento(
            *actual,
            m_selectedId,
            destino
        );

    if (!hijo)
        return;

    //--------------------------------------------------
    // Conectar árbol
    //--------------------------------------------------

    actual->agregarHijo(
        hijo
    );

    //--------------------------------------------------
    // Expandir el nuevo nodo
    //--------------------------------------------------

    m_tree.expandirNodo(
        hijo
    );

    //--------------------------------------------------
    // DEBUG
    //--------------------------------------------------

    std::cout
        << "====================================\n";

    std::cout
        << "Nodo padre : "
        << actual
        << "\n";

    std::cout
        << "Nodo hijo  : "
        << hijo
        << "\n";

    std::cout
        << "Hijos del nuevo nodo: "
        << hijo->hijos.size()
        << "\n";

    std::cout
        << "====================================\n";

    //--------------------------------------------------
    // Ahora el juego continúa desde el hijo
    //--------------------------------------------------

    m_builder->setNodo(
        hijo
    );

    //--------------------------------------------------
    // Limpiar selección
    //--------------------------------------------------

    deseleccionarFicha();
}

bool PlayFichaEngine::esMovimientoPosible(
    const Posicion& pos
) const
{
    for (const Posicion& p : m_movimientosPosibles)
    {
        if (
            p.x == pos.x &&
            p.y == pos.y
        )
        {
            return true;
        }
    }

    return false;
}

// ======================================================

const std::vector<Posicion>&
PlayFichaEngine::getMovimientosPosibles() const
{
    return m_movimientosPosibles;
}