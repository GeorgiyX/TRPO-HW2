#ifndef BUSNESSLOGIC_H
#define BUSNESSLOGIC_H

#include <QString>

/**
 * @brief Обьект IP адреса
 */
struct IpAddress{
  size_t id;
  QString address;
};

/**
 * @brief Объект с учетными данными
 */
struct LoginPasswod {
  QString login;
  QString passwordHash;
  bool operator==(const LoginPasswod & rhs) {
    return login == rhs.login && passwordHash == rhs.passwordHash;
  };
};

/**
 * @brief Объект конфигурации коммутатора
 */
struct Configuration {
  size_t workMode;
  bool isIpFilterEnable;
  size_t specIface;
  size_t specByte;
};


#endif // BUSNESSLOGIC_H
