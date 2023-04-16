#include "TableViewModel.h"

TableViewModel::TableViewModel(Game* game, QObject* parent)
    : QAbstractTableModel(parent)
{
    this->game = game;
}

int TableViewModel::rowCount(const QModelIndex& /*parent*/) const
{
    return this->game->getSize();
}

int TableViewModel::columnCount(const QModelIndex& /*parent*/) const
{
    return this->game->getSize();
}

QVariant TableViewModel::data(const QModelIndex& index, int role) const
{
    /*if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
        .arg(index.row() + 1)
        .arg(index.column() + 1);*/

    if (role == Qt::DisplayRole) {
        const ChessPiece* piece2 = this->game->getPiece(index.row(), index.column());
        if (piece2 == nullptr) {
            return QString("");
        }
        ChessPiece piece = *piece2;
        string output = "";
        Color c = Color::White;
        if (piece.getColor() == Color::White) {
            output += "w";
        }
        else {
            output += "b";
        }
        if (piece.getType() == Type::Bishop) {
            output += "b";
        }
        else if (piece.getType() == Type::Pawn) {
            output += "n";
        }
        else if (piece.getType() == Type::Knight) {
            output += "n";
        }
        else if (piece.getType() == Type::King) {
            output += "k";
        }
        else if (piece.getType() == Type::Queen) {
            output += "q";
        }
        else {
            output += "r";
        }
        return QString::fromStdString(output);
    }

    return QVariant();
}

QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            char letter = 'A' + section;
            return QString(letter);
        }
        else {
            return QString::fromStdString(std::to_string(this->game->getSize() - section));
        }
    }
    return QVariant();
}

void TableViewModel::tableClicked(short unsigned i, short unsigned j) {
    if (lastPieceClicked.has_value()) {
        for (tuple t : this->game->getAllCorrectMoves(get<0>(lastPieceClicked.value()), get<1>(lastPieceClicked.value()))) {
            if (get<0>(t) == i && get<1>(t) == j) {
                this->game->move(lastPieceClicked.value(), t);
                QModelIndex from = QAbstractItemModel::createIndex(get<0>(lastPieceClicked.value()), get<1>(lastPieceClicked.value()));
                QModelIndex to = QAbstractItemModel::createIndex(i, j);
                //this->setData(from, QString(""));
                //this->setData(to, QString::fromStdString(this->game->getPiece(get<0>(lastPieceClicked.value()), get<1>(lastPieceClicked.value()))));
                
                lastPieceClicked = nullopt;
                emit dataChanged(from, to);
                return;
            }
        }
    }
    const ChessPiece* piece = this->game->getPiece(i, j);
    if (piece != nullptr) {
        lastPieceClicked = tuple{ i,j };
    }
}

TableViewModel::~TableViewModel() {
    delete game;
}