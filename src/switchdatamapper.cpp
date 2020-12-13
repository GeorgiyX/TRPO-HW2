#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "switchdatamapper.h"
#include "businesslogic.h"

void SwitchDataMapper::updateConfig(const Configuration &config)
{
  QSqlQuery query;
  query.prepare("UPDATE Configuration SET work_mode = :wm, spec_iface = :sif, "
                "replace_byte = :rb, ip_filter = :if WHERE id is 1");
  query.bindValue(":wm", QString::number(config.workMode));
  query.bindValue(":rb", QString::number(config.specByte));
  query.bindValue(":sif", QString::number(config.specIface));
  query.bindValue(":if", QString::number(config.isIpFilterEnable));
  query.exec();
}

Configuration SwitchDataMapper::getConfig()
{
  /*получаем последний ID*/
  QSqlQuery query("SELECT work_mode, spec_iface, replace_byte, ip_filter FROM Configuration WHERE id is 1");
  if (!query.isActive() || !query.isSelect() || !query.next()) {
    throw std::runtime_error("can't execute SQL \"getConfig\" code");
  }
  Configuration config;
  config.workMode = query.value(0).toUInt();
  config.specIface = query.value(1).toUInt();
  config.specByte = query.value(2).toUInt();
  config.isIpFilterEnable = query.value(3).toBool();
  return config;
}

void SwitchDataMapper::addNewAddress(const IpAddress &address)
{
  /*получаем последний ID*/
  QSqlQuery queryId("SELECT max(id) FROM IpAddresses");
  if (!queryId.isActive() || !queryId.isSelect() || !queryId.next()) {
    throw std::runtime_error("can't execute SQL \"getAllAddresses\" code");
  }
  size_t id = queryId.value(0).toUInt() + 1;
  /*добавим запись*/
  QSqlQuery queryInsert;
  queryInsert.prepare("INSERT INTO IpAddresses (id, address) VALUES(:id, :address)");
  queryInsert.bindValue(":id", QString::number(id));
  queryInsert.bindValue(":address", address.address);
  queryInsert.exec();
}

void SwitchDataMapper::updateAddress(const IpAddress &address)
{
  QSqlQuery query;
  query.prepare("UPDATE IpAddresses SET address = :address WHERE id is :id");
  query.bindValue(":id", QString::number(address.id));
  query.bindValue(":address", address.address);
  query.exec();
}

void SwitchDataMapper::deleteAddress(const IpAddress &address)
{
  QSqlQuery query;
  query.prepare("DELETE FROM IpAddresses WHERE id is :id");
  query.bindValue(":id", QString::number(address.id));
  query.exec();
}

QList<IpAddress> SwitchDataMapper::getAllAddresses()
{
  QSqlQuery query("SELECT id, address FROM IpAddresses");
  if (!query.isActive()) {
    throw std::runtime_error("can't execute SQL \"getAllAddresses\" code");
  }
  QList<IpAddress> ipList;
  while (query.next()) {
    ipList.append({
                    query.value(0).toUInt(),
                    query.value(1).toString()
                  });
  }
  return ipList;
}

LoginPasswod SwitchDataMapper::getLoginAndPassword()
{
  QSqlQuery query("SELECT login, password_hash FROM AuthInfo WHERE id is 1");
  if (!query.isActive()) {
    throw std::runtime_error("can't execute SQL \"getLoginAndPassword\" code");
  }
  LoginPasswod loginPassword;
  while (query.next()) {
    loginPassword.login = query.value(0).toString();
    loginPassword.passwordHash = query.value(1).toString();
  }
  return loginPassword;
}

SwitchDataMapper &SwitchDataMapper::instance()
{
  static SwitchDataMapper instance;
  return instance;
}

SwitchDataMapper::SwitchDataMapper() : _databaseConnection(QSqlDatabase::addDatabase("QSQLITE") /*соединение по умолчанию*/)
{
  /*создаст сам файлик, если не найдет переданный*/
  _databaseConnection.setDatabaseName("./data/switchcontrol.sqlite");
  if (!_databaseConnection.open()) {
    throw std::runtime_error(("can't create connection to DB: " +
                              _databaseConnection.lastError().text()).toStdString());
  }
}

SwitchDataMapper::~SwitchDataMapper()
{
  _databaseConnection.close();
}
