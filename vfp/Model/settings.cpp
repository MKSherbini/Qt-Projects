#include "settings.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QStandardPaths>
#include <QString>
#include <QStringListModel>
#include <utility>

namespace Skull {

static const int PW_CMD_INDEX = 5;
static auto RESOURCE_PREFIX = QStringLiteral(":/json");
Settings::Settings(QObject *parent, QString filename)
    : QObject(parent), m_filename(filename),
      m_modelCommands(*new QStringListModel(this)) {}

void Settings::ParseJsonData() {
  QString raw_json = ReadJsonFile();
  if (raw_json.size() == 0)
    return;

  auto json_res = GetJsonObject(raw_json);
  auto json_err = json_res.second;
  if (json_err.error != QJsonParseError::NoError) {
    ShowJsonParseError(json_err);
  }
  auto json_obj = json_res.first;
  m_applicationName = json_obj["applicationTitle"].toString();
  m_appShortName = json_obj["appShortName"].toString();
  m_hostName = json_obj["hostName"].toString();
  m_portNumber = json_obj["port"].toInt();
  m_longWaitMs = json_obj["tcpWaitMs"].toInt();
  m_shortWaitMs = json_obj["readWaitMs"].toInt();

  SetupCommands(json_obj);
}
QString Settings::ReadJsonFile() {
  auto default_settings =
      ReadJsonFromInternalResource(); // TODO do only if you need to ie. when
                                      // custom config fails
  QDir config_dir = OpenConfigurationDirectory();
  auto path = config_dir.filePath(m_filename);
  QFile std_file(path);
  if (std_file.exists()) {
    if (!std_file.open(QFile::ReadOnly | QFile::Text)) {
      SendErrorMessage("Could not open " + path);
      return default_settings;
    }
    QString settings = std_file.readAll();
    std_file.close();
    return settings;
  } else {
    WriteDefaultstoStdConfigFile(std_file, default_settings);
    return default_settings;
  }
}

void Settings::WriteDefaultstoStdConfigFile(QFile &stdConfigFile,
                                            const QString &settings) {
  int len = settings.size();
  if (!stdConfigFile.open(QFile::WriteOnly | QFile::Text)) {
    SendErrorMessage("Could not open file to write to " +
                     stdConfigFile.fileName());
  }
  auto bytes_written = stdConfigFile.write(qPrintable(settings), len);
  if (bytes_written != len) {
    SendErrorMessage("Could not write the settings to " +
                     stdConfigFile.fileName());
    if (!stdConfigFile.remove()) {
      SendErrorMessage("Could not remove config file. Please delete manually " +
                       stdConfigFile.fileName());
    }
  }
  stdConfigFile.close();
}
QDir Settings::OpenConfigurationDirectory() {
  QDir config_dir(
      QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
  if (!config_dir.exists()) {
    QDir dir;
    dir.mkpath(config_dir.path());
  }
  return config_dir;
}
void Settings::SetupCommands(const QJsonObject &jo) {
  QJsonArray cmd_array = jo["commands"].toArray();
  QStringList cmd_list;
  for (auto item : cmd_array) {
    cmd_list.append(item.toString());
  }
  m_modelCommands.setStringList(cmd_list);

  auto index = m_modelCommands.index(PW_CMD_INDEX);
  auto test_cmd = m_modelCommands.data(index, Qt::DisplayRole);
  qDebug() << "test_cmd " << test_cmd.toString();

  if (PW_CMD_INDEX < cmd_list.size()) {
    m_pwCommand = cmd_list[PW_CMD_INDEX];
  } else {
    emit NotifyStatusMessage(tr("Unable to get pulse width command"));
  }
}

JsonObjErrPair Settings::GetJsonObject(const QString &rawJson) {
  QJsonParseError json_parse_error;
  QJsonDocument json_doc =
      QJsonDocument::fromJson(rawJson.toUtf8(), &json_parse_error);
  auto json_obj = json_doc.object();
  return std::make_pair(json_obj, json_parse_error);
}

QString Settings::ReadJsonFromInternalResource() {
  QDir res_dir(RESOURCE_PREFIX);
  if (!res_dir.exists()) {
    SendErrorMessage("Internal resource path misssing " +
                     res_dir.canonicalPath());
    return "";
  }
  auto path = res_dir.filePath(m_filename);
  QFile res_file(path);

  if (!res_file.open(QFile::ReadOnly | QFile::Text)) {
    SendErrorMessage("Couldn't open internal resource" + path);
    return "";
  }
  QString settings = res_file.readAll();
  return settings;
}

void Settings::SendErrorMessage(const QString &msg) {
  emit NotifyStatusMessage(msg);
}
void Settings::ShowJsonParseError(QJsonParseError err) {
  QString msg = tr("Error parsing json settings file.\n");
  msg.append(err.errorString());
  //  msg.append(tr("\nThe default value will be used."));
  QMessageBox::critical(0, tr("VFP"), msg);
}

JsonObjErrPair Settings::GetJsonPair(const QString &rawJson) {}

} // namespace Skull
