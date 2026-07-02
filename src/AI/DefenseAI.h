#pragma once

#include "CaptureAI.h"

class Nodo;

class DefenseAI
{
public:

    Nodo* jugar(
        Nodo* actual
    );

private:

    CaptureAI m_captureAI;
};