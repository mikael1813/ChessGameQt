#include "ChessPiece.h"


class Square {
private:
	ChessPiece* piece;
public:
	Square();
	Square(ChessPiece piece);

	void setPiece(ChessPiece* piece);
	ChessPiece* getPiece();
};