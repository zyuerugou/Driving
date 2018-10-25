/* *
 * Class:   MapDrive
 *          全局地图小车运行显示
 * date:    2018/9/9
 * */


#ifndef MAPDRIVE_H
#define MAPDRIVE_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QTimer>

#include "routeplanning.h"


class MapDrive : public QWidget
{
    Q_OBJECT
public:
    explicit MapDrive(QWidget *parent = 0);

    /* *
     * function:    重置 carPos, pathQpos
     * date:        2018/9/11
     * */
    void reset();

    /* *
     * function:    设置Control按钮是否可用
     * parameter:
     *      start:  开始按钮是否可用
     *      pause:  暂停按钮是否可用
     *      stop:   停止按钮是否可用
     *      reset:  重置按钮是否可用
     * date:        2018/9/11
     * */
    void setCtrlBtn(bool start, bool pause, bool stop, bool reset);

    /* *
     * function:    路径规划
     * return:      -1则为失败
     * date:        1018/9/11
     * */
    int routePlanFun();

    /* *
     * function:    读取mapDrive的地图
     * return:      -1则为失败
     * date:        2018/9/11
     * */
    int readMap();

protected:

    /* *
     * function:    重绘地图
     * date:        2018/9/11
     * */
    void paintEvent(QPaintEvent* e);

    /* *
     * function:    通过鼠标按下，按顺序进行映射
     * paramter:
     *      event:  获取鼠标状态
     * date:        2018/9/10
     * */
    void mousePressEvent(QMouseEvent* e);

signals:

public slots:

    /* *
     * function:    定时器槽
     * date:        2018/9/11
     * */
    void timeSlot();

    /* *
     * function:    按下开始按钮，计算路径或者继续开车，开启定时器
     * return:      -1则为失败
     * date:        2018/9/11
     * */
    int ctrlStartBtnClickedSlot();

    /* *
     * function:    按下暂停按钮，停止定时器
     * date:        2018/9/11
     * */
    void ctrlPauseBtnClickedSlot();

    /* *
     * function:    按下结束按钮，停止定时器
     * date:        2018/9/11
     * */
    void ctrlStopBtnClickedSlot();

    /* *
     * function:    按下重置按钮，重置状态
     * date:        2018/9/11
     * */
    void ctrlResetBtnClickedSlot();

private:
    //地图图片
    QPixmap mapImg;
    //小车图片
    QPixmap carImg;
    //背景图片
    QPixmap backImg;

    //小车的位置
    int carPos;
    QPoint carQpos;

    //地图结点映射
    int nodePos[max_vertexes][2];

    //路径规划类
    routePlanning* routePlan;

    //路径
    int path[max_vertexes];
    QVector<QPoint*> pathQpos;
    //路径速度
    float speed[max_vertexes];

    //起点、终点
    QLabel* beginLbl;
    QComboBox* beginCbx;
    QLabel* endLbl;
    QComboBox* endCbx;
    QGroupBox* beGbx;

    //路径规划算法选择
    QComboBox* algthmCbx;
    QGroupBox* algthmGbx;

    //控制按钮
    QPushButton* ctrlStartBtn;
    QPushButton* ctrlStopBtn;
    QPushButton* ctrlPauseBtn;
    QPushButton* ctrlResetBtn;
    QGroupBox* ctrlGbx;

    //定时器
    QTimer timer;
};

#endif // MAPDRIVE_H
