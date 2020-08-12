#pragma once
#include <QObject>

namespace Skull {

class SetupTab;
class Instrument;
class Settings;

class SetupTabController : public QObject {
  Q_OBJECT
public:
  explicit SetupTabController(QObject *parent, SetupTab &tab, Instrument &inst,
                              Settings &conf);
  ~SetupTabController();

signals:
  void NotifyConnectEnabled(bool val);
  void NotifyDisconnedEnabled(bool val);
  void NotifyDirectCommandsEnabled(bool val);
  void NotifyControlTabEnabled(bool val);

private slots:
  void OnConnected();
  void OnDisconnected();

private:
  SetupTab &m_setupTab;
  Instrument &m_instrument;

  void WireConnections(Settings &conf);

  explicit SetupTabController(const SetupTabController &rhs) = delete;
  SetupTabController &operator=(const SetupTabController &rhs) = delete;
};
} // namespace Skull
