#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>
#include <map>
#include <regex>
//#include "ChessPiece.h"
#include "Square.h"

using namespace std;

class Game {
private:
	vector<vector<Square>> board;
	const unsigned short int boardSize = 8;
	string movesHistory = "";
	int moveCount = 0;
	const map<char, unsigned short int> letterPositions{ {'a',0},{'b',1},{'c',2},{'d',3},{'e',4},{'f',5},{'g',6},{'h',7} };
public:
	Game();

	//position is a actual chess board position like E3 (so position is like [a-hA-H][0-9])
	//return actual position in matrix of position (ex. get_actual_postion("E3") => (5,4) )
	const tuple<unsigned short int, unsigned short int> getActualPostion(string position);

	const vector< tuple<unsigned short int, unsigned short int>> getAllPossibleMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllCorrectMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllBishopMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllRookMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllQueenMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getMoves(const short int i, const short int j, const short int k, const short int l, const Color color);

	const bool isKingInCheck(Color color);

	const tuple<unsigned short int, unsigned short int> getKingPosition(Color color);

	const bool move(tuple<unsigned short int, unsigned short int> from, tuple<unsigned short int, unsigned short int> to);

	void addHistory(const unsigned short int i, const unsigned short int j, const unsigned short int toi, const unsigned short int toj);

	~Game();

	const unsigned short int getSize() {
		return this->boardSize;
	}

	const ChessPiece* getPiece(unsigned short int i, unsigned short int j) {
		return this->board.at(i).at(j).getPiece();
	}
};


#endif // !'GAME_H_'