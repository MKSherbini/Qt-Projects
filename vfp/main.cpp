#include "startup.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Skull::Startup w;
  QObject::connect(&a, &QApplication::lastWindowClosed, &a,
                   &QApplication::quit); // why ?
  w.show();
  return a.exec();
}
