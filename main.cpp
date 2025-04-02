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


// Implement additional functions or classes of your choice

// taken from https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
int random_int(int max) 
{
    return rand()%(max);
}


int main() {
    //srand(time(NULL));
    std::srand(std::time(nullptr));
    ChessBoard b1;

    std::stringstream s;
    // s << "r.bkqbnr";
    // s << "P......p";
    // s << ".P.P..p.";
    // s << "....p...";
    // s << "..p..P..";
    // s << ".p....p.";
    // s << "R..Q.N.R";
    // s << "KNBKQBNR";
    //make a board with a single piece
    // s << "........";
    // s << "....R...";
    // s << "...N....";
    // s << ".....r..";
    // s << "..r.....";
    // s << "........";
    // s << ".....r..";
    // s << "........";
    // s >> b1;
    // s << "........";
    // s << "........";
    // s << "...N....";
    // s << ".p...p..";
    // s << "........";
    // s << "........";
    // s << "........";
    // s << "........";

    // s << "........" << endl;
    // s << ".....P.." << endl;
    // s << "......p." << endl;
    // s << "........" << endl;
    // s << "........" << endl;
    // s << "........" << endl;
    // s << "........" << endl;
    // s << "........";
    // s >> b1;

    // s << "........" << endl;
    // s << "......P." << endl;
    // s << "........" << endl;
    // s << "........" << endl;
    // s << ".....p.." << endl;
    // s << "........" << endl;
    // s << "........" << endl;
    // s << "........";
    // s >> b1;

    s << "........";
    s << "........";
    s << "......p.";
    s << "........";
    s << ".....R..";
    s << "........";
    s << "........";
    s << "........";
    s >> b1;

    std::cout << b1;

    
    while (true)
    {
        char input;
        std::cout << "Choose which AI model to use out of options (1,2) ";
        std::cin >> input;

        bool game_on = true;
        bool white = true;
        if (input == '1')
        {
            while (game_on)
            {
                if ((b1.capturingMoves(white)).size() != 0){

                        ChessMove piece_to_move = (b1.capturingMoves(white)).at(random_int((b1.capturingMoves(white)).size()));
                        // identify if piece_to_move can promote
                        if (piece_to_move.piece->latin1Representation() == 'P' && piece_to_move.to_y == 8 || 
                            piece_to_move.piece->latin1Representation() == 'p' && piece_to_move.to_y == 1)
                        {
                            // a random piece will be selected.
                            std::array<char, 4> pP_character_choices;
                            if (piece_to_move.piece->latin1Representation() == 'P'){
                                pP_character_choices = { 'Q', 'R', 'B', 'N' };} // white peices promotions
                            else if (piece_to_move.piece->latin1Representation() == 'p'){
                                pP_character_choices = { 'q', 'r', 'b', 'n' };} // black pieces promotions
                            int random_index = std::rand() % 4;
                            char pP_character_choice = pP_character_choices[random_index];
                            b1.movePiece(piece_to_move, pP_character_choice);
                        }
                        else
                        {
                            char pP_character_choice = 'E';
                            b1.movePiece(piece_to_move, pP_character_choice);
                        }
                        white = !white;
                        std::cout << "================================================================" << std::endl;
                        std::cout << b1;
                }
                else if ((b1.nonCapturingMoves(white)).size() != 0) {
                    ChessMove piece_to_move = (b1.nonCapturingMoves(white)).at(random_int((b1.nonCapturingMoves(white)).size()));
                    // identify if piece_to_move can promote
                    if (piece_to_move.piece->latin1Representation() == 'P' && piece_to_move.to_y == 8 || 
                        piece_to_move.piece->latin1Representation() == 'p' && piece_to_move.to_y == 1)
                    {
                        // choose randomly to promote between q, r,b, and n
                        std::array<char, 4> pP_character_choices;
                        if (piece_to_move.piece->latin1Representation() == 'P'){
                            pP_character_choices = { 'Q', 'R', 'B', 'N' };} // white promotion candidates
                        else{
                            pP_character_choices = { 'q', 'r', 'b', 'n' };} // black promotion candidates
                        int random_index = std::rand() % 4;
                        char pP_character_choice = pP_character_choices[random_index];
                        //std::cout << pPCharacter << std::endl;

                        b1.movePiece(piece_to_move, pP_character_choice);
                    }
                    else
                    {
                        char pP_character_choice = 'E';
                        b1.movePiece(piece_to_move, pP_character_choice);
                    }
                    white = !white;
                    std::cout << "================================================================" << std::endl;
                    std::cout << b1;
                }
                else 
                {
                    std::cout << b1;
                    break;
                }
            }
            return 0;
        }

        if (input == '2')
        {
            while (game_on)
            {
                //std::cout << "Turn: " << (white ? "White" : "Black") << std::endl;
                
                // moves is all available moves where capturing moves is possible first and if not then just non capturing moves and ends
                // if no moves available ends
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
                    // std::cout << "No available moves for " << (white ? "White" : "Black") << ". Game over." << std::endl;
                    break;
                }
                
                // lambda function & is used so it can affect the variables since we want to modify sim board
                // makes simboard and checks if it forces opponent any capturing moves
                auto move_forces_opponent_capture = [&](const ChessBoard &board, const ChessMove &m, char promotion) -> bool
                {
                    // std::cout << "=== Simulating move ===" << std::endl;
                    // std::cout << "Move details: from (" << m.from_x << ", " << m.from_y << ") to (" 
                    //         << m.to_x << ", " << m.to_y << ") with promotion: " << promotion << std::endl;
                    
                    //create deepcopy of board
                    ChessBoard sim_board = board; 
                    std::cout << "SimBoard before move:" << std::endl;
                    std::cout << sim_board << std::endl;
                    
                    //move piece in sim board
                    sim_board.movePiece(m, promotion);
                    
                    std::cout << "SimBoard after move:" << std::endl;
                    std::cout << sim_board << std::endl;
                    
                    // Get capturing moves for the opponent after the move.
                    auto opponent_capturing_moves = sim_board.capturingMoves(!m.piece->isWhite());
                    std::cout << "Opponent capturing moves count: " << opponent_capturing_moves.size() << std::endl;
                    
                    bool forces_capture = (opponent_capturing_moves.empty() == false);
                    std::cout << "Lambda which checks capture enforcment returns: " << (forces_capture ? "true" : "false") << std::endl;
                    std::cout << "=======================" << std::endl;
                    return forces_capture;
                };
        
                // Default to the first move and set default promotion character to 'E' (meaning "no promotion")
                ChessMove chosen_move = moves[0];
                char chosen_promotion = 'E';
                bool found_move_with_opp = false;

                // std::cout << "Starting to evaluate moves, total moves available: " << moves.size() << std::endl;

                // Try to find a move that does NOT force the opponent into a capture.
                for (const auto &move : moves)
                {
                    // std::cout << "Evaluating move from (" << move.from_x << ", " << move.from_y << ") to ("
                    //         << move.to_x << ", " << move.to_y << ")" << std::endl;
                    
                    // Determine if this move qualifies as a pawn promotion.
                    bool isPromotion = ((move.piece->latin1Representation() == 'P' && move.to_y == 8) ||
                                        (move.piece->latin1Representation() == 'p' && move.to_y == 1));
                    
                    if (isPromotion)
                    {
                        // std::cout << "This move is a promotion move." << std::endl;
                        std::array<char, 4> promotion_candidates;
                        if (move.piece->latin1Representation() == 'P')
                            promotion_candidates = { 'Q', 'R', 'B', 'N' };
                        else
                            promotion_candidates = { 'q', 'r', 'b', 'n' };
                        // Test each promotion candidate.
                        for (char cand : promotion_candidates)
                        {
                            // std::cout << "  Trying promotion candidate: " << cand << std::endl;
                            if (!move_forces_opponent_capture(b1, move, cand))
                            {
                                // std::cout << "    Candidate " << cand << " does not force an opponent capture by this candidate." << std::endl;
                                chosen_move = move;
                                chosen_promotion = cand;
                                found_move_with_opp = true;
                                break; // Exit candidate loop.
                            }
                            else
                            {
                                // std::cout << "    Candidate " << cand << " does force an opponent capture." << std::endl;
                            }
                        }
                        if (found_move_with_opp)
                        {
                            // std::cout << "Safe promotion move chosen with promotion: " << chosen_promotion << std::endl;
                            break; // Exit main loop.
                        }
                    }
                    else
                    {
                        // std::cout << "This move is not a promotion move." << std::endl;
                        if (move_forces_opponent_capture(b1, move, 'E'))
                        {
                            // std::cout << "  This move does forces an opponent capture." << std::endl;
                            chosen_move = move;
                            chosen_promotion = 'E';
                            found_move_with_opp = true;
                            break; // Found a safe move for the promoted piece
                        }
                        // else
                        // {
                        //     std::cout << "  This move does NOT force an opponent capture." << std::endl;
                        // }
                    }
                }

                // If no move forces an opponent capture, choose one at random
                if (!found_move_with_opp)
                {
                    // std::cout << "choosing a move at random." << std::endl;
                    int idx = random_int(moves.size());
                    chosen_move = moves[idx];
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
                        }
                        chosen_promotion = promotionCandidates[random_int(4)];
                        //std::cout << "Randomly chosen move is a promotion move; chosen promotion: " << chosen_promotion << std::endl;
                    }
                    else
                    {
                        chosen_promotion = 'E';
                        //std::cout << "Randomly chosen move with no promotion." << std::endl;
                    }
                }

                // print final decision just before executing the move
                // std::cout << "Executing chosen move from (" << chosen_move.from_x << ", " << chosen_move.from_y << ") to ("
                //         << chosen_move.to_x << ", " << chosen_move.to_y << ") with promotion: " << chosen_promotion << std::endl;

                // Do the move here
                b1.movePiece(chosen_move, chosen_promotion);

                // Print board after the move
                // std::cout << "Board after executing chosen move:" << std::endl;
                // std::cout << b1 << std::endl;

                // change turns
                white = !white;

            }
            return 0;
        }
        else
        {
            std::cout << "Invalid option." << std::endl;
        }
    }
}