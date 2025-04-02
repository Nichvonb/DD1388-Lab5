//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"
#include <cmath>

King::King(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {}
    
//methods
char King::latin1Representation() {
    if (isWhite())
    {
        return 'K';
    }
    else
    {
        return 'k';
    }
}

string King::utfRepresentation() {
    if (isWhite())
    {
        return "♔";
    }
    else
    {
        return "♚";
    }
}



int King::validMove(int to_x, int to_y)
{
    //std::cout << "INFO: running validMove(x,y) from King" << std::endl;
    
    if (std::abs(getX()-to_x) * std::abs(getY()-to_y) == 1 || std::abs(getX()-to_x)+std::abs(getY()-to_y) == 1)
    {   
        if (getBoard()->getPieceAt(to_x, to_y) == nullptr)
        {
            return 1;
        }
        if (getBoard()->getPieceAt(to_x, to_y) != nullptr and getBoard()->getPieceAt(to_x, to_y)->isWhite() != isWhite())
        {
            return 2;
        }
    }
    return 0;
}

