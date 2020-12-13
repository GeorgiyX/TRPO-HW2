#ifndef SWITCHDATAMAPPER_H
#define SWITCHDATAMAPPER_H

#include <QtSql/QSqlDatabase>
#include "businesslogic.h"



class SwitchDataMapper
{
public:
  void updateConfig(const Configuration &config);
  Configuration getConfig();
  void addNewAddress(const IpAddress &address);
  void updateAddress(const IpAddress &address);
  void deleteAddress(const IpAddress &address);
  QList<IpAddress> getAllAddresses();
  LoginPasswod getLoginAndPassword();
  static SwitchDataMapper &instance();

private:
  SwitchDataMapper();
  ~SwitchDataMapper();
  QSqlDatabase _databaseConnection;


};

#endif // SWITCHDATAMAPPER_H
