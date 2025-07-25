#include "flashwidget.h"
#include "ui_flashwidget.h"

FlashWidget::FlashWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlashWidget)
{
    ui->setupUi(this);
{
}
}

FlashWidget::~FlashWidget()
{
    delete ui;
}
