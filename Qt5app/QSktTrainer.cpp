#include <QApplication>
#include "mainwindow.h"

#include "../libskt/jackaudioclient.h"

int main(int argc, char* argv[])
{
  QApplication * app = new QApplication(argc, argv);
  MainWindow mw;
  mw.show();

  AbstractAudioClient * c = JackAudioClient::getInstance();
  AbstractAudioClient::StringList l = c->getAudioDevices(AbstractAudioClient::PortType::input);
  c->connectToDevice(l[1],AbstractAudioClient::PortType::input);
  c->getAudioDevices(AbstractAudioClient::PortType::output);

  return app->exec();
}
