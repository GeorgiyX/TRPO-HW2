#ifndef TWEAKPAGE_H
#define TWEAKPAGE_H

#include <QWidget>
#include <QListWidget>
#include "businesslogic.h"

namespace Ui {
  class TweakPage;
}

class TweakPage : public QWidget
{
  Q_OBJECT

public:
  explicit TweakPage(QWidget *parent = nullptr);
  ~TweakPage();

private slots:
  /** @brief переключаемся в режим обновления/удаления записи */
  void onIpClicked(QListWidgetItem *item);
  void onUpdateIpBtnClicked();

private:
  void setUpIpList();
  void setUpConfig();
  void reloadIpList();
  /** @brief переключаемся в режим добавления записи */
  void goAddMode();

  Ui::TweakPage *_ui;
  QMap<QListWidgetItem *, IpAddress> _ipMap;
  bool _isBtnUpdateInAddMode;
  IpAddress _currentEditIp;
};

#endif // TWEAKPAGE_H
