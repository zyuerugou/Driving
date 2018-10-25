#include <QPainter>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QValidator>

#include "lanedrive.h"


//const int otherWidth = 40;
//const int otherHeight = 40;
const int laneX = 0;            //laneX
const int laneY[3] = {          //laneY
  127,      //lane0
  200,      //lane1
  265       //lane2
};
const int driveStep = 20;       //绘制时像素更新
const int step = 100;           //地图分块
const int ctrlTimeSldStep = 100; //Slider步长

LaneDrive::LaneDrive(QWidget *parent)
    : QWidget(parent)
{

    //初始化count
    this->count = 0;

    //初始化offset
    this->offset = 0;

    //初始化goldi
    this->goldi = 0;

    //初始化obstaclei
    this->obstaclei = 0;

    //初始化carPos
    this->carPos = 1;

    //初始化timerCount
    this->timerCount = 0;

    //初始化goldPos
    this->goldPos.clear();

    //初始化obstaclePos
    this->obstaclePos.clear();

    //初始化timerStep
    this->timeStep = 100;

    //获取road图片
    this->roadImg.load(":/images/road.jpg");
    qDebug()<<"road size: "<<this->roadImg.width()<<", "<<this->roadImg.height();

    //获取背景图片
    this->backImg[0].load(":/images/oback.jpg");
    qDebug()<<"back size: "<<this->backImg[0].width()<<", "<<this->backImg[0].height();
    this->backImg[1].load(":/images/dback.jpg");
    qDebug()<<"back size: "<<this->backImg[1].width()<<", "<<this->backImg[1].height();
    this->backImg[2].load(":/images/btnback.jpg");
    qDebug()<<"back size: "<<this->backImg[2].width()<<", "<<this->backImg[2].height();

    //获取car图片
    this->carImg.load(":/images/car.png");
    qDebug()<<"car size: "<<this->carImg.width()<<", "<<this->carImg.height();

    //获取gold图片
    this->goldImg.load(":/images/gold.png");
    qDebug()<<"gold size: "<<this->goldImg.width()<<", "<<this->goldImg.height();

    //获取obstacle图片
    this->obstacleImg.load(":/images/obstacle.png");
    qDebug()<<"obstacle size: "<<this->obstacleImg.width()<<", "<<this->obstacleImg.height();


    //窗体布局
    //Btn样式
    this->setStyleSheet(QString(btnStyle));

    //初始化reword显示
    rewTotalLbl = new QLabel(tr("累计:\t%1").arg(0));
    rewLeftLbl = new QLabel(tr("左转:\t%1").arg(0));
    rewStraightLbl = new QLabel(tr("直行:\t%1").arg(0));
    rewRightLbl = new QLabel(tr("右转:\t%1").arg(0));
    //第一行布局
    QHBoxLayout* rewHLayout0 = new QHBoxLayout;
    rewHLayout0->addStretch();
    rewHLayout0->addWidget(rewTotalLbl);
    rewHLayout0->setMargin(5);
    //第二行布局
    QHBoxLayout* rewHLayout1 = new QHBoxLayout;
    rewHLayout1->addWidget(rewLeftLbl);
    rewHLayout1->addWidget(rewStraightLbl);
    rewHLayout1->addWidget(rewRightLbl);
    rewHLayout1->setMargin(5);
    //垂直布局
    QVBoxLayout* rewVLayout = new QVBoxLayout;
    rewVLayout->addLayout(rewHLayout0);
    rewVLayout->addLayout(rewHLayout1);
    //GroupBox布局
    rewGbx = new QGroupBox(tr("回报"));
    rewGbx->setFixedSize(rewGbxWidth, rewGbxHeight);
    rewGbx->setStyleSheet(QString(gbxStyle));
    rewGbx->setLayout(rewVLayout);

    //初始化QValue显示
    qVLeftLbl = new QLabel(tr("左转:\t%1").arg(0));
    qVStraightLbl = new QLabel(tr("直行:\t%1").arg(0));
    qVRightLbl = new QLabel(tr("右转:\t%1").arg(0));
    //水平布局
    QHBoxLayout* qVHLayout = new QHBoxLayout;
    qVHLayout->addWidget(qVLeftLbl);
    qVHLayout->addWidget(qVStraightLbl);
    qVHLayout->addWidget(qVRightLbl);
    qVHLayout->setMargin(5);
    //GroupBox布局
    qVGbx = new QGroupBox(tr("Q值"));
    qVGbx->setFixedSize(qVGbxWidth, qVGbxHeight);
    qVGbx->setStyleSheet(QString(gbxStyle));
    qVGbx->setLayout(qVHLayout);

    //初始化Control显示
    //滑块
    ctrlSpeedLbl = new QLabel(tr("速度: "));
    ctrlTimerSld = new QSlider(this);
    ctrlTimerSld->setOrientation(Qt::Horizontal);            // 水平方向
    ctrlTimerSld->setMinimum(timeMax / timeMax);             // 最小值
    ctrlTimerSld->setMaximum(timeMax / timeMin);             // 最大值
    ctrlTimerSld->setSingleStep(timeMax / ctrlTimeSldStep);  // 步长
//    ctrlTimerSld->setTickInterval(5);                      // 设置刻度间隔
    ctrlTimerSld->setTickPosition(QSlider::TicksAbove);      //刻度在上方
    ctrlTimerSld->setValue(timeMax / timeMin);
    //编辑框
    ctrlEposideNumLbl = new QLabel(tr("迭代次数: "));
    ctrlEposideNumEdt = new QLineEdit(tr("100"));
    ctrlGammaLbl = new QLabel(tr("伽马: "));
    ctrlGammaEdt = new QLineEdit(tr("0.8"));
    ctrlEGreedyLbl = new QLabel(tr("探索概率: "));
    ctrlEGreedyEdt = new QLineEdit(tr("0.1"));
    ctrlEposideNumEdt->setAlignment(Qt::AlignCenter);                       //居中
    ctrlGammaEdt->setAlignment(Qt::AlignCenter);                            //居中
    ctrlEGreedyEdt->setAlignment(Qt::AlignCenter);                          //居中
    ctrlEposideNumEdt->setValidator(new QIntValidator(ctrlEposideNumEdt));  //限制整数输入
    QDoubleValidator* gammaVldr = new QDoubleValidator(0.0, 0.99, 2, ctrlGammaEdt);
    gammaVldr->setNotation(QDoubleValidator::StandardNotation);
    ctrlGammaEdt->setValidator(gammaVldr);                                  //限制0.0 - 1.0 最多两位小数输入
    QDoubleValidator* eGreedyVldr = new QDoubleValidator(0.0, 0.99, 2, ctrlEGreedyEdt);
    eGreedyVldr->setNotation(QDoubleValidator::StandardNotation);
    ctrlEGreedyEdt->setValidator(eGreedyVldr);                             //限制0.0 - 1.0 最多两位小数输入
    //按钮
    ctrlStartBtn = new QPushButton(tr("开始"));
    ctrlPauseBtn = new QPushButton(tr("暂停"));
    ctrlStopBtn = new QPushButton(tr("结束"));
    ctrlResetBtn = new QPushButton(tr("重置"));
    //编辑框水平布局
    QHBoxLayout *ctrlEdtHLayout = new QHBoxLayout;
    ctrlEdtHLayout->addWidget(ctrlEposideNumLbl);
    ctrlEdtHLayout->addWidget(ctrlEposideNumEdt);
    ctrlEdtHLayout->addWidget(ctrlGammaLbl);
    ctrlEdtHLayout->addWidget(ctrlGammaEdt);
    ctrlEdtHLayout->addWidget(ctrlEGreedyLbl);
    ctrlEdtHLayout->addWidget(ctrlEGreedyEdt);
    //按钮水平布局
    QHBoxLayout *ctrlBtnHLayout = new QHBoxLayout;
    ctrlBtnHLayout->addWidget(ctrlStartBtn);
    ctrlBtnHLayout->addWidget(ctrlPauseBtn);
    ctrlBtnHLayout->addWidget(ctrlStopBtn);
    ctrlBtnHLayout->addWidget(ctrlResetBtn);
    ctrlBtnHLayout->setMargin(5);
    //垂直布局
    QVBoxLayout *ctrlVLayout = new QVBoxLayout;
    ctrlVLayout->addWidget(ctrlSpeedLbl);
    ctrlVLayout->addWidget(ctrlTimerSld);
    ctrlVLayout->addLayout(ctrlEdtHLayout);
    ctrlVLayout->addLayout(ctrlBtnHLayout);
    ctrlGbx = new QGroupBox(tr("控制"));
    //GroupBox布局
    ctrlGbx->setFixedSize(ctrlGbxWidth, ctrlGbxHeight);
    ctrlGbx->setStyleSheet(QString(gbxStyle));
    ctrlGbx->setLayout(ctrlVLayout);

    //全局布局
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QVBoxLayout* leftdownLayout = new QVBoxLayout;
    QHBoxLayout* downLayout = new QHBoxLayout;
    //左下角局部布局
    leftdownLayout->addWidget(rewGbx);
    leftdownLayout->addWidget(qVGbx);
    //下方局部布局
    downLayout->addLayout(leftdownLayout);
    downLayout->addWidget(ctrlGbx);
    //全局布局
    QSpacerItem *spaceTop = new QSpacerItem(0, obackHeight + roadHeight + dbackHeight + 20, QSizePolicy::Minimum,QSizePolicy::Minimum);
    mainLayout->addSpacerItem(spaceTop);
    mainLayout->addLayout(downLayout);

    //设置窗体大小
    this->setFixedSize(windowWidth, windowHeight);
    qDebug()<<"window size: "<<windowWidth<<", "<<windowHeight;

    //设置窗体布局
    this->setLayout(mainLayout);

    //开启开始按钮，关闭暂停、结束、重置按钮
    this->setCtrlBtn(true, false, false, false);


    connect(&(this->timer),
            SIGNAL(timeout()),
            this,
            SLOT(timerSlot()));

    connect(this->ctrlStartBtn,
            SIGNAL(clicked()),
            this,
            SLOT(ctrlStartBtnClickedSlot()));

    connect(this->ctrlPauseBtn,
            SIGNAL(clicked()),
            this,
            SLOT(ctrlPauseBtnClickedSlot()));

    connect(this->ctrlStopBtn,
            SIGNAL(clicked()),
            this,
            SLOT(ctrlStopBtnClickedSlot()));

    connect(this->ctrlResetBtn,
            SIGNAL(clicked()),
            this,
            SLOT(ctrlResetBtnClickedSlot()));

    connect(this->ctrlTimerSld,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(ctrlTimerSldValueChangedSLot(int)));

}

