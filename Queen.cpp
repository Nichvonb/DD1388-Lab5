//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"

// Implement method definitions here
#include <cmath>

// Constructor implementation
Queen::Queen(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board), Bishop(x, y, is_white, board), Rook(x, y, is_white, board) {}

char Queen::latin1Representation() 
{
    if (isWhite()) 
    {
        return 'Q';
    } 
    else 
    {
        return 'q';
    }
}

string Queen::utfRepresentation() 
{
    if (isWhite())
    {
        return "♕";
    }
    else
    {
        return "♛";
    }
}