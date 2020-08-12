#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QWidget>

namespace Ui {
class ControlTab;
}

namespace Skull {
class ControlTab : public QWidget {
  Q_OBJECT

public:
  explicit ControlTab(QWidget *parent = nullptr);
  ~ControlTab();
  void EnablePanel(bool isEnabled);
signals:
  void NotifyPulseWidthChanged(double val);

private slots:
  void on_spinPulseWidth_valueChanged(double val);

private:
  Ui::ControlTab *ui;
};
} // namespace Skull
#endif // CONTROLTAB_H