LaneDrive::~LaneDrive()
{

}


/* *
 * function:    设置Control按钮是否可用
 * parameter:
 *      start:  开始按钮是否可用
 *      pause:  暂停按钮是否可用
 *      stop:   停止按钮是否可用
 *      reset:  重置按钮是否可用
 * date:        2018/9/10
 * */
void LaneDrive::setCtrlBtn(bool start, bool pause, bool stop, bool reset)
{
    this->ctrlStartBtn->setEnabled(start);
    this->ctrlPauseBtn->setEnabled(pause);
    this->ctrlStopBtn->setEnabled(stop);
    this->ctrlResetBtn->setEnabled(reset);
}


/* *
 * function:    设置LaneMap
 * return:      -1则为失败
 * parameter:
 *      map:    地图2维布局
 * date:        2018/9/8
 * */
int LaneDrive::setLaneMap(float map[totalTime][stateNum])
{
    //初始化
    this->obstaclePos.clear();
    this->goldPos.clear();
    //搜索
    for (int i = 0; i < totalTime; i++)
    {
        for (int j = 0; j < stateNum; j++)
        {
            //障碍
            if (map[i][j] == (float)noWay)
            {
                this->obstaclePos.append(i);
                this->obstaclePos.append(j);
            }
            //奖励
            if (map[i][j] == (float)bestWay)
            {
                this->goldPos.append(i);
                this->goldPos.append(j);
            }
        }
    }

    return 0;
}


