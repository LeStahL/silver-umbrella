#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char **args)
{
    QApplication *application = new QApplication(argc, args);
    MainWindow *mainWindow = new MainWindow(application, nullptr);
    mainWindow->show();
    return application->exec();
}
