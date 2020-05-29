#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QObject>

class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QWidget *parent = 0);

    void mouseDoubleClickEvent(QMouseEvent *ev);

signals:
    void Mouse_Double_Pressed();

public slots:

};

#endif // MY_QLABEL_H
