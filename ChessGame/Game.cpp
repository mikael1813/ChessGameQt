#include "Game.h"

Game::Game() {

	vector<Square> row;
	Square s(ChessPiece(Color::Black, Type::Rook));
	row.push_back(s);
	this->board.push_back({ Square(ChessPiece(Color::Black, Type::Rook)),Square(ChessPiece(Color::Black, Type::Knight)),Square(ChessPiece(Color::Black, Type::Bishop)),Square(ChessPiece(Color::Black, Type::Queen)),Square(ChessPiece(Color::Black, Type::King)),Square(ChessPiece(Color::Black, Type::Bishop)),Square(ChessPiece(Color::Black, Type::Knight)),Square(ChessPiece(Color::Black, Type::Rook)) });
	for (int i = 1; i < this->boardSize - 1; i++) {
		vector<Square> row;
		for (int j = 0; j < this->boardSize; j++) {
			switch (i) {
			case 1:
				row.push_back(Square(ChessPiece(Color::Black, Type::Pawn)));
				break;
			case 6:
				row.push_back(Square(ChessPiece(Color::White, Type::Pawn)));
				break;
			default:
				row.push_back(Square());
				break;
			}
		}
		this->board.push_back(row);
	}
	this->board.push_back({ Square(ChessPiece(Color::White, Type::Rook)),Square(ChessPiece(Color::White, Type::Knight)),Square(ChessPiece(Color::White, Type::Bishop)),Square(ChessPiece(Color::White, Type::Queen)),Square(ChessPiece(Color::White, Type::King)),Square(ChessPiece(Color::White, Type::Bishop)),Square(ChessPiece(Color::White, Type::Knight)),Square(ChessPiece(Color::White, Type::Rook)) });
}

const tuple<unsigned short int, unsigned short int> Game::getActualPostion(const string position) {

	regex reg("[a-hA-H][0-9]");
	if (position.size() != 2 || !regex_match(position, reg)) {
		throw;
	}

	char letter = position.at(0);
	if (letter >= 'A' && letter <= 'Z') {
		letter = 'a' + (letter - 'A');
	}
	return { this->boardSize - atoi(&position.at(1)),letterPositions.at(letter) };
}

