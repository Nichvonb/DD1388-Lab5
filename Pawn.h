//
// DD1388 - Lab 4: Losing Chess
//

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(int x, int y, bool is_white, ChessBoard* board);

    // virtual std::shared_ptr<ChessPiece> clone() const override {
    //     return std::make_shared<Pawn>(*this);
    // }

    // including the explicit parameters i am now makingsure that the cloned 
    //piece's board pointer is being set to the new board instead of the original
    virtual std::shared_ptr<ChessPiece> clone(ChessBoard* new_board) const override 
    {
        return std::make_shared<Pawn>(m_x, m_y, m_is_white, new_board);
    }
    // Override virtual methods from ChessPiece
    virtual int validMove(int to_x, int to_y) override;
    virtual string utfRepresentation() override;
    virtual char latin1Representation() override;
};

#endif // PAWN_H
