#include <QApplication>
#include "mainwindow.h"

#include "../libskt/jackaudioclient.h"

int main(int argc, char* argv[])
{
  QApplication * app = new QApplication(argc, argv);
  MainWindow mw;
  mw.show();

  JackAudioClient c = JackAudioClient::getInstance();
  return app->exec();
}
