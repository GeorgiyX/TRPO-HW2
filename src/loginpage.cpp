#include "loginpage.h"
#include "ui_loginpage.h"
#include "businesslogic.h"
#include <QCryptographicHash>
#include "QDebug"
#include "switchdatamapper.h"

LoginPage::LoginPage(QWidget *parent) :
  QWidget(parent),
  _ui(new Ui::LoginPage)
{
  _ui->setupUi(this);
  connect(_ui->btnGoLogin, &QPushButton::clicked, this, &LoginPage::tryLogin);
}

LoginPage::~LoginPage()
{
  delete _ui;
}

void LoginPage::tryLogin()
{
  if (isLoginPasswordCorrect()) {
    emit loginSuccsess();
  } else {
    qDebug() << "incorrect login or password";
  }
}

bool LoginPage::isLoginPasswordCorrect()
{
  LoginPasswod loginPassword {
    _ui->leLogin->text(),
    QString(QCryptographicHash::hash(_ui->lePassword->text().toUtf8(), QCryptographicHash::Sha256).toHex())
  };
  qDebug() << "Сurrent password hash: " <<  loginPassword.passwordHash;
  return loginPassword == SwitchDataMapper::instance().getLoginAndPassword();
}
