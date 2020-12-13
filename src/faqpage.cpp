#include "faqpage.h"
#include "ui_faqpage.h"

FaqPage::FaqPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::faq)
{
  ui->setupUi(this);
}

FaqPage::~FaqPage()
{
  delete ui;
}
