//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSMOVE_H
#define CHESSMOVE_H

using namespace std;

class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece * piece;   // you can change the position of the chess piece with this pointer.

    // Constructor
    ChessMove(int fromX, int fromY, int toX, int toY, ChessPiece* piece)
        : from_x(fromX), from_y(fromY), to_x(toX), to_y(toY), piece(piece) {}
};

#endif //CHESSMOVE_H
