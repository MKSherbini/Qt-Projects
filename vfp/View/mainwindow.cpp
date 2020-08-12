#include "mainwindow.h"
#include "View/aboutbox.h"
#include "View/controltab.h"
#include "View/setuptab.h"
#include "ui_mainwindow.h"
#include "utils.h"

namespace Skull {
MainWindow::MainWindow(QWidget *parent, SetupTab &setup, ControlTab &control)
    : QMainWindow(parent), m_setupTab(setup), m_controlTab(control),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_setupTab.setParent(this);
  m_controlTab.setParent(this);
  ui->loSetupTab->addWidget(&m_setupTab);
  ui->loControlTab->addWidget(&m_controlTab);
}

MainWindow::~MainWindow() {
  Utils::DestructorMsg(this);

  delete ui;
}
void MainWindow::on_action_Exit_triggered() { QApplication::quit(); }

void MainWindow::on_action_About_triggered() {
  // TODO
  AboutBox about;
  about.show();
  about.exec();
}

} // namespace Skull
