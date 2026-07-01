#pragma once

#include <array>
#include <cstdint>
#include <string>

#include "Ficha.h"

class Nodo;

class NodeEncoder
{
public:

    enum BitboardIndex
    {
        WhitePawns = 0,
        WhiteKnights,
        WhiteBishops,
        WhiteRooks,
        WhiteQueens,
        WhiteKing,

        BlackPawns,
        BlackKnights,
        BlackBishops,
        BlackRooks,
        BlackQueens,
        BlackKing,

        Count
    };

    static std::array<uint64_t, Count>
    obtenerBitboards(const Nodo& nodo);

    static uint64_t
    obtenerBitboardCompleto(const Nodo& nodo);

    static std::string
    bitboardToString(uint64_t bitboard);

    static std::string
    bitboardToHex(uint64_t bitboard);

    static void
    imprimirBitboards(const Nodo& nodo);

    static std::string
    obtenerMovimiento(const Nodo& padre, const Nodo& hijo);

private:

    static std::string casillaToString(int x, int y);

    static int obtenerIndiceBitboard(TipoFicha tipo, Color color);
};