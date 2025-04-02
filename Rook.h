//
// DD1388 - Lab 4: Losing Chess
//

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public virtual ChessPiece {
public:
    Rook(int x, int y, bool is_white, ChessBoard* board);// : ChessPiece(x,y,is_white,board){};

    // virtual std::shared_ptr<ChessPiece> clone() const override {
    //     return std::make_shared<Rook>(*this);
    // }
    // removed as when going into the deep copy this goes to the oold board
    virtual std::shared_ptr<ChessPiece> clone(ChessBoard* new_board) const override {
        return std::make_shared<Rook>(m_x, m_y, m_is_white, new_board);
    }
    //override virtual methods from ChessPiece
    virtual int validMove(int to_x, int to_y) override;
    virtual string utfRepresentation() override;
    virtual char latin1Representation() override;
};

#endif // ROOK_H