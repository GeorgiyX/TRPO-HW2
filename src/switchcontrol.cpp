#include "switchcontrol.h"
#include "switchdatamapper.h"
#include "QDebug"
#include "ui_switchcontrol.h"
#include <QCryptographicHash>

SwitchControl::SwitchControl(QWidget *parent)
  : QMainWindow(parent), _ui(new Ui::SwitchControl), _tweakPage(new TweakPage(this)), _faqPage(new FaqPage(this))
{
  _ui->setupUi(this);
  _tweakPage->hide();
  _faqPage->hide();
  connect(_ui->btnGoLogin, &QPushButton::clicked, this, &SwitchControl::tryLogin);
}
SwitchControl::~SwitchControl()
{
  delete _tweakPage;
  delete _faqPage;
  delete _ui;
}

void SwitchControl::tryLogin()
{
  if (isLoginPasswordCorrect()) {
    _ui->tabWidget->removeTab(0);
    _ui->tabWidget->addTab(_tweakPage, "Tweak Page");
    _ui->tabWidget->addTab(_faqPage, "FAQ Page");
    _tweakPage->show();
    _faqPage->show();
    _ui->tabWidget->setCurrentIndex(0);
  } else {
    qDebug() << "incorrect login or password";
  }
}

bool SwitchControl::isLoginPasswordCorrect()
{
  LoginPasswod loginPassword {
    _ui->leLogin->text(),
    QString(QCryptographicHash::hash(_ui->lePassword->text().toUtf8(), QCryptographicHash::Sha256).toHex())
  };
  qDebug() << "Сurrent password hash: " <<  loginPassword.passwordHash;
  return loginPassword == SwitchDataMapper::instance().getLoginAndPassword();
}

