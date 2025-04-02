//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
    : m_x(x), m_y(y), m_is_white(is_white), m_board(board) {}


int ChessPiece::validMove(int to_x, int to_y) {
    // Implementation goes here, e.g., check if the move is valid for this piece type
    //std::cout << "Does it go in here to become 0" << std::endl;
    return 0; // Default: not a valid move
}

string ChessPiece::utfRepresentation() {
    // Implementation goes here
    //string symb = U'\u2720';
    string symb = " ✠ ";
    return symb;
}

char ChessPiece::latin1Representation() {
    // Implementation goes here
    char rep = 'L';
    return rep;
}


// Getter methods

int ChessPiece::getX() const {
    return m_x;
}

int ChessPiece::getY() const {
    return m_y;
}

bool ChessPiece::isWhite() const {
    return m_is_white;
}

ChessBoard* ChessPiece::getBoard() const {
    return m_board;
}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    // int move_status = this -> validMove(to_x, to_y);
    int move_status = validMove(to_x, to_y);
    //print here to_x and to_y
    //std::cout << "capturing move dafadsfasdfasdfadsfasdfadsf" << std::endl;
    //std::cout << "move status asdfadsf " << move_status << "----------------------------"<< std::endl;
    return (move_status == 2);
}
bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    // int move_status = this -> validMove(to_x, to_y);
    int move_status = validMove(to_x, to_y);

    return (move_status == 1);
}

vector<ChessMove> ChessPiece::capturingMoves() {
    vector<ChessMove> moves;
    // Iterate over all possible moves and add capturing moves to the vector
    for (int x = 1; x <= 8; ++x) {
        for (int y = 1; y <= 8; ++y) 
        {
            if (capturingMove(x, y)) 
            {
                //print moves list
                //std::cout << "Capturing move ble ble: " << x << y << std::endl;
                moves.push_back(ChessMove(m_x, m_y, x, y, this));
            }
        }
    }
    //print capturing moves
    // for (int i = 0; i < moves.size(); i++)
    // {
    //    std::cout << "Capturing move 2: " << moves.at(i).from_x << moves.at(i).from_y << moves.at(i).to_x << moves.at(i).to_y << std::endl;
    // }

    return moves;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    vector<ChessMove> moves;
    // Iterate over all possible moves and add non capturing moves to the vector
    for (int x = 1; x <= 8; ++x) 
    {
        for (int y = 1; y <= 8; ++y) 
        {
            if (nonCapturingMove(x, y)) 
            {
                moves.push_back(ChessMove(m_x, m_y, x, y, this));
            }
        }
    }
    //print non capturing moves
    //for (int i = 0; i < moves.size(); i++)
    //{
    //    std::cout << "Non capturing move: " << moves.at(i).from_x << moves.at(i).from_y << moves.at(i).to_x << moves.at(i).to_y << std::endl;
    return moves;
}
