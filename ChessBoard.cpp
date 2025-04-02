//
// DD1388 - Lab 4: Losing Chess
//

#include <sstream>
#include <algorithm> // Add this line to include the <algorithm> header file
#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

#include <iostream> // For debugging output

//creates new ChessBoard object as a copy of an existing one
ChessBoard::ChessBoard(const ChessBoard& other) {
    // Get board dimensions from the other board
    size_t rows = other.getRows();
    size_t cols = other.getCols();

    // Create a new matrix for m_state with the same dimensions.
    Matrix<std::shared_ptr<ChessPiece>> newState(rows, cols);
    // Deep-copy each cell.
    for (size_t i = 1; i <= rows; i++) 
    {
        for (size_t j = 1; j <= cols; j++) 
        {
            std::shared_ptr<ChessPiece> piece = other.m_state(i, j);
            if (piece != nullptr)
            {
                newState(i, j) = piece->clone(this);
            } 
            else 
            {
                newState(i, j) = nullptr;
            }
        }
    }
    m_state = newState;

    // make vector again
    m_white_pieces.clear();
    m_black_pieces.clear();
    for (size_t i = 1; i <= rows; i++) 
    {
        for (size_t j = 1; j <= cols; j++) 
        {
            std::shared_ptr<ChessPiece> piece = m_state(i, j);
            if (piece) 
            {
                if (piece->isWhite()) 
                {
                    m_white_pieces.push_back(piece);
                } 
                else 
                {
                    m_black_pieces.push_back(piece);
                }
            }
        }
    }
}

ChessBoard::~ChessBoard() {
    // Nothing specific to clean up as smart pointers manage memory automatically
}

shared_ptr<ChessPiece> ChessBoard::getPieceAt(int x, int y) const {
    //std::cout << "print the piece at position " << x << "," << y << std::endl;
    //std::cout << "print m_state " << m_state(y,x) << std::endl;
    return m_state(x, y);
}

void ChessBoard::setPieceAt(int x, int y, shared_ptr<ChessPiece> piece) {
    m_state(x, y) = piece;
}

vector<shared_ptr<ChessPiece>>& ChessBoard::getWhitePieces() {
    return m_white_pieces;
}

vector<shared_ptr<ChessPiece>>& ChessBoard::getBlackPieces() {
    return m_black_pieces;
}

void ChessBoard::movePiece(ChessMove chess_move) {
    movePiece(chess_move, false);
}