const  vector< tuple<unsigned short int, unsigned short int>> Game::getAllPossibleMoves(const unsigned short int i, const unsigned short int j) {
	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	ChessPiece* piece = this->board.at(i).at(j).getPiece();
	
	if (*piece == ChessPiece(Color::Black,Type::Pawn)) {
		if (this->board.at(i + 1).at(j).getPiece() == nullptr) {
			possible_moves.push_back({ i + 1,j });
		}
		if (i == 1 && this->board.at(i + 2).at(j).getPiece() == nullptr) {
			possible_moves.push_back({ i + 2,j });
		}
		if (j < this->boardSize - 1 && this->board.at(i + 1).at(j + 1).getPiece() != nullptr && this->board.at(i + 1).at(j + 1).getPiece()->getColor() == Color::White) {
			possible_moves.push_back({ i + 1,j + 1 });
		}
		if (j > 0 && this->board.at(i + 1).at(j - 1).getPiece() != nullptr && this->board.at(i + 1).at(j - 1).getPiece()->getColor() == Color::White) {
			possible_moves.push_back({ i + 1,j - 1 });
		}
	}

	else if (*piece == ChessPiece(Color::White, Type::Pawn)) {
		if (this->board.at(i - 1).at(j).getPiece() == nullptr) {
			possible_moves.push_back({ i - 1,j });
		}
		if (i == this->boardSize - 2 && this->board.at(i - 2).at(j).getPiece() == nullptr) {
			possible_moves.push_back({ i - 2,j });
		}
		if (j < this->boardSize - 1 && this->board.at(i - 1).at(j + 1).getPiece() != nullptr && this->board.at(i - 1).at(j + 1).getPiece()->getColor() == Color::Black) {
			possible_moves.push_back({ i - 1,j + 1 });
		}
		if (j > 0 && this->board.at(i - 1).at(j - 1).getPiece() != nullptr && this->board.at(i - 1).at(j - 1).getPiece()->getColor() == Color::Black) {
			possible_moves.push_back({ i - 1,j - 1 });
		}
	}

	else if (piece->getType() == Type::Knight) {
		vector<int> moves{ -2,-1,1,2 };
		for (auto k : moves) {
			for (auto l : moves) {
				if (abs(k) != abs(l)) {
					int posi = i + k, posj = j + l;
					if (posi < 0 || posi >= this->boardSize || posj < 0 || posj >= this->boardSize) {
						//break;
					}
					else if (this->board.at(posi).at(posj).getPiece() == nullptr) {
						possible_moves.push_back({ posi,posj });
					}
					else if (this->board.at(posi).at(posj).getPiece()->getColor() != piece->getColor()) {
						possible_moves.push_back({ posi,posj });
						//break;
					}
					else if (this->board.at(posi).at(posj).getPiece()->getColor() == piece->getColor()) {
						//break;
					}
				}
			}
		}
	}

	else if (piece->getType() == Type::Bishop) {
		possible_moves = this->getAllBishopMoves(i, j);
	}

	else if (piece->getType() == Type::Rook) {
		possible_moves = this->getAllRookMoves(i, j);
	}

	else if (piece->getType() == Type::Queen) {
		possible_moves = this->getAllQueenMoves(i, j);
	}

	else if (piece->getType() == Type::King) {
		for (int k = -1; k <= 1; k++) {
			for (int l = -1; l <= 1; l++) {
				if (k != 0 && l != 0 && 0 <= i + k && i + k < this->boardSize && 0 <= j + l && j + l < this->boardSize && (this->board.at(i + k).at(j + l).getPiece() == nullptr || this->board.at(i + k).at(j + l).getPiece()->getColor() != piece->getColor())) {
					possible_moves.push_back({ i + k,j + l });
				}
			}
		}
	}

	return possible_moves;
}

const vector< tuple<unsigned short int, unsigned short int>> Game::getAllBishopMoves(const unsigned short int i, const unsigned short int j) {
	Color color = this->board.at(i).at(j).getPiece()->getColor();

	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	for (int k = -1; k <= 1; k = k + 2) {
		for (int l = -1; l <= 1; l = l + 2) {
			vector< tuple<unsigned short int, unsigned short int>> aux = this->getMoves(i, j, k, l, color);
			possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());
		}
	}

	return possible_moves;
}


const vector< tuple<unsigned short int, unsigned short int>> Game::getAllRookMoves(const unsigned short int i, const unsigned short int j) {
	Color color = this->board.at(i).at(j).getPiece()->getColor();

	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	for (int k = -1; k <= 1; k = k + 2) {
		vector< tuple<unsigned short int, unsigned short int>> aux = this->getMoves(i, j, k, 0, color);
		possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());
	}
	for (int l = -1; l <= 1; l = l + 2) {
		vector< tuple<unsigned short int, unsigned short int>> aux = this->getMoves(i, j, 0, l, color);
		possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());
	}

	return possible_moves;
}

const vector< tuple<unsigned short int, unsigned short int>> Game::getAllQueenMoves(const unsigned short int i, const unsigned short int j) {
	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	vector< tuple<unsigned short int, unsigned short int>> aux;

	aux = this->getAllBishopMoves(i, j);
	possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());

	aux = this->getAllRookMoves(i, j);
	possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());

	return possible_moves;
}

const vector< tuple<unsigned short int, unsigned short int>> Game::getMoves(short int i, short int j, const short int k, const short int l, const Color color) {

	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	while (true) {
		i += k;
		j += l;
		if (i < 0 || i >= this->boardSize || j < 0 || j >= this->boardSize) {
			break;
		}
		else if (this->board.at(i).at(j).getPiece() == nullptr) {
			possible_moves.push_back({ i,j });
		}
		else if (this->board.at(i).at(j).getPiece()->getColor() != color) {
			possible_moves.push_back({ i,j });
			break;
		}
		else if (this->board.at(i).at(j).getPiece()->getColor() == color) {
			break;
		}
	}

	return possible_moves;
}

