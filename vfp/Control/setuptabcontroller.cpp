#include "setuptabcontroller.h"
#include "Model/instrument.h"
#include "Model/settings.h"
#include "View/setuptab.h"
#include "utils.h"

namespace Skull {
SetupTabController::SetupTabController(QObject *parent, SetupTab &tab,
                                       Instrument &inst, Settings &conf)
    : QObject(parent), m_setupTab(tab), m_instrument(inst) {
  WireConnections(conf);
  conf.ParseJsonData();

  m_setupTab.SetHostName(conf.getHostName());
  m_setupTab.SetPort(conf.getPortNumber());
  m_setupTab.SetCommands(conf.getCommandsAsModel());
  m_instrument.SetLongWaitMs(conf.getLongWaitMs());
  m_instrument.SetShortWaitMs(conf.getShortWaitMs());
}

SetupTabController::~SetupTabController() { Utils::DestructorMsg(this); }

void SetupTabController::OnConnected() {
  emit NotifyConnectEnabled(false);
  emit NotifyDisconnedEnabled(true);
  emit NotifyControlTabEnabled(true);
  emit NotifyDirectCommandsEnabled(true);
}

void SetupTabController::OnDisconnected() {
  emit NotifyConnectEnabled(true);
  emit NotifyDisconnedEnabled(false);
  emit NotifyControlTabEnabled(false);
  emit NotifyDirectCommandsEnabled(false);
}

void SetupTabController::WireConnections(Settings &conf) {
  // Settings
  connect(&conf, &Settings::NotifyStatusMessage, &m_setupTab,
          &SetupTab::OnStatusUpdated);
  // Host and Port
  connect(&m_setupTab, &SetupTab::NotifyHostNameChanged, &m_instrument,
          &Instrument::OnHostNameChanged);
  connect(&m_setupTab, &SetupTab::NotifyPortChanged, &m_instrument,
          &Instrument::OnPortChanged);
  // Messages
  connect(&m_instrument, &Instrument::NotifyErrorDetected, &m_setupTab,
          &SetupTab::OnStatusUpdated);
  connect(&m_instrument, &Instrument::NotifyStatusUpdated, &m_setupTab,
          &SetupTab::OnStatusUpdated);
  // Buttons
  connect(&m_instrument, &Instrument::NotifyConnected, &m_setupTab,
          &SetupTab::OnConnected);
  connect(&m_setupTab, &SetupTab::NotifyConnectClicked, &m_instrument,
          &Instrument::Connect);

  connect(&m_instrument, &Instrument::NotifyDisconnected, &m_setupTab,
          &SetupTab::OnDisconnected);
  connect(&m_setupTab, &SetupTab::NotifyDisconnectClicked, &m_instrument,
          &Instrument::Disconnect);

  connect(&m_instrument, &Instrument::NotifyDataSent, &m_setupTab,
          &SetupTab::OnDataSent);
  connect(&m_setupTab, &SetupTab::NotifySendClicked, &m_instrument,
          &Instrument::OnSendRequest);

  connect(&m_instrument, &Instrument::NotifyDataReceived, &m_setupTab,
          &SetupTab::OnDataReceived);
  connect(&m_setupTab, &SetupTab::NotifyReceiveClicked, &m_instrument,
          &Instrument::OnReceiveRequest);

  connect(&m_instrument, &Instrument::NotifyConnected, this,
          &SetupTabController::OnConnected);
  connect(&m_instrument, &Instrument::NotifyDisconnected, this,
          &SetupTabController::OnDisconnected);

  // DiplayUpdate
  connect(this, &SetupTabController::NotifyConnectEnabled, &m_setupTab,
          &SetupTab::OnConnectEnabled);
  connect(this, &SetupTabController::NotifyDisconnedEnabled, &m_setupTab,
          &SetupTab::OnDisconnectEnabled);
  connect(this, &SetupTabController::NotifyDirectCommandsEnabled, &m_setupTab,
          &SetupTab::OnDirectCommandsEnabled);
  connect(this, &SetupTabController::NotifyControlTabEnabled, &m_setupTab,
          &SetupTab::OnControlTabEnabled);
}

} // namespace Skull
