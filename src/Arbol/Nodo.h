#pragma once

#include <vector>
#include "Tablero.h"
#include "Ficha.h"

class Nodo
{
public:
    Nodo();
    Nodo(const Nodo& other);
    ~Nodo();

    // Estado del juego
    Tablero tablero;
    std::vector<Ficha> piezas;

    // Árbol
    Nodo* padre;
    std::vector<Nodo*> hijos;

    // Turno (integrado en el estado del nodo)
    Color turnoActual;

    // Profundidad en el árbol
    int profundidad;

    // Operaciones del árbol
    void agregarHijo(Nodo* hijo);
    Nodo* clonar() const;

    // Utilidad de consulta
    const Ficha* obtenerFichaEn(int x, int y) const;
    bool hayFichaEn(int x, int y) const;

    void liberarHijos();

private:
    void copiarPiezas(const Nodo& other);
};