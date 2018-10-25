/* *
 * Class:   HomePage
 *          首页
 * date:    2018/9/11
 * */

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* e);

private:

    //背景图片
    QPixmap backImg;
};

#endif // HOMEPAGE_H
