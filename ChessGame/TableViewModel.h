#pragma once

#include <QAbstractTableModel>
#include "Game.h"

class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableViewModel(Game* game, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    ~TableViewModel();
    void tableClicked(short unsigned i, short unsigned j);
    //vector< tuple<unsigned short int, unsigned short int>> lastAvailableMoves;
    optional<tuple<unsigned short int, unsigned short int>> lastPieceClicked;

private:
    Game* game;
};