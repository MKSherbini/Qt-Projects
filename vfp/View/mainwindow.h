#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace Skull {
class SetupTab;
class ControlTab;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent, SetupTab &setup, ControlTab &control);
  ~MainWindow();

private slots:
  void on_action_Exit_triggered();

  void on_action_About_triggered();

private:
  SetupTab &m_setupTab;
  ControlTab &m_controlTab;

  Ui::MainWindow *ui;
};
} // namespace Skull
#endif // MAINWINDOW_H
