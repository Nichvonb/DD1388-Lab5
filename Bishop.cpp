//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"

// Implement method definitions here
#include <cmath>

Bishop::Bishop(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {}

char Bishop::latin1Representation() {
    if (isWhite())
    {
        return 'B';
    }
    else
    {
        return 'b';
    }
}

string Bishop::utfRepresentation() {
    if (isWhite())
    {
        return "♗";
    }
    else
    {
        return "♝";
    }
}

int Bishop::validMove(int to_x, int to_y) {
    //std::cout << "BISHOP: getX: " << getX() << " to_x: " << to_x << "getY: " << getY() << "to_y" << to_y << std::endl;

    // print getX and to x
    // Check if the move is diagonal
    if (std::abs(getX() - to_x) == std::abs(getY() - to_y)) {
        int x_direction;
        if ((to_x - getX()) == 0) 
        {
            x_direction = 0;
        } 
        else if ((to_x - getX()) > 0) 
        {
            x_direction = 1;
        } 
        else 
        {
            x_direction = -1;
        }

        int y_direction;
        if ((to_y - getY()) == 0) 
        {
            y_direction = 0;
        } 
        else if ((to_y - getY()) > 0) 
        {
            y_direction = 1;
        } 
        else 
        {
            y_direction = -1;
        }
        int x = getX() + x_direction;
        int y = getY() + y_direction;
        //std::cout << " OVER HERE BISHOP" << std::endl;
        //std::cout << "x: " << x << std::endl;
        //std::cout << "y: " << y << std::endl;
        while (x != to_x && y != to_y) 
        {
            if (getBoard()->getPieceAt(x, y) != nullptr) 
            {
                return 0;
            }
            //std::cout << "Print x" << x << std::endl;
            //std::cout << "Print y" << y << std::endl;
            x += x_direction;
            y += y_direction;
            //std::cout << "Print x" << x << std::endl;
            //std::cout << "Print y" << y << std::endl;
        }

        if (getBoard()->getPieceAt(to_x, to_y) == nullptr) 
        {
            return 1;
        } 
        else if (getBoard()->getPieceAt(to_x, to_y)->isWhite() != isWhite()) 
        {
            return 2;
        }
    }
    return 0;
}