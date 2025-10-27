//
// DD1388 - Lab 4: Losing Chess
//

//#include "ChessBoard.h"
#include "ChessPiece.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <tuple>
#include <ctime>
#include <array>
#include <limits>
// Implement additional functions or classes of your choice

// taken from https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
int random_int(int max) 
{
    return rand()%(max);
}




int main() {
    std::srand(std::time(nullptr)); // Sets random number generator seed
    ChessBoard b1;
    
    // Used to fill chessboard
    std::vector<std::string> rows; 
    rows.reserve(8);
    std::string line;

    for (std::size_t i = 0; i < 8; ++i) 
    {
        if (!std::getline(std::cin, line)) 
        {
                std::cerr << "Invalid end of input at row " << i << ".\n"; 
                return 1; // Return 1 to indicate error
        }
        if (!line.empty() && line.back() == '\r'){ line.pop_back();}
        if (line.size() != 8u) 
        { 
            std::cerr << "Each row must be exactly 8 characters at row " << i << ".\n";
            return 1; // Return 1 to indicate error
        }
        // rows.push_back(line);
        rows.emplace_back(std::move(line));
    }

    std::stringstream stringStreamTemp;
    for (const auto& r : rows){stringStreamTemp << r;}
    stringStreamTemp >> b1;
    std::cout << b1;

    char whiteStrat;
    char blackStrat;
    while (true) {
        std::cout << "Choose strategy for WHITE: (R) Random or (A) A step ahead AI: ";
        if (!(std::cin >> whiteStrat)){ return 0;}
        if (whiteStrat=='R' || whiteStrat=='r' || whiteStrat=='A' || whiteStrat=='a'){ break;}
        std::cout << "Invalid choice. Please try again.\n";
    }
    while (true) {
        std::cout << "Choose strategy for BLACK: (R) Random or (A) A step ahead AI: ";
        if (!(std::cin >> blackStrat)){ return 0;}
        if (blackStrat=='R' || blackStrat=='r' || blackStrat=='A' || blackStrat=='a'){ break;}
        std::cout << "Invalid choice. Please try again.\n";
    }

    // 50 move rules counter
    int moveNoCapturePawnCounter = 0;
    const int maxMoveNoCapturePawn = 100; // 50*2

    bool game_on = true;
    bool white = true;

    while (game_on) 
    {
        // Create capture list before choosing a move
        auto capturingMovesBefore = b1.capturingMoves(white);

        // Pick strategyfor each side
        char strategy = white ? whiteStrat : blackStrat;

        if (strategy=='R' || strategy=='r') {
            if ((b1.capturingMoves(white)).size() != 0) 
            {

                ChessMove piece_to_move = (b1.capturingMoves(white)).at(random_int(static_cast<int>((b1.capturingMoves(white)).size())));

                bool isPawnMove = (piece_to_move.piece->latin1Representation()=='P' ||
                                   piece_to_move.piece->latin1Representation()=='p');
                bool isCapture = false;

                for (const auto& c : capturingMovesBefore) 
                {
                    if (c.from_x==piece_to_move.from_x && c.from_y==piece_to_move.from_y &&
                        c.to_x==piece_to_move.to_x && c.to_y==piece_to_move.to_y) { isCapture = true; break; }
                }
                // Determine if this move qualifies as a pawn promotion.
                if (piece_to_move.piece->latin1Representation() == 'P' && piece_to_move.to_y == 8 || 
                    piece_to_move.piece->latin1Representation() == 'p' && piece_to_move.to_y == 1)
                {
                    // A random piece will be selected for promotion
                    std::array<char, 4> pP_character_choices;
                    if (piece_to_move.piece->latin1Representation() == 'P'){
                        pP_character_choices = { 'Q', 'R', 'B', 'N' };
                    } 
                    else if (piece_to_move.piece->latin1Representation() == 'p'){
                        pP_character_choices = { 'q', 'r', 'b', 'n' };
                    }
                    int random_index = std::rand() % 4;
                    char pP_character_choice = pP_character_choices[random_index];
                    b1.movePiece(piece_to_move, pP_character_choice);
                }
                else
                {
                    char pP_character_choice = 'E';
                    b1.movePiece(piece_to_move, pP_character_choice);
                }

                // 50-move rule accounting
                if (isPawnMove || isCapture){ moveNoCapturePawnCounter = 0;} 
                else{ ++moveNoCapturePawnCounter;}

                white = !white;
                std::cout << "================================================================" << std::endl;
                std::cout << b1;
            }
            else if ((b1.nonCapturingMoves(white)).size() != 0) 
            {
                ChessMove piece_to_move = (b1.nonCapturingMoves(white)).at(random_int((int)(b1.nonCapturingMoves(white)).size()));

                bool isPawnMove = (piece_to_move.piece->latin1Representation()=='P' ||
                                   piece_to_move.piece->latin1Representation()=='p');
                bool isCapture = false; // by construction it's from non-captures

                // Determine if this move qualifies as a pawn promotion.
                if (piece_to_move.piece->latin1Representation() == 'P' && piece_to_move.to_y == 8 || 
                    piece_to_move.piece->latin1Representation() == 'p' && piece_to_move.to_y == 1)
                {
                    std::array<char, 4> pP_character_choices;
                    if (piece_to_move.piece->latin1Representation() == 'P'){
                        pP_character_choices = { 'Q', 'R', 'B', 'N' };
                    } else {
                        pP_character_choices = { 'q', 'r', 'b', 'n' };
                    }
                    int random_index = std::rand() % 4;
                    char pP_character_choice = pP_character_choices[random_index];
                    b1.movePiece(piece_to_move, pP_character_choice);
                }
                else
                {
                    char pP_character_choice = 'E';
                    b1.movePiece(piece_to_move, pP_character_choice);
                }

                if (isPawnMove || isCapture) moveNoCapturePawnCounter = 0; else ++moveNoCapturePawnCounter;

                white = !white;
                std::cout << "================================================================" << std::endl;
                std::cout << b1;
            }
            else 
            {
                std::cout << b1 << "\nNo available and/or legal moves left for " << (white ? "White" : "Black") << ".\n";
                break;
            }
        }
        // One step ahead strategy
        else if  (strategy=='A' || strategy=='a') {
            std::vector<ChessMove> moves;
            if (!b1.capturingMoves(white).empty())
            {
                moves = b1.capturingMoves(white);
            }
            else if (!b1.nonCapturingMoves(white).empty())
            {
                moves = b1.nonCapturingMoves(white);
            }
            else
            {
                std::cout << b1 << "\nNo available and/or legal moves left for " << (white ? "White" : "Black") << ".\n";
                break;
            }
            // Lambda function & is used so it can affect the variables since we want to modify sim board
            // makes simboard and checks if it forces opponent any capturing moves       
            auto move_forces_opponent_capture = [&](const ChessBoard &board, const ChessMove &m, char promotion) -> bool
            {
                //create deepcopy of board
                ChessBoard sim_board = board; 
                // std::cout << "SimBoard before move:" << std::endl;
                // std::cout << sim_board << std::endl;
                // Move piece in sim board
                sim_board.movePiece(m, promotion);
                // std::cout << "SimBoard after move:" << std::endl;
                // std::cout << sim_board << std::endl;
                // Get capturing moves for the opponent after the move.
                auto opponent_capturing_moves = sim_board.capturingMoves(!m.piece->isWhite());
                
                return !opponent_capturing_moves.empty();
            };

            ChessMove chosen_move = moves[0];
            char chosen_promotion = 'E';
            bool found_move_with_opp = false;

            // Try to find a move that does NOT force the opponent to a capturing move.
            for (const auto &move : moves)
            {
                // Determine if this move is qualifiable as a pawn promotion.
                bool isPromotion = ((move.piece->latin1Representation() == 'P' && move.to_y == 8) ||
                                    (move.piece->latin1Representation() == 'p' && move.to_y == 1));
                
                if (isPromotion)
                {
                    std::array<char, 4> promotion_candidates;
                    if (move.piece->latin1Representation() == 'P')
                        promotion_candidates = { 'Q', 'R', 'B', 'N' };
                    else
                        promotion_candidates = { 'q', 'r', 'b', 'n' };
                    // Test each promotion candidate.
                    for (char cand : promotion_candidates)
                    {
                        if (!move_forces_opponent_capture(b1, move, cand))
                        {
                            chosen_move = move;
                            chosen_promotion = cand;
                            found_move_with_opp = true;
                            break;
                        }
                    }
                    if (found_move_with_opp){break;}
                }
                else
                {
                    if (!move_forces_opponent_capture(b1, move, 'E'))
                    {
                        chosen_move = move;
                        chosen_promotion = 'E';
                        found_move_with_opp = true;
                        break; // Found a safe move for the promoted piece
                    }
                }
            }

            // If no move forces an opponent capture, choose one at random
            if (!found_move_with_opp)
            {
                int idx = random_int((int)moves.size());
                chosen_move = moves[idx];
                // Determine if this move qualifies as a pawn promotion.
                if ((chosen_move.piece->latin1Representation() == 'P' && chosen_move.to_y == 8) ||
                    (chosen_move.piece->latin1Representation() == 'p' && chosen_move.to_y == 1))
                {
                    std::array<char, 4> promotionCandidates;
                    if (chosen_move.piece->latin1Representation() == 'P')
                    {
                        promotionCandidates = { 'Q', 'R', 'B', 'N' };
                    }
                    else
                    {
                        promotionCandidates = { 'q', 'r', 'b', 'n' };
                    chosen_promotion = promotionCandidates[random_int(4)];
                    }
                }
                else
                {
                    chosen_promotion = 'E';
                }
            }

            // print final decision just before executing the move
            // std::cout << "Executing chosen move from (" << chosen_move.from_x << ", " << chosen_move.from_y << ") to ("
            //         << chosen_move.to_x << ", " << chosen_move.to_y << ") with promotion: " << chosen_promotion << std::endl;
            
            bool isPawnMove = (chosen_move.piece->latin1Representation()=='P' ||
                               chosen_move.piece->latin1Representation()=='p');
            bool isCapture = false;
            for (const auto& c : capturingMovesBefore) 
            {
                if (c.from_x==chosen_move.from_x && c.from_y==chosen_move.from_y &&
                    c.to_x==chosen_move.to_x && c.to_y==chosen_move.to_y) 
                    {
                        isCapture = true; 
                        break; 
                    }
            }
            
            // Do move here
            b1.movePiece(chosen_move, chosen_promotion);

            if (isPawnMove || isCapture){ moveNoCapturePawnCounter = 0;}
            else{ ++moveNoCapturePawnCounter;}

            // change turns
            white = !white;
        }

        else
        {
            std::cout << "Not a valid response";
            break;
        }

        // Printing board whatever the strategy
        std::cout << "\n================================================================" << std::endl;
        std::cout << b1;

        // Use for testing
        std::cout << "Press  for next position (or 'q' + Enter to quit)..." << std::flush;
        std::string response;
        if (!std::getline(std::cin, response)){ break;}
        if (!response.empty() && (response[0] == 'q' || response[0] == 'Q')){ break;}


        // 50 move rule
        if (moveNoCapturePawnCounter >= maxMoveNoCapturePawn) {
            std::cout << "Draw by 50-move rule.\n";
            break;
        }
    }

    return 0;
}
