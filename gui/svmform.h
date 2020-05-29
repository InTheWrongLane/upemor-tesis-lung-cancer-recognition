#ifndef SVMFORM_H
#define SVMFORM_H

#include <QDialog>

namespace Ui {
class SVMForm;
}

class SVMForm : public QDialog
{
    Q_OBJECT

public:
    explicit SVMForm(QWidget *parent = 0);
    ~SVMForm();

private:
    Ui::SVMForm *ui;
};

#endif // SVMFORM_H
