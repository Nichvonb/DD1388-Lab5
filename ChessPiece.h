//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessMove.h"
#include "ChessBoard.h"

using namespace std;

class ChessPiece {
    friend class ChessBoard; // Allow ChessBoard to access protected members

    friend void ChessBoard::movePiece(ChessMove p, char pawnPromotion);
private:                               // protected will cause problems

    ChessBoard* m_board;
    

protected:
    /**
     * Returns 0 if target location is not reachable
     * Returns 1 if target location is reachable but empty
     * Returns 2 if target location is reachable and not empty
     */
    int m_x, m_y;
    bool m_is_white;
    virtual int validMove(int to_x, int to_y);

public:
    virtual ~ChessPiece() = default;

    // Copy constructor (shallow copy)
    // copies the pointer m_board (which points to a ChessBoard), rather than creating 
    //a new ChessBoard object. This is called a shallow copy because:
    //Both other and the newly created ChessPiece will now point to the same board.
    //f other.m_board is modified, the copied ChessPiece will see the same changes.
    ChessPiece(const ChessPiece& other)
        : m_x(other.m_x), m_y(other.m_y), m_is_white(other.m_is_white), m_board(other.m_board) {
        // deep copy probably unnecessary
    }

    ChessPiece(int x, int y, bool is_white, ChessBoard* board);

    // Constructor
    virtual string utfRepresentation();     // may be implemented as string
    virtual char latin1Representation();

    //virtual std::shared_ptr<ChessPiece> clone() const = 0;

    //does absolutely nothing or abstract function anyhow and as such is a pure virtual function
    // so every class should implement their own impementation of the clone function
    // i do this since we have several pieces
    virtual std::shared_ptr<ChessPiece> clone(ChessBoard* new_board) const = 0;


    int getX() const;
    int getY() const;
    bool isWhite() const;
    ChessBoard* getBoard() const;
    

     //checks if this move is valid for this current piece and captures a piece of the opposite color
    bool capturingMove(int to_x, int to_y);
    
    // checks if valid move for non capturing move
    bool nonCapturingMove(int to_x, int to_y);
    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();
};


#endif //CHESSPIECE_H
