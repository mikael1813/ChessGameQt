#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtableview.h>
#include "ui_ChessGame.h"
#include "TableViewModel.h"
#include "Game.h"

class ChessGameGUI : public QMainWindow
{
    Q_OBJECT

public:
    ChessGameGUI(QWidget *parent = nullptr);
    void adjustTableViewCellSize();
    ~ChessGameGUI();

public:
    void onTableClicked();

private:
    Ui::ChessGameClass ui;
    TableViewModel* myModel;
    //QTableView board;
};