/* *
 * function:    获取count
 * return:      count
 * date:        2018/9/9
 * */
int LaneDrive::getCount()
{
    return this->count;
}


/* *
 * function:    获取Q-Learning需要的迭代次数、伽马、探索概率
 * parameter:
 *      eposideNum: 迭代次数
 *      gamma:      伽马
 *      e:          探索概率
 * date:        2018/9/10
 * */
void LaneDrive::getQlArgs(int &eposideNum, float &gamma, float &e)
{
    eposideNum = this->ctrlEposideNumEdt->text().toInt();
    gamma = this->ctrlGammaEdt->text().toFloat();
    e = this->ctrlEGreedyEdt->text().toFloat();
}


/* *
 * function:    定时器槽，更新offset，重绘窗口
 * date:        2018/9/8
 * */
int LaneDrive::timerSlot()
{

    //获取新状态
    if (this->timerCount % (step / driveStep) == 1)
    {
        emit this->getNextStateSig(this->count);
    }

    this->offset -= driveStep;

    this->timerCount++;

    this->update();

    return 0;
}


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
int LaneDrive::changeCarPos(int state, float totalR, float* currentActR, float* currentActQ)
{
    assert(state >= 0 && state < stateNum);

    this->count++;

    //更新carPos
    this->carPos = state;

    //更新totalR
    this->rewTotalLbl->setText(tr("累计:\t%1").arg(totalR));

    //更新currentActR
    this->rewLeftLbl->setText(tr("左转:\t%1").arg(*(currentActR)));
    this->rewStraightLbl->setText(tr("直行:\t%1").arg(*(currentActR + 1)));
    this->rewRightLbl->setText(tr("右转:\t%1").arg(*(currentActR + 2)));

    delete currentActR;

    //更新currentActQ
    this->qVLeftLbl->setText(tr("左转:\t%1").arg(*(currentActQ)));
    this->qVStraightLbl->setText(tr("直行:\t%1").arg(*(currentActQ + 1)));
    this->qVRightLbl->setText(tr("右转:\t%1").arg(*(currentActQ + 2)));

    delete currentActQ;

    qDebug()<<QString("state %1: ").arg(this->count)<<this->carPos;

    return count;
}


