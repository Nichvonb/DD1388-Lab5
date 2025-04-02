//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public virtual ChessPiece {
    // Override virtual methods from ChessPiece here
public:
    Bishop(int x, int y, bool is_white, ChessBoard* board);// : ChessPiece(x,y,is_white,board){};

    // virtual std::shared_ptr<ChessPiece> clone() const override 
    // {
    //     return std::make_shared<Bishop>(*this);
    // }

    virtual std::shared_ptr<ChessPiece> clone(ChessBoard* new_board) const override 
    {
        return std::make_shared<Bishop>(m_x, m_y, m_is_white, new_board);
    }
    // Override virtual methods from ChessPiece
    virtual int validMove(int to_x, int to_y) override;
    virtual string utfRepresentation() override;
    virtual char latin1Representation() override;
};

#endif // BISHOP_H