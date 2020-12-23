#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
  class LoginPage;
}

class LoginPage : public QWidget
{
  Q_OBJECT

public:
  explicit LoginPage(QWidget *parent = nullptr);
  ~LoginPage();

signals:
  void loginSuccsess();

private:
  void tryLogin();
  bool isLoginPasswordCorrect();
  Ui::LoginPage *_ui;
};

#endif // LOGINPAGE_H
