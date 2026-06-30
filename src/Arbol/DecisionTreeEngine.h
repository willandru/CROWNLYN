#pragma once


#include "StateEvaluator.h"

class Nodo;

class DecisionTreeEngine
{
public:

    DecisionTreeEngine();

    void expandirNodo(
        Nodo* nodo
    );

private:

    StateEvaluator m_evaluator;
};