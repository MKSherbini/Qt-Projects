#pragma once
#include <QObject>

namespace Skull {
class MainWindow;
class SetupTab;
class Instrument;
class SetupTabController;
class ControlTab;
class ControlTabController;

class Startup final : public QObject {
  Q_OBJECT
public:
  explicit Startup();
  void show() const;

  ~Startup();

private:
  SetupTab &m_setupTab;
  ControlTab &m_controlTab;
  MainWindow &m_mainWindow;
  Instrument *m_instrument;
  SetupTabController *m_setupCon;
  ControlTabController *m_controlTabCon;

  explicit Startup(const Startup &rhs) = delete;
  Startup &operator=(const Startup &rhs) = delete;
};
} // namespace Skull
