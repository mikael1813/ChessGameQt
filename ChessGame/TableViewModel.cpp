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

    if (role == Qt::DisplayRole)
        return QString::fromStdString(this->game->getPiece(index.row(), index.column()));

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