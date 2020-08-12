#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QTcpServer;
class QTcpSocket;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_btnStartServer_clicked();

  void on_btnStopServer_clicked();

private:
  Ui::MainWindow *ui;
  QTcpServer *m_Server;
  QTcpSocket *m_Socket;
  bool StartServer();
  void StopServer();
  void ExhangeData();
  void EchoReadData();
};
#endif // MAINWINDOW_H
