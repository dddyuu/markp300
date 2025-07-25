#include "parallelportcontroller.h"
#include "QDebug"
#include <QThread> 
#include <QTimer>
ParallelPortController::ParallelPortController(QObject* parent)
    : QObject(parent), m_hLib(nullptr), m_outp(nullptr), m_inp(nullptr),m_socket(new QTcpSocket(this))
{
//    m_hLib = LoadLibraryA("inpoutx64.dll");
//    if (!m_hLib) {
//        m_available = false;
//        return;
//    }

//    m_outp = (Out32)GetProcAddress(m_hLib, "Out32");
//    m_inp = (Inp32)GetProcAddress(m_hLib, "Inp32");
//    m_available = m_outp && m_inp;
    m_host = "127.0.0.1";
    m_defaultPort = 8888;
    m_socket->connectToHost(m_host, m_defaultPort);
    if (m_socket->waitForConnected(3000)) { // 等待 3 秒
        qDebug() << "Connected to server:" << m_host << ":" << m_defaultPort;
        m_available = true;
    } else {
        qDebug() << "Failed to connect to server:" << m_socket->errorString();
        m_available = false;
    }
    connect(m_socket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });

}

ParallelPortController::~ParallelPortController()
{
    if (m_hLib) FreeLibrary(m_hLib);
    if (m_socket) {
            m_socket->disconnectFromHost();
            m_socket->deleteLater();
        }
}

bool ParallelPortController::isAvailable() const { return m_available; }

void ParallelPortController::sendData(short port, short data)
{
//    qDebug() << data;
//        if (m_available) {
//            m_outp(port, data); // 发送原始数据

//            // 创建一次性定时器，5ms后发送0
//            QTimer::singleShot(5, this, [this, port]() {
//                m_outp(port, 0); // 延时后发送0
//                });
//        }
    qDebug() << "Sending data:" << data << "to port:" << port;
    if (!m_available) {
        qDebug() << "Cannot send data: TCP connection not available.";
        return;
    }
    if (m_socket->peerPort() != port) {
        m_socket->disconnectFromHost();
        m_socket->connectToHost(m_host, port);
        if (!m_socket->waitForConnected(3000)) {
            qDebug() << "Failed to connect to port" << port << ":" << m_socket->errorString();
            m_available = false;
            return;
        }
        m_available = true;
    }
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << data;
    qint64 bytesWritten = m_socket->write(buffer);
    if (bytesWritten == -1) {
        qDebug() << "Failed to send data:" << m_socket->errorString();
        m_available = false;
    } else {
        qDebug() << "Sent" << bytesWritten << "bytes.";
    }

    m_socket->flush();
}

short ParallelPortController::readData(short port)
{
    return m_available ? m_inp(port) : -1;
}
