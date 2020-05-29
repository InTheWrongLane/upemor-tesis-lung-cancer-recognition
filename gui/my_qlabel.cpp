#include <gui/my_qlabel.h>
#include <iostream>


my_qlabel::my_qlabel(QWidget *parent):QLabel(parent)
{

}

void my_qlabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    emit Mouse_Double_Pressed();
}
