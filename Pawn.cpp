//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"

// Implement method definitions here

// Constructor implementation
Pawn::Pawn(int x, int y, bool is_white, ChessBoard* board)
    : ChessPiece(x, y, is_white, board) {}

char Pawn::latin1Representation() {
    if (isWhite()) 
    {
        return 'P';
    } 
    else 
    {
        return 'p';
    }
}

string Pawn::utfRepresentation() {
    if (isWhite()) 
    {
        return "♙";
    } 
    else 
    {
        return "♟";
    }
}

int Pawn::validMove(int to_x, int to_y) {
    //std::cout<<"Pawn::validMove"<<std::endl;
    //std::cout<<"----------------------------------------"<<std::endl;

    //int dx = std::abs(getX() - to_x);
    int dx = to_x - getX();
    int dy = to_y - getY();

    // Determine direction based on color
    int direction;
    if (isWhite()) 
    {
        direction = 1;
    } 
    else 
    {
        direction = -1;
    }

    // Normal move
    if (dx == 0) {
        if (dy == direction && getBoard()->getPieceAt(to_x, to_y) == nullptr) 
        {
            return 1; // Valid move (one square forward)
        }
        //std::cout<<"getY: "<<getY()<<std::endl;
        //if (((!isWhite() && getY() == 7))){
        //std::cout << "TEST TESTS TESTSETESTSETESTSETTSETSETESTESTTESTTESTESTESTSETTESTESTESTSETEST" << std::endl;
        //}
        
        if (dy == 2 * direction && getBoard()->getPieceAt(to_x, to_y) == nullptr && 
            getBoard()->getPieceAt(getX(), getY() + direction) == nullptr && 
            ((isWhite() && getY() == 2) || (!isWhite() && getY() == 7))) 
        {
            //std::cout << "TEST TESTS TESTSETESTSETESTSETTSETSETESTESTTESTTESTESTESTESTSETTESTESTESTSETEST" << std::endl;
            //std::cout << "dy" << dy << std::endl;
            //std::cout<<"in here pawn piece"<<std::endl;
            //std::cout << "direction" << direction << std::endl;
            return 1; //only for first move, two steps, from starting position
        }
    }
    
    if ((dx == 1 || dx == -1) && dy == direction && getBoard()->getPieceAt(to_x, to_y) != nullptr && 
        getBoard()->getPieceAt(to_x, to_y)->isWhite() != isWhite()) 
    {
        return 2;
    }
    
    return 0;
}