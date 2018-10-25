#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QTabWidget(parent)
{
    //初始化mapDrive
    mapDrive = new MapDrive(this);

    //初始化laneDrive
    laneDrive = new LaneDrive(this);

    //初始化homePage
    homePage = new HomePage(this);

    //初始化qLearning
    qLearning = new QLearning;

    //初始化action
    action.clear();
    actionSize = 0;

    //设置Icon
    windowIcon = new QIcon(":/images/car.png");
    this->setWindowIcon(*windowIcon);

    //设置窗体名
    this->setWindowTitle(tr("智慧交通系统"));

    //添加标签页面
    this->addTab(homePage, tr("首页"));
    this->addTab(mapDrive, tr("全局级"));
    this->addTab(laneDrive, tr("车道级"));

    //将tabBar放到左边
    this->setTabPosition(QTabWidget::West);
    //设置size
    this->setFixedSize(windowWidth, windowHeight);

    //读取laneMap
    this->readLaneMapSlot(":/data/lanemap.txt");
    //设置laneDrive的laneMap
    laneDrive->setLaneMap(this->laneMap);


    connect(this,
            SIGNAL(changeCarStateSig(int, float, float*, float*)),
            laneDrive,
            SLOT(changeCarPos(int, float, float*, float*)));

    connect(laneDrive,
            SIGNAL(timerStartSig()),
            this,
            SLOT(getActionSlot()),
            Qt::DirectConnection);

    connect(laneDrive,
            SIGNAL(getNextStateSig(int)),
            this,
            SLOT(driveSlot(int)));

    connect(this,
            SIGNAL(laneDriveDoneSig()),
            laneDrive,
            SLOT(laneDriveDoneSlot()));

    //设置qLearning的R矩阵
    qLearning->setR(this->laneMap);
}


/* *
 * function:    读取LaneMap
 * return:      -1则为失败
 * parameter:
 *      addr:   文件路径
 * date:        2018/9/8
 * */
int MainWindow::readLaneMapSlot(QString addr)
{
    assert(addr != "");

    QFile file(addr);
    //以只读方式打开文件失败
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<tr("文件打开失败");
        return -1;
    }

    //读取数据
    QTextStream textR(&file);

    int size = 0;
    textR>>size;

    QString tmp = "";
    for (int t = 0; t < size; t++)
    {
        for (int i = 0; i < stateNum; i++)
        {
            textR>>tmp;

            //异常处理
            if (tmp == "")
            {
                if (i != 0)
                {
                    qDebug()<<"Error: Read error";
                    return -1;
                }
            }

            //赋值给laneMap
            switch (tmp.toInt())
            {
            case -1://障碍
                this->laneMap[t][i] = (float)noWay;
                break;
            case 0://通行
                this->laneMap[t][i] = (float)goodWay;
                break;
            case 1://奖励
                this->laneMap[t][i] = (float)bestWay;
                break;
            default:
                this->laneMap[t][i] = (float)goodWay;
            }
        }
    }

    qDebug()<<"Read data successfully";

    return 0;
}


/* *
 * function:    q-learning之后获取动作序列
 * return:      -1则为失败
 * date:        2018/9/11
 * */
int MainWindow::getActionSlot()
{
    int eposideNum = 0;
    float gamma = 0.0f;
    float e = 0.0f;

    //获取qLearning的参数
    this->laneDrive->getQlArgs(eposideNum, gamma, e);

    //初始化qLearning的R/Q/totalR
    this->qLearning->initRQ();

    //qLearning的学习
    this->qLearning->learning(eposideNum, gamma , e);

    //初始化路径
    this->action.clear();

    //获取路径
    this->action = this->qLearning->chooseAction(1);

    //路径长度
    this->actionSize = this->action.size();

    qDebug()<<this->actionSize;

    //异常处理
    if (this->action.isEmpty())
    {
        return -1;
    }


 //   emit this->getActionSig();


    return 0;
}


/* *
 * function:    获取新状态槽
 * return:      -1则为失败
 * parameter:
 *      time:   时刻
 * date:        2018/9/9
 * */
int MainWindow::driveSlot(int time)
{
    //到达终点
    if (time == actionSize - 1)
    {
        qDebug()<<"arrived";
        QMessageBox::information(this, tr("车道级"), tr("小车到达终点"));

        emit this->laneDriveDoneSig();

        return 0;
    }

    //获取新状态
    int state = this->action[time];
    //获取累计R值
    float totalR = this->qLearning->getTotalR(time);
    //获取currentActR
    float* currentActR = this->qLearning->getCurrentActR(time + 1, state);
    //获取currentActQ
    float* currentActQ = this->qLearning->getCurrentActQ(time + 1, state);

    //发送信号
    emit this->changeCarStateSig(state, totalR, currentActR, currentActQ);

    return 0;
}
