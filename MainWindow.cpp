#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QGraphicsRectItem>

MainWindow::MainWindow(QApplication *_application, QWidget *_parent)
    : QMainWindow(_parent)
    , application(_application)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

