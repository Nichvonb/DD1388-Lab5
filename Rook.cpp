//
// DD1388 - Lab 4: Losing Chess
//

#include "Rook.h"

// Implement method definitions here
// Constructor implementation
Rook::Rook(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {}

char Rook::latin1Representation() {
    if (isWhite())
    {
        return 'R';
    }
    else
    {
        return 'r';
    }
}

string Rook::utfRepresentation() {
    if (isWhite())
    {
        return "♖";
    }
    else
    {
        return "♜";
    }
}

int Rook::validMove(int to_x, int to_y) {
    // Check if the move is horizontal or vertical
    //print getX and to_x
    //std::cout << "getpiece at dfafdsfdfsadasdfasf: " << getBoard()->getPieceAt(4, 8) << std::endl;
    //std::cout << "getpiece at dfafdsfdfsadasdfasf: " << getBoard()->getPieceAt(1, 8) << std::endl;
    //std::cout << "getpiece at dfafdsfdfsadasdfasf: " << getBoard()->getPieceAt(3, 6) << std::endl;
    //std::cout << "ROOK: getX: " << getX() << " to_x: " << to_x << "getY: " << getY() << "to_y" << to_y << std::endl;

    if (getX() == to_x || getY() == to_y) {        
        int x_direction;
        if (to_x == getX()) 
        {
            x_direction = 0;
        } 
        else if (to_x > getX()) 
        {
            x_direction = 1;
        } 
        else 
        {
            x_direction = -1;
        }

        int y_direction;
        if (to_y == getY()) 
        {
            y_direction = 0;
        } 
        else if (to_y > getY()) 
        {
            y_direction = 1;
        } 
        else 
        {
            y_direction = -1;
        }

        // Initialize current position to next square in the direction of the move
        int x = getX() + x_direction;
        int y = getY() + y_direction;

        // Check each square along the path to the destination
        while (x != to_x || y != to_y) 
        {
            if (getBoard()->getPieceAt(x, y) != nullptr) 
            {
                return 0;
            }
            x += x_direction;
            y += y_direction;
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