const bool Game::move(tuple<unsigned short int, unsigned short int> from, tuple<unsigned short int, unsigned short int> to) {
	vector< tuple<unsigned short int, unsigned short int>> correct_moves = this->getAllCorrectMoves(get<0>(from), get<1>(from));

	if (find(correct_moves.begin(), correct_moves.end(), to) != correct_moves.end()) {
		this->addHistory(get<0>(from), get<1>(from), get<0>(to), get<1>(to));

		this->board.at(get<0>(to)).at(get<1>(to)).setPiece(this->board.at(get<0>(from)).at(get<1>(from)).getPiece());
		this->board.at(get<0>(from)).at(get<1>(from)).setPiece(nullptr);
		return true;
	}
	else {
		return false;
	}
}

void Game::addHistory(const unsigned short int i, const unsigned short int j, const unsigned short int toi, const unsigned short int toj) {
	if (this->board.at(i).at(j).getPiece()->getColor() == Color::White) {
		this->moveCount++;
		this->movesHistory += to_string(this->moveCount) + ".";
	}
	char letter = 'a' + j;
	this->movesHistory += " " + letter;

	if (this->board.at(toi).at(toj).getPiece() != nullptr) {
		this->movesHistory += 'x';
	}
	letter = 'a' + toj;
	this->movesHistory += letter + to_string(this->boardSize - toi);
}

const vector< tuple<unsigned short int, unsigned short int>> Game::getAllCorrectMoves(const unsigned short int i, const unsigned short int j) {
	vector< tuple<unsigned short int, unsigned short int>> possible_moves = this->getAllPossibleMoves(i, j);

	vector< tuple<unsigned short int, unsigned short int>> correct_moves;

	Color color = this->board.at(i).at(j).getPiece()->getColor();
	ChessPiece* piece = this->board.at(i).at(j).getPiece();
	for (auto pos : possible_moves) {
		ChessPiece* aux = this->board.at(get<0>(pos)).at(get<1>(pos)).getPiece();
		this->board.at(get<0>(pos)).at(get<1>(pos)).setPiece(piece);
		this->board.at(i).at(j).setPiece(nullptr);
		if (!this->isKingInCheck(color)) {
			correct_moves.push_back(pos);
		}
		this->board.at(get<0>(pos)).at(get<1>(pos)).setPiece(aux);
		this->board.at(i).at(j).setPiece(piece);
	}

	return correct_moves;
}

const bool Game::isKingInCheck(Color color) {
	tuple<unsigned short int, unsigned short int> king_position = this->getKingPosition(color);

	vector< tuple<unsigned short int, unsigned short int>> possible_checks;

	for (int i = 0; i < this->boardSize; i++) {
		for (int j = 0; j < this->boardSize; j++) {
			if (this->board.at(i).at(j).getPiece() != nullptr && this->board.at(i).at(j).getPiece()->getColor() != color) {
				vector< tuple<unsigned short int, unsigned short int>> possible_moves = this->getAllPossibleMoves(i, j);
				possible_checks.insert(possible_checks.end(), possible_moves.begin(), possible_moves.end());
			}
		}
	}

	for (auto pos : possible_checks) {
		if (pos == king_position) {
			return true;
		}
	}

	return false;
}

const tuple<unsigned short int, unsigned short int> Game::getKingPosition(Color color) {
	tuple<unsigned short int, unsigned short int> kingPosition;
	ChessPiece king(color, Type::King);
	for (int i = 0; i < this->boardSize; i++) {
		for (int j = 0; j < this->boardSize; j++) {
			if (*this->board.at(i).at(j).getPiece() == king) {
				get<0>(kingPosition) = i;
				get<1>(kingPosition) = j;
				return kingPosition;
			}
		}
	}
	return kingPosition;
}


Game::~Game() {

}