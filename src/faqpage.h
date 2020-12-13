#ifndef FAQ_H
#define FAQ_H

#include <QWidget>

namespace Ui {
  class faq;
}

class FaqPage : public QWidget
{
  Q_OBJECT

public:
  explicit FaqPage(QWidget *parent = nullptr);
  ~FaqPage();

private:
  Ui::faq *ui;
};

#endif // FAQ_H
