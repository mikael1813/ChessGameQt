#include "ChessGameGUI.h"

ChessGameGUI::ChessGameGUI(QWidget *parent)
    : QMainWindow(parent)
{
    
    ui.setupUi(this);

    //std::unique_ptr<TableViewModel> myModel(new TableViewModel());
    this->game = new Game();

    this->myModel = new TableViewModel(this->game);
    ui.tableView->setModel(myModel);

    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui.tableView->horizontalHeader()->;

    connect(ui.tableView, ui.tableView->clicked(), this, SLOT(onTableClicked(const QModelIndex&)));
}

void ChessGameGUI::onTableClicked(const QModelIndex& index) {
    if (index.isValid()) {
        QString cellText = index.data().toString();
    }
}

ChessGameGUI::~ChessGameGUI() {
    delete this->myModel;
    delete this->game;
}
