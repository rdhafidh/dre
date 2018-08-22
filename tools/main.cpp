#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>

int main(int a, char** b) {
  QGuiApplication app(a, b);
  QGuiApplication::setApplicationName("BusyWaitServer");
  QGuiApplication::setApplicationVersion("0.1.0");
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  QCommandLineOption svr(
      "s",
      QCoreApplication::translate(
          "main", "Server mode")); 
  parser.addOption (svr);
  
  QCommandLineOption cldebug(
      "c",
      QCoreApplication::translate(
          "main", "Client debugging mode")); 
  parser.addOption (cldebug);
  
  parser.process (app);
  if(parser.isSet (svr)){
      
      return app.exec();
  }
  
  return 0;
}