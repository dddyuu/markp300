#pragma once
#include <Windows.h>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
class ParallelPortController : public QObject
{
    Q_OBJECT
public:
    explicit ParallelPortController(QObject* parent = nullptr);
    ~ParallelPortController();

    bool isAvailable() const;
    void sendData(short port, short data);
    short readData(short port);

private:
    HINSTANCE m_hLib;
    typedef void(__stdcall* Out32)(short, short);
    typedef short(__stdcall* Inp32)(short);
    Out32 m_outp;
    Inp32 m_inp;
    bool m_available;
    QTcpSocket* m_socket;  // TCP 套接字
    QString m_host;
    quint16 m_defaultPort;
};
