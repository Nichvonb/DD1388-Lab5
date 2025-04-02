//
// DD1388 - Lab 4: Losing Chess
//
#include <stack>

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <istream>
#include <memory>
#include "ChessMove.h"
#include "Matrix.h"   // Use the "-I ../02" flag to let the compiler find Matrix.h

using namespace std;

class ChessPiece;

class ChessBoard {

private:
    Matrix<std::shared_ptr<ChessPiece>> m_state; // Matrix from lab 2
    vector<std::shared_ptr<ChessPiece>> m_white_pieces;
    vector<std::shared_ptr<ChessPiece>> m_black_pieces;



public:

    // Constructor
    ChessBoard(){
        //std::cout << "INFO: New ChessBoard object created." << std::endl;
        Matrix< std::shared_ptr<ChessPiece>> m1(8);
        m_state = m1;
    }
    
    // Copy constructor
    ChessBoard(const ChessBoard& other);

    //Copy assignment operator
    ChessBoard& operator=(const ChessBoard& other);
    
    // Destructor
    ~ChessBoard();                 // Just declaration


    // Accessors
    std::shared_ptr<ChessPiece> getPieceAt(int x, int y) const;
    void setPieceAt(int x, int y, std::shared_ptr<ChessPiece> piece);

    vector<std::shared_ptr<ChessPiece>>& getWhitePieces();
    vector<std::shared_ptr<ChessPiece>>& getBlackPieces();

    void movePiece(ChessMove chess_move);
    void movePiece(ChessMove chess_move, char pawnPromotion);

    
    std::vector<ChessMove> capturingMoves(bool is_white);
    std::vector<ChessMove> nonCapturingMoves(bool is_white);

    //void undo();
    size_t getRows() const { return m_state.rows(); }
    size_t getCols() const { return m_state.cols(); }

};

ChessBoard & operator>>(std::istream & is, ChessBoard & cb);
std::ostream & operator<<(std::ostream & os, const ChessBoard & cb);

#endif //CHESSBOARD_H
