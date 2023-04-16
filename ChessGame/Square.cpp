#include "Square.h"


Square::Square() {
	this->piece = nullptr;
}
Square::Square(ChessPiece piece) {
	this->piece = &piece;
}

void Square::setPiece(ChessPiece* piece) {
	this->piece = piece;
}
ChessPiece* Square::getPiece() {
	return this->piece;
}