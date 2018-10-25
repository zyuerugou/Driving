#include "homepage.h"

#include <QPainter>

HomePage::HomePage(QWidget *parent) : QWidget(parent)
{
    backImg.load(":/images/homepage.jpg");

}


/* *
 * function:    重绘界面
 * date:        2018/9/12
 * */
void HomePage::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0,
                       backImg);
}


