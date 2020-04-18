#pragma once

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    public:
    MainWindow(QApplication *application, QWidget *parent = nullptr);
    virtual ~MainWindow();

    private:
    QApplication *application;
    Ui::MainWindow *ui;
};
