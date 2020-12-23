#ifndef SWITCHCONTROL_H
#define SWITCHCONTROL_H

#include <QMainWindow>
#include "tweakpage.h"
#include "faqpage.h"
#include "loginpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SwitchControl; }
QT_END_NAMESPACE

class SwitchControl : public QMainWindow
{
  Q_OBJECT

public:
  SwitchControl(QWidget *parent = nullptr);
  ~SwitchControl();

public slots:
  void onLoginSuccsess();

private:
  Ui::SwitchControl *_ui;
  TweakPage *_tweakPage;
  FaqPage *_faqPage;
  LoginPage *_loginPage;
};
#endif // SWITCHCONTROL_H
