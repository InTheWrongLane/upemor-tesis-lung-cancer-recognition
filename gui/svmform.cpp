#include "svmform.h"
#include "ui_svmform.h"

SVMForm::SVMForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SVMForm)
{
    ui->setupUi(this);
}

SVMForm::~SVMForm()
{
    delete ui;
}
