#pragma once
#include <QObject>

namespace Skull {
class InstSocket;
class Instrument : public QObject {
  Q_OBJECT
public:
  explicit Instrument(QObject *parent, InstSocket &soc);
  virtual ~Instrument();

  bool Connect();
  void Disconnect() const;
  bool IsConnected() const;

  QString GetHostName() const;
  //  void SetHostName(const QString &val);
  quint16 GetPort() const;
  //  void SetPort(quint16 val);
  void SetLongWaitMs(int val);
  void SetShortWaitMs(int val);

signals:
  void NotifyConnected() const;
  void NotifyDisconnected() const;
  void NotifyDataSent(const QString &dataSent) const;
  void NotifyDataReceived(const QString &dataReceived) const;
  void NotifyErrorDetected(const QString &errorMsg) const;
  void NotifyStatusUpdated(const QString &statusMsg) const;

public slots:
  void OnConnected();
  void OnDisconnected();
  void OnHostNameChanged(const QString &hostName);
  void OnPortChanged(quint16 port);
  void OnSendRequest(const QString &dataToSend);
  void OnReceiveRequest();
  void OnPulseWidthChanged(double val);

private:
  InstSocket &m_instSocket;
  QString m_lastCommandSent;

  void WireConnections();

  explicit Instrument(const Instrument &rhs) = delete;
  Instrument &operator=(const Instrument &rhs) = delete;
};
} // namespace Skull
