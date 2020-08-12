#include "setuptab.h"
#include "ui_setuptab.h"
#include "utils.h"
#include <QString>
#include <QStringListModel>
#include <QStringLiteral>

namespace Skull {
SetupTab::SetupTab(QWidget *parent) : QWidget(parent), ui(new Ui::SetupTab) {
  ui->setupUi(this);
}

SetupTab::~SetupTab() {
  Utils::DestructorMsg(this);
  delete ui;
}

void SetupTab::SetHostName(const QString &val) {
  ui->editIpAdress->setText(val);
  emit NotifyHostNameChanged(val);
}

void SetupTab::SetPort(quint16 val) {
  ui->editPort->setText(QString::number(val));
  emit NotifyPortChanged(val);
}

void SetupTab::SetCommands(QStringListModel &cmds) {
  ui->cmbCommands->setModel(&cmds);
}

void SetupTab::OnStatusUpdated(const QString &statusMsg) {
  ui->txtMessages->append(statusMsg);
}

void SetupTab::OnConnected() {
  ui->txtMessages->append(QString(tr("Connected")));
}

void SetupTab::OnDisconnected() {
  ui->txtMessages->append(QString(tr("Disonnected")));
}

void SetupTab::OnDataSent(const QString &dataSent) {
  ui->txtMessages->append(QString(tr("Data Sent: ")) + dataSent);
}

void SetupTab::OnDataReceived(const QString &dataRead) {
  ui->txtMessages->append(QString(tr("Data Received: ")) + dataRead);
}

void SetupTab::OnConnectEnabled(bool isEnabled) {
  ui->btnConnect->setEnabled(isEnabled);
}

void SetupTab::OnDisconnectEnabled(bool isEnabled) {
  ui->btnDisconnect->setEnabled(isEnabled);
}

void SetupTab::OnDirectCommandsEnabled(bool isEnabled) {
  ui->gbDirectCommands->setEnabled(isEnabled);
}

void SetupTab::OnControlTabEnabled(bool isEnabled) {
  //    ui->gbDirectCommands->setEnabled(isEnabled);
  // TODO
}
void SetupTab::on_editIpAdress_editingFinished() {
  emit NotifyHostNameChanged(ui->editIpAdress->text());
}

void SetupTab::on_editPort_editingFinished() {
  bool ok;
  int res = ui->editPort->text().toUInt(&ok);
  if (!ok || (res > USHRT_MAX)) {
    ui->txtMessages->append(
        tr((QString("Invalid Port Number ") + QString::number(res))
               .toStdString()
               .c_str()));
  } else {
    emit NotifyPortChanged(res);
  }
}

void SetupTab::on_btnConnect_clicked() { emit NotifyConnectClicked(); }

void SetupTab::on_btnDisconnect_clicked() { emit NotifyDisconnectClicked(); }

void SetupTab::on_btnSend_clicked() {
  emit NotifySendClicked(ui->cmbCommands->currentText());
}

void SetupTab::on_btnReceive_clicked() { emit NotifyReceiveClicked(); }

void SetupTab::on_btnClear_clicked() { ui->txtMessages->clear(); }

} // namespace Skull
