#include "NodeEncoder.h"

#include "Nodo.h"
#include "Ficha.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <intrin.h>   // <-- MSVC bit operations

//==================================================
// BITBOARDS
//==================================================

std::array<uint64_t, NodeEncoder::Count>
NodeEncoder::obtenerBitboards(const Nodo& nodo)
{
    std::array<uint64_t, Count> boards{};
    boards.fill(0);

    for (const Ficha& f : nodo.piezas)
    {
        int index = obtenerIndiceBitboard(f.getTipo(), f.getColor());

        if (index < 0 || index >= Count)
            continue;

        const Posicion& p = f.getPosicion();

        int bit = p.y * 8 + p.x;

        boards[index] |= (uint64_t(1) << bit);
    }

    return boards;
}

//==================================================

uint64_t NodeEncoder::obtenerBitboardCompleto(const Nodo& nodo)
{
    uint64_t board = 0;

    for (const Ficha& f : nodo.piezas)
    {
        const Posicion& p = f.getPosicion();
        int bit = p.y * 8 + p.x;

        board |= (uint64_t(1) << bit);
    }

    return board;
}

//==================================================

std::string NodeEncoder::bitboardToString(uint64_t bitboard)
{
    std::stringstream out;

    for (int y = 7; y >= 0; --y)
    {
        for (int x = 0; x < 8; ++x)
        {
            int bit = y * 8 + x;
            out << ((bitboard >> bit) & 1) << ' ';
        }
        out << '\n';
    }

    return out.str();
}

//==================================================

std::string NodeEncoder::bitboardToHex(uint64_t bitboard)
{
    std::stringstream ss;

    ss << "0x"
       << std::hex
       << std::uppercase
       << std::setw(16)
       << std::setfill('0')
       << bitboard;

    return ss.str();
}

//==================================================

void NodeEncoder::imprimirBitboards(const Nodo& nodo)
{
    auto boards = obtenerBitboards(nodo);

    const char* names[Count] =
    {
        "WhitePawns","WhiteKnights","WhiteBishops",
        "WhiteRooks","WhiteQueens","WhiteKing",
        "BlackPawns","BlackKnights","BlackBishops",
        "BlackRooks","BlackQueens","BlackKing"
    };

    for (int i = 0; i < Count; i++)
    {
        std::cout << "============================\n";
        std::cout << names[i] << "\n";
        std::cout << bitboardToHex(boards[i]) << "\n";
        std::cout << bitboardToString(boards[i]) << "\n";
    }
}

//==================================================
// MOVIMIENTO (FIXED MSVC)
//==================================================

std::string NodeEncoder::obtenerMovimiento(const Nodo& padre, const Nodo& hijo)
{
    uint64_t bbA = obtenerBitboardCompleto(padre);
    uint64_t bbB = obtenerBitboardCompleto(hijo);

    uint64_t diff = bbA ^ bbB;

    if (diff == 0)
        return "----";

    int from = -1;
    int to   = -1;

    while (diff)
    {
        unsigned long index;
        _BitScanForward64(&index, diff); // MSVC replacement

        int bit = (int)index;

        if (from == -1)
            from = bit;
        else
            to = bit;

        diff &= (diff - 1);
    }

    if (from == -1 || to == -1)
        return "??";

    int fx = from % 8;
    int fy = from / 8;

    int tx = to % 8;
    int ty = to / 8;

    return casillaToString(fx, fy) + casillaToString(tx, ty);
}

//==================================================

std::string NodeEncoder::casillaToString(int x, int y)
{
    std::string s;
    s += char('a' + x);
    s += char('1' + y);
    return s;
}

//==================================================

int NodeEncoder::obtenerIndiceBitboard(TipoFicha tipo, Color color)
{
    if (color == Color::Blanca)
    {
        switch (tipo)
        {
            case TipoFicha::Peon:    return WhitePawns;
            case TipoFicha::Caballo: return WhiteKnights;
            case TipoFicha::Alfil:   return WhiteBishops;
            case TipoFicha::Torre:   return WhiteRooks;
            case TipoFicha::Dama:    return WhiteQueens;
            case TipoFicha::Rey:     return WhiteKing;
        }
    }
    else
    {
        switch (tipo)
        {
            case TipoFicha::Peon:    return BlackPawns;
            case TipoFicha::Caballo: return BlackKnights;
            case TipoFicha::Alfil:   return BlackBishops;
            case TipoFicha::Torre:   return BlackRooks;
            case TipoFicha::Dama:    return BlackQueens;
            case TipoFicha::Rey:     return BlackKing;
        }
    }

    return -1;
}