#include "controltabcontroller.h"
#include "Model/instrument.h"
#include "View/controltab.h"
#include "utils.h"

namespace Skull {
ControlTabController::ControlTabController(QObject *parent, ControlTab &ctrlTab,
                                           Instrument &inst)
    : QObject(parent), m_controlTab(ctrlTab), m_instrument(inst) {
  WireConnections();
}

ControlTabController::~ControlTabController() { Utils::DestructorMsg(this); }

void ControlTabController::OnConnected() { m_controlTab.EnablePanel(true); }

void ControlTabController::OnDisconnected() { m_controlTab.EnablePanel(false); }

void ControlTabController::WireConnections() {
  // controls
  connect(&m_controlTab, &ControlTab::NotifyPulseWidthChanged, &m_instrument,
          &Instrument::OnPulseWidthChanged);

  // connected
  connect(&m_instrument, &Instrument::NotifyConnected, this,
          &ControlTabController::OnConnected);
  connect(&m_instrument, &Instrument::NotifyDisconnected, this,
          &ControlTabController::OnDisconnected);
}
} // namespace Skull
