#pragma once
#include <QObject>

class QTcpSocket;

namespace Skull {
class InstSocket : public QObject {
  Q_OBJECT
public:
  explicit InstSocket(QObject *parent = 0);
  bool Connect();
  bool IsOpen();
  void Disconnect();

  QString GetHostName() const { return m_hostName; }
  void SetHostName(const QString &val);
  quint16 GetPort() const { return m_port; }
  void SetPort(quint16 val);
  void SetLongWaitMs(int val) { m_longWaitMs = val; }
  void SetShortWaitMs(int val) { m_shortWaitMs = val; }
  QString ReadData() const;
  void WriteData(const QString &data) const;

  ~InstSocket();
signals:
  void NotifyConnected();
  void NotifyDisconnected();

private slots:
  void OnConnected();
  void OnDisconnected();

private:
  QTcpSocket &m_socket;
  QString m_hostName;
  quint16 m_port;
  int m_shortWaitMs;
  int m_longWaitMs;

  explicit InstSocket(const InstSocket &rhs) = delete;
  InstSocket &operator=(const InstSocket &rhs) = delete;
};
} // namespace Skull
