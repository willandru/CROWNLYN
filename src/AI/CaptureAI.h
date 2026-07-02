#pragma once

#include "RandomAI.h"

class Nodo;

class CaptureAI
{
public:

    Nodo* jugar(
        Nodo* actual
    );

private:

    RandomAI m_randomAI;
};