#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>

namespace Ui {
class AboutBox;
}
namespace Skull {

class AboutBox : public QDialog {
  Q_OBJECT

public:
  explicit AboutBox(QWidget *parent = nullptr);
  ~AboutBox();

private:
  Ui::AboutBox *ui;
};

} // namespace Skull
#endif // ABOUTBOX_H
