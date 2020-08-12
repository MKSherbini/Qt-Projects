#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

static int PORT_NUMBER = 23;
static int WAIT_FOR_DATA_MS = 200;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_Server(new QTcpServer(this)), m_Socket(nullptr) {
  ui->setupUi(this);
  ui->btnStopServer->setEnabled(false);
  connect(m_Server, &QTcpServer::newConnection, this, &MainWindow::ExhangeData);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnStartServer_clicked() {
  StartServer();
  ui->btnStartServer->setEnabled(false);
  ui->btnStopServer->setEnabled(true);
}

void MainWindow::on_btnStopServer_clicked() {
  StopServer();
  ui->btnStartServer->setEnabled(true);
  ui->btnStopServer->setEnabled(false);
}

bool MainWindow::StartServer() {
  bool res = m_Server->listen(QHostAddress::Any, PORT_NUMBER);
  if (!res) {
    QMessageBox::critical(
        this, tr("Echo Server"),
        tr("Unable to start server: %1").arg(m_Server->errorString()));
    return false;
  }
  return true;
}

void MainWindow::StopServer() {
  m_Server->close();
  if (m_Socket && m_Socket->isOpen())
    m_Socket->close();
}

void MainWindow::ExhangeData() {
  m_Socket = m_Server->nextPendingConnection();
  if (m_Socket->isOpen()) {
    connect(m_Socket, &QTcpSocket::readyRead, this, &MainWindow::EchoReadData);
  }
}

void MainWindow::EchoReadData() {
  m_Socket->write("<echoserver>\n");
  QString res;
  while (!m_Socket->atEnd()) {
    res.append(m_Socket->readAll());
    m_Socket->waitForReadyRead(WAIT_FOR_DATA_MS);
  }
  m_Socket->write(qPrintable(res));
  m_Socket->write("\n</echoserver>");
}
