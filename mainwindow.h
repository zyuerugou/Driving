/* *
 * Class:   MainWindow
 *          顶级容器
 * date:    2018/9/8
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTabWidget>
#include <QVector>
#include <QIcon>

#include "lanedrive.h"
#include "qlearning.h"
#include "mapdrive.h"
#include "homepage.h"
#include "head.h"

class MainWindow : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:
    /* *
     * function:    获取动作序列成功信号
     * date:        2018/9/9
     * */
    void getActionSig();

    /* *
     * function:    改变小车状态信号
     * parameter:
     *      state:          新状态
     *      totalR:         累计R值
     *      currentActR:    当前状态的ActR
     *      currentActQ:    当前状态的ActQ
     * date:        2018/9/11
     * */
    void changeCarStateSig(int, float, float*, float*);

    /* *
     * function:    车道级导航结束信号
     * date:        2018/9/9
     * */
    void laneDriveDoneSig();

public slots:

    /* *
     * function:    读取LaneMap
     * return:      -1则为失败
     * parameter:
     *      addr:   文件路径
     * date:        2018/9/8
     * */
    int readLaneMapSlot(QString addr);

    /* *
     * function:    q-learning之后获取动作序列
     * return:      -1则为失败
     * date:        2018/9/11
     * */
    int getActionSlot();

    /* *
     * function:    获取新状态槽
     * return:      -1则为失败
     * parameter:
     *      time:   时刻
     * date:        2018/9/9
     * */
    int driveSlot(int time);

private:
    //窗体Icon
    QIcon* windowIcon;

    //首页窗口
    HomePage* homePage;

    //全局级小车运行显示的窗口
    MapDrive* mapDrive;

    //车道级小车运行显示的窗口
    LaneDrive* laneDrive;

    //Q-Learning
    QLearning* qLearning;

    //Q-Learning Action序列
    QVector<int> action;
    int actionSize;

    //laneMap
    float laneMap[totalTime][stateNum];


};

#endif // MAINWINDOW_H
