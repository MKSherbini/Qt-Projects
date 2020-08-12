#pragma once
#include <QWidget>

namespace Skull {
class Utils {
public:
  Utils();

  static void DestructorMsg(const QString &msg);
  static void DestructorMsg(const QObject *const o);

  template <typename T, typename... Args>
  static std::unique_ptr<T> make_unique(Args &&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

private:
  explicit Utils(const Utils &rhs) = delete;
  Utils &operator=(const Utils &rhs) = delete;
};
} // namespace Skull
