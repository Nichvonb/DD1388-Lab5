//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"
#include <cmath>

// Constructor implementation
Knight::Knight(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {}

char Knight::latin1Representation() {
    if (isWhite()) 
    {
        return 'N';
    } 
    else 
    {
        return 'n';
    }
}

string Knight::utfRepresentation() {
    if (isWhite()) 
    {
        return "♘";
    } 
    else 
    {
        return "♞";
    }
}

int Knight::validMove(int to_x, int to_y) {
    //std::cout << "KNIGHT: getX: " << getX() << " to_x: " << to_x << "getY: " << getY() << "to_y" << to_y << std::endl;
    //std::cout << "Knight: ToX" << to_x << "ToY" << to_y << std::endl;
    int dx = std::abs(getX() - to_x);
    int dy = std::abs(getY() - to_y);
    //std::cout << "Knight at (" << getX() << ", " << getY() << ") evaluating move to ("
    //<< to_x << ", " << to_y << "). dx = " << dx << ", dy = " << dy << std::endl;
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) 
    {
        //std::cout << getBoard()->getPieceAt(to_x, to_y) << std::endl;
        // check if the destinatino of this piece is empty or not
        if (getBoard()->getPieceAt(to_x, to_y) == nullptr) 
        {
            //std::cout << "Destination (" << to_x << ", " << to_y << ") is empty." << std::endl;
            return 1;
        }
        else if (getBoard()->getPieceAt(to_x, to_y)->isWhite() != isWhite()) 
        {
            return 2;
        }
    }
    return 0;
}