#include "ChessGameGUI.h"

ChessGameGUI::ChessGameGUI(QWidget *parent)
    : QMainWindow(parent)
{
    
    ui.setupUi(this);

    //std::unique_ptr<TableViewModel> myModel(new TableViewModel());
    Game* game = new Game();
    Game game2;

    this->myModel = new TableViewModel(game);
    ui.tableView->setModel(myModel);

    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui.tableView->horizontalHeader()->;
    auto x = &QTableView::clicked;
    //connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
    connect(ui.tableView, &QTableView::clicked, this, &ChessGameGUI::onTableClicked);
}

void ChessGameGUI::onTableClicked() {
    
    QModelIndexList selectedPiece = this->ui.tableView->selectionModel()->selectedIndexes();

    short unsigned i = selectedPiece.at(0).row(), j = selectedPiece.at(0).column();

    this->myModel->tableClicked(i, j);

    
}

ChessGameGUI::~ChessGameGUI() {
    delete this->myModel;
}
