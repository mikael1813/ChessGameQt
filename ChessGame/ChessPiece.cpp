#include "ChessPiece.h"

ChessPiece::ChessPiece(Color color, Type type) {
	this->color = color;
	this->type = type;
}

void ChessPiece::setColor(Color color) {
	this->color = color;
}

const Color ChessPiece::getColor() {
	return this->color;
}

void ChessPiece::setType(Type type) {
	this->type = type;
}
const Type ChessPiece::getType() {
	return this->type;
}

bool ChessPiece::operator==(ChessPiece const& other) const {
	if (this->color == other.color && this->type == other.type) {
		return true;
	}
	return false;
}