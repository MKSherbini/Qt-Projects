#ifndef SETUPTAB_H
#define SETUPTAB_H

#include <QWidget>

class QStringListModel;

namespace Ui {
class SetupTab;
}

namespace Skull {

class SetupTab : public QWidget {
  Q_OBJECT

public:
  explicit SetupTab(QWidget *parent = nullptr);
  ~SetupTab();

  void SetHostName(const QString &val);
  void SetPort(quint16 val);
  void SetCommands(QStringListModel &cmds);

signals:
  void NotifyHostNameChanged(const QString &val);
  void NotifyPortChanged(quint16 val);
  void NotifyConnectClicked();
  void NotifyDisconnectClicked();
  void NotifySendClicked(const QString &dataToSend);
  void NotifyReceiveClicked();

public slots:
  void OnStatusUpdated(const QString &statusMsg);
  void OnConnected();
  void OnDisconnected();
  void OnDataSent(const QString &dataSent);
  void OnDataReceived(const QString &dataRead);
  void OnConnectEnabled(bool isEnabled);
  void OnDisconnectEnabled(bool isEnabled);
  void OnDirectCommandsEnabled(bool isEnabled);
  void OnControlTabEnabled(bool isEnabled);

private slots:
  void on_editIpAdress_editingFinished();

  void on_editPort_editingFinished();

  void on_btnConnect_clicked();

  void on_btnDisconnect_clicked();

  void on_btnSend_clicked();

  void on_btnReceive_clicked();

  void on_btnClear_clicked();

private:
  Ui::SetupTab *ui;
};
} // namespace Skull
#endif // SETUPTAB_H