void ChessBoard::movePiece(ChessMove chess_move, char pawnPromotion) {
    auto piece = m_state(chess_move.from_x, chess_move.from_y);
    int valid_move_flag = piece->validMove(chess_move.to_x, chess_move.to_y);
    if (!piece || valid_move_flag == 0) 
    {
        return;
    }
    
    auto targetPiece = this->m_state(chess_move.to_x, chess_move.to_y);

    if (valid_move_flag == 1) {
        //std::cout << "valid_move_flag1" << std::endl;
        //move piece to the destination
        this->m_state(chess_move.to_x, chess_move.to_y) = piece;
        piece->m_x = chess_move.to_x;
        piece->m_y = chess_move.to_y;
        this->m_state(chess_move.from_x, chess_move.from_y) = nullptr;
    }

    if (valid_move_flag == 2) {
        //std::cout << "Destination TKDKFHKSDHJAKLJD: " << chess_move.to_x << chess_move.to_y << std::endl;
        if (targetPiece != nullptr && targetPiece->m_is_white) {
            //remove from the white pieces list
            auto piece_found_white = std::find(m_white_pieces.begin(), m_white_pieces.end(), targetPiece);
            bool found_piece_white = (piece_found_white != m_white_pieces.end());
            if (found_piece_white == true) {
                m_white_pieces.erase(piece_found_white);
            }
        } 
        else if (targetPiece != nullptr && !targetPiece->m_is_white) {
            //remove from the black peices
            //std::cout << "taking black piece out" << std::endl;
            auto piece_found_black = std::find(m_black_pieces.begin(), m_black_pieces.end(), targetPiece);
            bool found_piece_black = (piece_found_black != m_black_pieces.end());
            if (found_piece_black == true) {
                m_black_pieces.erase(piece_found_black);
            }
            //check if the piece is taken out print
            //for (const auto& piece : m_black_pieces) {
                //std::cout << "checking for black piece: " << piece->latin1Representation() << std::endl;
                //std::cout << "piece position of black piece: " << piece->m_x << piece->m_y << std::endl;
            //}
        }
        this->m_state(chess_move.to_x, chess_move.to_y) = piece;
        piece->m_x = chess_move.to_x;
        piece->m_y = chess_move.to_y;
        this->m_state(chess_move.from_x, chess_move.from_y) = nullptr;
        //print piece
        //std::cout << "Piece position: " << piece->m_x << piece->m_y << std::endl;
    }

    //pawn promotion check
    if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(piece)) 
    {
        bool promote = (pawn->m_is_white && chess_move.to_y == 8) || (!pawn->m_is_white && chess_move.to_y == 1);
        if (promote) 
        {
            std::shared_ptr<ChessPiece> promoted_piece;
            switch (pawnPromotion) 
            {
                case 'Q': case 'q':
                    promoted_piece = std::make_shared<Queen>(chess_move.to_x, chess_move.to_y, pawn->m_is_white, this);
                    break;
                case 'R': case 'r':
                    promoted_piece = std::make_shared<Rook>(chess_move.to_x, chess_move.to_y, pawn->m_is_white, this);
                    break;
                case 'B': case 'b':
                    promoted_piece = std::make_shared<Bishop>(chess_move.to_x, chess_move.to_y, pawn->m_is_white, this);
                    break;
                case 'N': case 'n':
                    promoted_piece = std::make_shared<Knight>(chess_move.to_x, chess_move.to_y, pawn->m_is_white, this);
                    break;
                default:
                    promoted_piece = std::make_shared<Queen>(chess_move.to_x, chess_move.to_y, pawn->m_is_white, this);
                    break;
            }
            
            // make peice the promoted piece
            this->m_state(chess_move.to_x, chess_move.to_y) = promoted_piece;
    
            // Update the piece_list to replace the old pawn with the promoted piece
            std::vector<std::shared_ptr<ChessPiece>>* pieces_list_pointer;
            if (pawn->m_is_white) {
                pieces_list_pointer = &m_white_pieces;
            } else {
                pieces_list_pointer = &m_black_pieces;
            }
            auto& pieces_list = *pieces_list_pointer;
            auto pawn_iterator = std::find(pieces_list.begin(), pieces_list.end(), piece);
            if (pawn_iterator != pieces_list.end()) 
            {
                *pawn_iterator = promoted_piece;
            }
        }
    }
}


vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    // Implementation goes here
    std::vector<ChessMove> vector_capture_moves = {};
    const std::vector<std::shared_ptr<ChessPiece>> * pieces_ptr;
    if (is_white) 
    {
        pieces_ptr = &m_white_pieces;
    } 
    else 
    {
        pieces_ptr = &m_black_pieces;
    }

    // Iterate through the pieces and collect capturing moves
    for (const auto& piece : *pieces_ptr) 
    {
        auto piece_capture_moves = piece->capturingMoves();
        vector_capture_moves.insert(vector_capture_moves.end(), piece_capture_moves.begin(), piece_capture_moves.end());
    }

    return vector_capture_moves;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    
    std::vector<ChessMove> vector_non_capture_moves = {};
    const std::vector<std::shared_ptr<ChessPiece>>* pieces_ptr;
    if (is_white) 
    {
        pieces_ptr = &m_white_pieces;
    } 
    else 
    {
        pieces_ptr = &m_black_pieces;
    }

    for (const auto& piece : *pieces_ptr) 
    {
        auto piece_capture_moves = piece->nonCapturingMoves();
        vector_non_capture_moves.insert(vector_non_capture_moves.end(), piece_capture_moves.begin(), piece_capture_moves.end());
    }
    return vector_non_capture_moves;
}


