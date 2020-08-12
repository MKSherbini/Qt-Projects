#include "instsocket.h"
#include "utils.h"
#include <QDebug>
#include <QTcpSocket>

namespace Skull {
InstSocket::InstSocket(QObject *parent)
    : QObject(parent), m_socket(*new QTcpSocket(this)), m_hostName(""),
      m_port(0), m_shortWaitMs(0), m_longWaitMs(0)

{
  connect(&m_socket, &QTcpSocket::connected, this, &InstSocket::OnConnected);
  connect(&m_socket, &QTcpSocket::disconnected, this,
          &InstSocket::OnDisconnected);
}

bool InstSocket::Connect() {
  qDebug() << "Attempting to connect to " << m_hostName << " on port " << m_port
           << " with wait of " << m_longWaitMs;
  m_socket.connectToHost(m_hostName, m_port, QTcpSocket::ReadWrite);
  return m_socket.waitForConnected(m_longWaitMs); // can add error handling here
}

bool InstSocket::IsOpen() { return m_socket.isOpen(); }

void InstSocket::Disconnect() {
  if (IsOpen())
    m_socket.disconnectFromHost();
}

void InstSocket::SetHostName(const QString &val) { m_hostName = val; }

void InstSocket::SetPort(quint16 val) { m_port = val; }

QString InstSocket::ReadData() const {
  if (!m_socket.isReadable()) {
    return "ERROR: Socket is not readable";
  }
  QString res;
  while (!m_socket.atEnd()) {
    res.append(m_socket.readAll());
    m_socket.waitForReadyRead(m_shortWaitMs);
  }
  return res;
}

void InstSocket::WriteData(const QString &data) const {
  if (!m_socket.isWritable()) {
    // TODO error
  }
  int bytes_written = m_socket.write(qPrintable(data));
  qDebug() << "Bytes written: " << bytes_written;
}

InstSocket::~InstSocket() { Utils::DestructorMsg(this); }

void InstSocket::OnConnected() { emit NotifyConnected(); }

void InstSocket::OnDisconnected() { emit NotifyDisconnected(); }

} // namespace Skull
