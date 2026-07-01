#pragma once

#include "StateEvaluator.h"

class Nodo;

class DecisionTreeEngine
{
public:

    DecisionTreeEngine();

    void expandirNodo(Nodo* nodo);

    void imprimirRama(const Nodo* nodo) const;

private:

    StateEvaluator m_evaluator;
};