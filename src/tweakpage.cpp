#include "tweakpage.h"
#include "switchdatamapper.h"
#include "ui_tweakpage.h"

const char *ADD_TEXT = "Добавить";
const char *UPDATE_TEXT = "Обновить";
const char *FAILURE_MODE = "Симуляция обрыва";
const char *HUB_MODE = "Режим хаба";
const char *NORMAL_MODE = "Режим свича";


TweakPage::TweakPage(QWidget *parent) :
  QWidget(parent),
  _ui(new Ui::TweakPage), _ipMap(), _isBtnUpdateInAddMode(true)
{
  _ui->setupUi(this);

  setUpIpList();
  setUpConfig();
}

TweakPage::~TweakPage()
{
  delete _ui;
}

void TweakPage::setUpIpList()
{
  connect(_ui->btnUpdateIp, &QCommandLinkButton::clicked, this, &TweakPage::onUpdateIpBtnClicked);
  connect(_ui->ipListWidget, &QListWidget::itemClicked, this, &TweakPage::onIpClicked);
  connect(_ui->lineEdit, &QLineEdit::textEdited, [this](const QString &text){
    if (!_isBtnUpdateInAddMode && (text == "...")) { goAddMode(); }
  });
  connect(_ui->btnDeleteIp, &QCommandLinkButton::clicked, [this](){
    SwitchDataMapper::instance().deleteAddress(_currentEditIp);
    goAddMode();
    reloadIpList();
  });
  reloadIpList();
  goAddMode();
}

void TweakPage::setUpConfig()
{
  _ui->cbWorkMode->addItems(QStringList() << FAILURE_MODE << NORMAL_MODE << HUB_MODE);
  auto config = SwitchDataMapper::instance().getConfig();
  _ui->sbSpecByte->setValue(config.specByte);
  _ui->sbSpecIface->setValue(config.specIface);
  _ui->cbWorkMode->setCurrentIndex(config.workMode);
  _ui->cbIpFilter->setChecked(config.isIpFilterEnable);

  connect(_ui->btnUpdateConfig, &QCommandLinkButton::clicked, [this](){
    SwitchDataMapper::instance().updateConfig({
                                                static_cast<size_t>(_ui->cbWorkMode->currentIndex()),
                                                _ui->cbIpFilter->isChecked(),
                                                static_cast<size_t>(_ui->sbSpecIface->value()),
                                                static_cast<size_t>(_ui->sbSpecByte->value())
                                              });
  });
}

void TweakPage::reloadIpList()
{
  _ui->ipListWidget->clear();
  _ipMap.clear();
  auto ipList = SwitchDataMapper::instance().getAllAddresses();
  for(auto &ip : ipList) {
    /*Qt позаботится об удалении QListWidgetItem*/
    _ipMap[new QListWidgetItem(ip.address, _ui->ipListWidget)] = ip;
  }
}

void TweakPage::goAddMode()
{
  _ui->btnDeleteIp->hide();
  _ui->btnUpdateIp->setText(ADD_TEXT);
  _isBtnUpdateInAddMode = true;
  _ui->lineEdit->clear();
}

void TweakPage::onIpClicked(QListWidgetItem *item)
{
  _currentEditIp = _ipMap[item];
  _ui->btnDeleteIp->show();
  _ui->lineEdit->setText(_currentEditIp.address);
  _ui->btnUpdateIp->setText(UPDATE_TEXT);
  _isBtnUpdateInAddMode = false;
}

void TweakPage::onUpdateIpBtnClicked()
{
  _isBtnUpdateInAddMode ? SwitchDataMapper::instance().addNewAddress({0, _ui->lineEdit->text()})
                        : SwitchDataMapper::instance().updateAddress({_currentEditIp.id, _ui->lineEdit->text()});
  goAddMode();
  reloadIpList();
}
