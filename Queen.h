//
// DD1388 - Lab 4: Losing Chess
//

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Rook, public Bishop {
    // Override virtual methods from ChessPiece here
    public:
    
    Queen(int x, int y, bool is_white, ChessBoard *board);//: ChessPiece(x, y, is_white, board), Rook(x,y,is_white,board), Bishop(x,y,is_white,board) {}

    // virtual std::shared_ptr<ChessPiece> clone() const override {
    //     return std::make_shared<Queen>(*this);
    // }
    virtual std::shared_ptr<ChessPiece> clone(ChessBoard* new_board) const override {
        return std::make_shared<Queen>(m_x, m_y, m_is_white, new_board);
    }
    virtual string utfRepresentation() override;
    virtual char latin1Representation() override;

    int validMove(int to_x, int to_y){
        int status;
        if (ChessPiece::getX() == to_x || getY() == to_y)
        {
            status = Rook::validMove(to_x, to_y);
        } else {
            status = Bishop::validMove(to_x, to_y);
        }
        return status;
    }
};



#endif //QUEEN_H