#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QObject>
class QLocalServer;

enum class ExitStatusCode {
    EXIT_UNKNOWN_ERROR,
    EXIT_SERVER_START_FAIL
};

class ServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit ServerHandler(QObject *parent = nullptr);
    ~ServerHandler();
    
Q_SIGNALS:
    
public Q_SLOTS:
    
private Q_SLOTS:
    void serverListenFailed();
    void handelClientBaru();
    
private:
    QLocalServer *server;
};

#endif // SERVERHANDLER_H