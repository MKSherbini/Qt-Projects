#include "utils.h"
#include <QString>
#include <QtDebug>

namespace Skull {
static QString DESTRUCTOR_MSG = QStringLiteral("Running the %1 destructor.");

void Utils::DestructorMsg(const QString &msg) {
  qDebug() << DESTRUCTOR_MSG.arg(msg);
}
void Utils::DestructorMsg(const QObject *const o) {
  qDebug() << DESTRUCTOR_MSG.arg(o->metaObject()->className());
}
} // namespace Skull
