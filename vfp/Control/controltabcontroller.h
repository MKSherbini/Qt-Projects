#pragma once
#include <QObject>

namespace Skull {

class ControlTab;
class Instrument;

class ControlTabController : public QObject {
  Q_OBJECT
public:
  explicit ControlTabController(QObject *parent, ControlTab &ctrlTab,
                                Instrument &inst);
  ~ControlTabController();

public slots:
  void OnConnected();
  void OnDisconnected();

private:
  ControlTab &m_controlTab;
  Instrument &m_instrument;

  void WireConnections();

  explicit ControlTabController(const ControlTabController &rhs) = delete;
  ControlTabController &operator=(const ControlTabController &rhs) = delete;
};
} // namespace Skull
