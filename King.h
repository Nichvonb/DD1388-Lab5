//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
    // Override virtual methods from ChessPiece here
public:
    King(int x, int y, bool is_white, ChessBoard* board);

    // virtual std::shared_ptr<ChessPiece> clone() const override 
    // {
    //     return std::make_shared<King>(*this);
    // }

    virtual std::shared_ptr<ChessPiece> clone(ChessBoard* new_board) const override {
        return std::make_shared<King>(m_x, m_y, m_is_white, new_board);
    }
    // Override virtual methods from ChessPiece
    virtual int validMove(int to_x, int to_y) override;
    virtual string utfRepresentation() override;
    virtual char latin1Representation() override;
};

#endif //KING_H
