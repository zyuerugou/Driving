/* *
 * Class:   LaneDrive
 *          车道级小车运行显示
 * date:    2018/9/5
 * */


#ifndef LANEDRIVE_H
#define LANEDRIVE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>

#include "head.h"

class LaneDrive : public QWidget
{
    Q_OBJECT

public:
    LaneDrive(QWidget *parent = 0);
    ~LaneDrive();

    /* *
     * function:    设置Control按钮是否可用
     * parameter:
     *      start:  开始按钮是否可用
     *      pause:  暂停按钮是否可用
     *      stop:   停止按钮是否可用
     *      reset:  重置按钮是否可用
     * date:        2018/9/10
     * */
    void setCtrlBtn(bool start, bool pause, bool stop, bool reset);

    /* *
     * function:    设置LaneMap
     * return:      -1则为失败
     * parameter:
     *      map:    地图2维布局
     * date:        2018/9/8
     * */
    int setLaneMap(float map[totalTime][stateNum]);

    /* *
     * function:    获取count
     * return:      count
     * date:        2018/9/9
     * */
    int getCount();

    /* *
     * function:    获取Q-Learning需要的迭代次数、伽马、探索概率
     * parameter:
     *      eposideNum: 迭代次数
     *      gamma:      伽马
     *      e:          探索概率
     * date:        2018/9/10
     * */
    void getQlArgs(int& eposideNum, float& gamma, float& e);

signals:
    /* *
     * function:    定时器开始信号
     * date:        2018/9/9
     * */
    void timerStartSig();

    /* *
     * function:    获取新状态信号
     * date:        2018/9/9
     * */
    void getNextStateSig(int);

public slots:

    /* *
     * function:    定时器槽，更新offset，重绘窗口
     * date:        2018/9/5
     * */
    int timerSlot();

    /* *
     * function:    更新carPos槽
     * return:      计数count，即time
     * parameter:
     *      state:          新的carPos
     *      totalR:         累计的R值
     *      currentActR:    当前状态ActR
     *      currentActQ:    当前状态ActQ
     * date:    2018/9/11
     * */
    int changeCarPos(int state, float totalR, float* currentActR, float* currentActQ);

    /* *
     * function:    车道级导航结束槽，结束定时
     * date:        2018/9/9
     * */
    void laneDriveDoneSlot();

    /* *
     * function:    重置 count, carPos, offset, goldi, obstaclei
     * return:      -1则为失败
     * date:        2018/9/9
     * */
    int resetSlot();

    /* *
     * function:    滑块值改变，修改定时器步长
     * parameter:
     *      value:  滑块值
     * date:        2018/9/10
     * */
    void ctrlTimerSldValueChangedSLot(int value);

    /* *
     * function:    按下开始按钮，开始定时器
     * date:        2018/9/10
     * */
    void ctrlStartBtnClickedSlot();

    /* *
     * function:    按下暂停按钮，停止定时器
     * date:        2018/9/10
     * */
    void ctrlPauseBtnClickedSlot();

    /* *
     * function:    按下结束按钮，停止定时器
     * date:        2018/9/10
     * */
    void ctrlStopBtnClickedSlot();

    /* *
     * function:    按下重置按钮，重置状态
     * date:        2018/9/10
     * */
    void ctrlResetBtnClickedSlot();

protected:

    /* *
     * function:    重绘函数
     * date:
     *      绘制背景及小车:            2018/9/5
     *      优化多余的左边不显示的图片:  2018/9/7
     *      绘制gold及obstacle:       2018/9/8
     *      重写碰撞:                 2018/9/9
     * */
    void paintEvent(QPaintEvent* event);

    /* *
     * function:    测试像素位置
     * date:        2018/9/5
     * */
    void mousePressEvent(QMouseEvent* event);

private:

    //road图片
    QPixmap roadImg;
    //back图片
    QPixmap backImg[3];
    //car图片
    QPixmap carImg;
    //gold图片
    QPixmap goldImg;
    //obstacle图片
    QPixmap obstacleImg;

    //reward
    QLabel* rewTotalLbl;
    QLabel* rewLeftLbl;
    QLabel* rewStraightLbl;
    QLabel* rewRightLbl;
    QGroupBox* rewGbx;

    //QValue
    QLabel* qVLeftLbl;
    QLabel* qVStraightLbl;
    QLabel* qVRightLbl;
    QGroupBox* qVGbx;

    //Control
    QLabel* ctrlSpeedLbl;
    QSlider* ctrlTimerSld;
    QPushButton* ctrlStartBtn;
    QPushButton* ctrlStopBtn;
    QPushButton* ctrlPauseBtn;
    QPushButton* ctrlResetBtn;
    QGroupBox* ctrlGbx;
    QLabel* ctrlEposideNumLbl;
    QLineEdit* ctrlEposideNumEdt;
    QLabel* ctrlGammaLbl;
    QLineEdit* ctrlGammaEdt;
    QLabel* ctrlEGreedyLbl;
    QLineEdit* ctrlEGreedyEdt;

    //定时器
    QTimer timer;
    //定时器步长
    int timeStep;
    //定时器计数（用于改变小车状态）
    int timerCount;

    //图片偏移
    int offset;

    /* *
     * 小车位置状态
     * 0:   lane0
     * 1:   lane1
     * 2:   lane2
     * */
    int carPos;
    //gold位置序列
    QVector<int> goldPos;
    //obstacle位置序列
    QVector<int> obstaclePos;
    //优化已经访问过的gold
    int goldi;
    //优化已经访问过的obstacle
    int obstaclei;

    //计数用，即time
    int count;

};

#endif // LANEDRIVE_H