ChessBoard & operator>>(std::istream & is, ChessBoard & cb) {
    std::vector<std::shared_ptr<ChessPiece>> vector_white_pieces;
    std::vector<std::shared_ptr<ChessPiece>> vector_black_pieces;
    
    std::string input;
    std::getline(is, input);
    // 64 characters?
    //std::cout << input.length() << std::endl;
    if (input.length() == 64) {
        //std::cout << "Input consists of one lines." << std::endl;
        std::getline(is, input);
        // split string into 8-character segments.
        for (size_t i = 8; i > 0; i--) 
        {
            int new_line = (8 - i) * 8;
            std::string line = input.substr(new_line, 8);
            // top row of the chessboard should be row 8
            // so the row board is i

             for (size_t j = 1; j <= 8; j++) 
             {
                char boardChar = line[j - 1];
                switch (boardChar) {
                    case 'R': {
                        auto piece = std::make_shared<Rook>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'r': {
                        auto piece = std::make_shared<Rook>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'N': {
                        auto piece = std::make_shared<Knight>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'n': {
                        auto piece = std::make_shared<Knight>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'B': {
                        auto piece = std::make_shared<Bishop>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'b': {
                        auto piece = std::make_shared<Bishop>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'Q': {
                        auto piece = std::make_shared<Queen>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'q': {
                        auto piece = std::make_shared<Queen>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'K': {
                        auto piece = std::make_shared<King>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'k': {
                        auto piece = std::make_shared<King>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'P': {
                        auto piece = std::make_shared<Pawn>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'p': {
                        auto piece = std::make_shared<Pawn>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case '.': {
                        cb.setPieceAt(j, i, nullptr);
                        break;
                    }
                    default: {
                        cb.setPieceAt(j, i, nullptr);
                        break;
                    }
                }
            }
        }
    } 
    else 
    {
        // 8 lines given
        for (size_t i = 8; i > 0; i--) 
        {
            size_t total_lines = 0;
            //std::cout << "Input consists of multiple lines." << std::endl;
            std::string line;
            if (i == 8)
                line = input;
            else
                std::getline(is, line);
            //std::cout << "Read line for row " << i << ": \"" << line << "\" (length " << line.length() << ")" << std::endl;
            for (size_t j = 1; j <= 8; j++) 
            {
                char boardChar = line[j - 1];
                switch (boardChar) 
                {
                    case 'R': {
                        auto piece = std::make_shared<Rook>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'r': {
                        auto piece = std::make_shared<Rook>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'N': {
                        auto piece = std::make_shared<Knight>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'n': {
                        auto piece = std::make_shared<Knight>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'B': {
                        auto piece = std::make_shared<Bishop>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'b': {
                        auto piece = std::make_shared<Bishop>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'Q': {
                        auto piece = std::make_shared<Queen>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'q': {
                        auto piece = std::make_shared<Queen>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'K': {
                        auto piece = std::make_shared<King>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        break;
                    }
                    case 'k': {
                        auto piece = std::make_shared<King>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case 'P': {
                        auto piece = std::make_shared<Pawn>(j, i, true, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_white_pieces.push_back(piece);
                        //std::cout << "Placed white Pawn at (" << j << ", " << i << ")" << std::endl;
                        break;
                    }
                    case 'p': {
                        auto piece = std::make_shared<Pawn>(j, i, false, &cb);
                        cb.setPieceAt(j, i, piece);
                        vector_black_pieces.push_back(piece);
                        break;
                    }
                    case '.': {
                        cb.setPieceAt(j, i, nullptr);
                        break;
                    }
                    default: {
                        cb.setPieceAt(j, i, nullptr);
                        break;
                    }
                }
            }
        }
    }
    
    cb.getWhitePieces() = vector_white_pieces;
    cb.getBlackPieces() = vector_black_pieces;

    return cb;
}



std::ostream & operator<<(std::ostream & os, const ChessBoard & cb) {
    for (size_t y = cb.getRows(); y >= 1; --y) {
        for (size_t x = 1; x <= cb.getCols(); ++x) {
            auto piece = cb.getPieceAt(x, y);
            if (piece) {
                os << " " << piece->utfRepresentation() << " ";
            } else {
                os << " . ";
            }
        }
        os << std::endl;
    }
    return os;
}
