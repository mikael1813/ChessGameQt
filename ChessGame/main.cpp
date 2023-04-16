#include "ChessGameGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QTableView tableView;
    TableViewModel myModel;
    tableView.setModel(&myModel);
    tableView.show();*/
    ChessGameGUI w;
    w.show();
    return a.exec();
}