/* *
 * function:    车道级导航结束槽，结束定时
 * date:        2018/9/9
 * */
void LaneDrive::laneDriveDoneSlot()
{
    this->timer.stop();

    //开启重置按钮，关闭开始、暂停、结束按钮
    this->setCtrlBtn(false, false, false, true);
}


/* *
 * function:    重绘函数
 * date:
 *      绘制背景及小车:            2018/9/5
 *      优化多余的左边不显示的图片:  2018/9/7
 *      绘制gold及obstacle:       2018/9/8
 *      重写碰撞:                 2018/9/9
 * */
void LaneDrive::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制road
    for (int i = (-offset) / roadWidth * roadWidth; i + offset < roadWidth; i += roadWidth)
    {
        painter.drawPixmap(i + offset, obackHeight,
                           roadImg);
    }

    //绘制back
    for (int i = (-offset) / obackWidth * obackWidth; i + offset < roadWidth; i += obackWidth)
    {
        painter.drawPixmap(i + offset, 0,
                           backImg[0]);
    }
    for (int i = (-offset) / dbackWidth * dbackWidth; i + offset < roadWidth; i += dbackWidth)
    {
        painter.drawPixmap(i + offset, obackHeight + roadHeight,
                           backImg[1]);
    }
    painter.drawPixmap(0, obackHeight + roadHeight + dbackHeight,
                       windowWidth, windowHeight - (obackHeight + roadHeight + dbackHeight),
                       backImg[2]);

    //绘制gold
    if (!goldPos.isEmpty())
    {        
        int size = goldPos.size();

        //搜索第一个在界面内的gold
        for (; goldi < size; goldi += 2)
        {
            if (goldPos[goldi] * step + offset > driveStep + laneX - carWidth)
            {
                break;
            }
        }

        //结束
        if (goldi >= size)
        {
            qDebug()<<"gold: lane is compeleted";
        }
        else    //绘图
        {
            for (int i = goldi; i < size; i += 2)
            {
                //超出界面范围
                if (goldPos[i] * step + offset >= roadWidth)
                {
                    break;
                }
                //处理碰撞问题
                if (goldPos[i] * step + offset < laneX + carWidth - driveStep * 4 / 3 && goldPos[i + 1] == carPos)
                {
                    continue;
                }
                painter.drawPixmap(goldPos[i] * step + offset, laneY[goldPos[i + 1]],
                                carWidth, carHeight,
                                goldImg);
            }
        }

    }
    else
    {
        qDebug()<<"goldPos is empty";
    }


    //绘制obstacle
    if (!obstaclePos.isEmpty())
    {
        int size = obstaclePos.size();

        //搜索第一个在界面内的obstacle
        for (; obstaclei < size; obstaclei += 2)
        {
            if (obstaclePos[obstaclei] * step + offset > driveStep + laneX - carWidth)
            {
                break;
            }
        }

        //结束
        if (obstaclei >= size)
        {
            qDebug()<<"obstacle: lane is compeleted";
        }
        else    //绘图
        {
            for (int i = obstaclei; i < size; i += 2)
            {
                //超出界面范围
                if (obstaclePos[i] * step + offset >= roadWidth)
                {
                    break;
                }
                //处理碰撞问题
                if (obstaclePos[i] * step + offset < laneX + carWidth - driveStep * 4 / 3 && obstaclePos[i + 1] == carPos)
                {
                    continue;
                }
                painter.drawPixmap(obstaclePos[i] * step + offset, laneY[obstaclePos[i + 1]],
                                carWidth, carHeight,
                                obstacleImg);
            }
        }

    }
    else
    {
        qDebug()<<"obstaclePos is empty";
    }


    //绘制car
    painter.drawPixmap(laneX, laneY[carPos],
                       carWidth, carHeight,
                       carImg);

}


