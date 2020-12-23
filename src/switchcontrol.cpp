#include "switchcontrol.h"
#include "switchdatamapper.h"
#include "QDebug"
#include "ui_switchcontrol.h"
#include <QCryptographicHash>

SwitchControl::SwitchControl(QWidget *parent)
  : QMainWindow(parent), _ui(new Ui::SwitchControl), _tweakPage(new TweakPage(this)), _faqPage(new FaqPage(this)), _loginPage(new LoginPage(this))
{
  _ui->setupUi(this);
  _tweakPage->hide();
  _faqPage->hide();
  _ui->tabWidget->addTab(_loginPage, "Login Page");
  connect(_loginPage, &LoginPage::loginSuccsess, this, &SwitchControl::onLoginSuccsess);
}
SwitchControl::~SwitchControl()
{
  delete _loginPage;
  delete _tweakPage;
  delete _faqPage;
  delete _ui;
}

void SwitchControl::onLoginSuccsess()
{
  _ui->tabWidget->removeTab(0);
  _ui->tabWidget->addTab(_tweakPage, "Tweak Page");
  _ui->tabWidget->addTab(_faqPage, "FAQ Page");
  _tweakPage->show();
  _faqPage->show();
  _ui->tabWidget->setCurrentIndex(0);
}
