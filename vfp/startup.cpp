#include "startup.h"
#include "Control/controltabcontroller.h"
#include "Control/setuptabcontroller.h"
#include "Model/instrument.h"
#include "Model/instsocket.h"
#include "Model/provider.h"
#include "Model/settings.h"
#include "View/controltab.h"
#include "View/mainwindow.h"
#include "View/setuptab.h"
#include "utils.h"

namespace Skull {
Startup::Startup()
    : QObject(nullptr), m_setupTab(*new SetupTab(nullptr)),
      m_controlTab(*new ControlTab(nullptr)),
      m_mainWindow(*new MainWindow(nullptr, m_setupTab, m_controlTab)),
      m_instrument(new Instrument(this, *new InstSocket(this))),
      m_setupCon(new SetupTabController(this, m_setupTab, *m_instrument,
                                        Provider::GetSettingsAsSingleton())),
      m_controlTabCon(
          new ControlTabController(this, m_controlTab, *m_instrument)) {
  //  Settings &my_settings = Provider::GetSettingsAsSingleton();
  //  my_settings.ParseJsonData();
  //  int x = 0; debugger is crazy
  m_instrument->Disconnect();
}

void Startup::show() const { m_mainWindow.show(); }

Startup::~Startup() {
  Utils::DestructorMsg(this);
  delete &m_mainWindow;
}
} // namespace Skull
