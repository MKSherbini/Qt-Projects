#include "instrument.h"
#include "Model/instsocket.h"
#include "Model/provider.h"
#include "Model/settings.h"
#include "utils.h"
#include <QDebug>

namespace Skull {
Instrument::Instrument(QObject *parent, InstSocket &soc)
    : QObject(parent), m_instSocket(soc), m_lastCommandSent("") {
  WireConnections();
}

Instrument::~Instrument() { Utils::DestructorMsg(this); }

bool Instrument::Connect() {
  Disconnect();
  if (!m_instSocket.Connect()) {
    emit NotifyErrorDetected(tr("ERROR: Did not connect to instrument"));
    return false;
  }
  return true;
}

void Instrument::Disconnect() const {
  if (m_instSocket.IsOpen()) {
    m_instSocket.Disconnect();
  } else {
    emit NotifyDisconnected();
  }
}

bool Instrument::IsConnected() const { return m_instSocket.IsOpen(); }

QString Instrument::GetHostName() const { return m_instSocket.GetHostName(); }

quint16 Instrument::GetPort() const { return m_instSocket.GetPort(); }

void Instrument::SetLongWaitMs(int val) { m_instSocket.SetLongWaitMs(val); }

void Instrument::SetShortWaitMs(int val) { m_instSocket.SetShortWaitMs(val); }

void Instrument::OnConnected() { emit NotifyConnected(); }

void Instrument::OnDisconnected() { emit NotifyDisconnected(); }

void Instrument::OnHostNameChanged(const QString &hostName) {
  m_instSocket.SetHostName(hostName);
}

void Instrument::OnPortChanged(quint16 port) { m_instSocket.SetPort(port); }

void Instrument::OnSendRequest(const QString &dataToSend) {
  m_lastCommandSent = dataToSend;
  qDebug() << "Instrument ready to send data: " << dataToSend;
  m_instSocket.WriteData(dataToSend);
  emit NotifyDataSent(dataToSend);
}

void Instrument::OnReceiveRequest() {
  QString input_buf = m_instSocket.ReadData();
  if (input_buf.size() == 0) {
    emit NotifyDataReceived("No data received");
  } else {
    emit NotifyDataReceived(input_buf);
  }
}

void Instrument::OnPulseWidthChanged(double val) {
  Settings &settings = Provider::GetSettingsAsSingleton();
  auto pw_cmd = settings.getPwCommand() + "%1;";
  auto full_cmd = pw_cmd.arg(val);
  m_instSocket.WriteData(full_cmd);
  emit NotifyStatusUpdated(full_cmd);
}

void Instrument::WireConnections() {
  connect(&m_instSocket, &InstSocket::NotifyConnected, this,
          &Instrument::OnConnected);
  connect(&m_instSocket, &InstSocket::NotifyDisconnected, this,
          &Instrument::OnDisconnected);
}
} // namespace Skull