/* *
 * function:    测试像素位置
 *              开始定时器
 * date:        2018/9/8
 * */
void LaneDrive::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse point: "<<event->pos().x() - carWidth / 2<<", "<<event->pos().y() - carHeight / 2;
}


/* *
 * function:    重置 count, carPos, offset, goldi, obstaclei, timerCount
 * return:      -1则为失败
 * date:        2018/9/9
 * */
int LaneDrive::resetSlot()
{
    this->count = 0;
    this->carPos = 1;
    this->offset = 0;
    this->goldi = 0;
    this->obstaclei = 0;
    this->timerCount = 0;

    this->update();

    return 0;
}


/* *
 * function:    滑块值改变，修改定时器步长
 * parameter:
 *      value:  滑块值
 * date:        2018/9/10
 * */
void LaneDrive::ctrlTimerSldValueChangedSLot(int value)
{
    this->timeStep = timeMax / value;

    //处理运行过程中的情况
    if (this->timer.isActive())
    {
        this->timer.stop();
        this->timer.start(this->timeStep);
    }
}


/* *
 * function:    按下开始按钮，开始定时器
 * date:        2018/9/10
 * */
void LaneDrive::ctrlStartBtnClickedSlot()
{
    assert(!this->timer.isActive());

    //结束后需重新Q-learning
    if (this->offset == 0)
    {
        //发送信号给MainWindow::driveSlot()
        emit this->timerStartSig();
    }

    //开始定时器
    qDebug()<<"timer start";
    timer.start(timeStep);

    //关闭开始、重置按钮，开启暂停、结束按钮
    this->setCtrlBtn(false, true, true, false);
}


/* *
 * function:    按下暂停按钮，停止定时器
 * date:        2018/9/10
 * */
void LaneDrive::ctrlPauseBtnClickedSlot()
{
    assert(this->timer.isActive());

    //停止定时器
    timer.stop();

    //开启开始、结束、重置按钮
    this->setCtrlBtn(true, false, true, true);
}


/* *
 * function:    按下结束按钮，停止定时器
 * date:        2018/9/10
 * */
void LaneDrive::ctrlStopBtnClickedSlot()
{
    //停止定时器
    timer.stop();

    //开启重置按钮，关闭开始、暂停、结束按钮
    this->setCtrlBtn(false, false, false, true);
}


/* *
 * function:    按下重置按钮，重置状态
 * date:        2018/9/10
 * */
void LaneDrive::ctrlResetBtnClickedSlot()
{
    assert(!this->timer.isActive());

    //重置 count, carPos, offset, goldi, obstaclei
    this->resetSlot();

    //开启开始按钮，关闭暂停、结束、重置按钮
    this->setCtrlBtn(true, false, false, false);
}


