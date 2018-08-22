#include "serverhandler.h"
#include <QGuiApplication>
#include <QLocalServer>

ServerHandler::ServerHandler(QObject *parent) : QObject(parent) {
  server = new QLocalServer;
  connect(server, SIGNAL(newConnection()),this, SLOT(handelClientBaru()));
  server->setMaxPendingConnections(100);
  if (!server->listen("dre_busywait")) {
    this->serverListenFailed();
  }
}

ServerHandler::~ServerHandler() {
    if(server->isListening ()){
        server->close ();
    }
    server->disconnect ();
    delete server;
}

void ServerHandler::serverListenFailed()
{  
    qApp->exit (static_cast<int>(ExitStatusCode::EXIT_SERVER_START_FAIL));
}

void ServerHandler::handelClientBaru()
{
    
}
