#ReadME
By Nicholas von Butovitsch

To test the program a main code and a test code was created.
Compile the tests with these instructions as listed and in order of:

*g++ -o lab5_final main.cpp ChessBoard.cpp ChessPiece.cpp King.cpp Queen.cpp Rook.cpp Bishop.cpp Knight.cpp Pawn.cpp
*valgrind --leak-check=full ./lab5_final < tests.in
*g++ -o lab5_tests tests.cpp ChessBoard.cpp ChessPiece.cpp King.cpp Queen.cpp Rook.cpp Bishop.cpp Knight.cpp Pawn.cpp
*valgrind --leak-check=full ./lab5_tests < tests.in

This should run all relevant code.