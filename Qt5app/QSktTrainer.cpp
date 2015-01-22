#include <QApplication>
#include "mainwindow.h"
int main(int argc, char* argv[])
{
  QApplication * app = new QApplication(argc, argv);
  MainWindow mw;
  mw.show();

  return app->exec();
}
