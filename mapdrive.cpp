#include "mapdrive.h"
#include "head.h"

#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFont>

const int mapWidth = 842;//569;//map宽
const int mapHeight = 653;//map高
const int gbxWidth = windowWidth - mapWidth - 50;//Gbox宽
const int pixXStep = 20;//每timeout移动的像素步长X

MapDrive::MapDrive(QWidget *parent) : QWidget(parent)
{
    //获取map图片
    mapImg.load(":/images/map.jpg");
    qDebug()<<"map size: "<<this->mapImg.width()<<", "<<this->mapImg.height();

    //获取小车图片
    carImg.load(":/images/car.png");
    qDebug()<<"car size: "<<this->carImg.width()<<", "<<this->carImg.height();

    //获取背景图片
    backImg.load(":/images/mapbtnback.jpg");
    qDebug()<<"back size: "<<this->backImg.width()<<" ,"<<this->backImg.height();


    //初始化path
    memset(path, -1, sizeof(path));
    //初始化speed
    memset(speed, 0.0f, sizeof(speed));

    //初始化小车位置
    carPos = -1;

    //读取mapDrive的地图
    this->readMap();

    //初始化routePlan
    routePlan = new routePlanning;
    //设置结点QPoint
    this->routePlan->setEuclideanmetric(this->nodePos);

    //设置按钮风格
    this->setStyleSheet(QString(btnStyle));

    //起点、终点
    beginLbl = new QLabel(tr("起点: "));
    beginCbx = new QComboBox();
    for (int i = 0; i < max_vertexes; i++)
    {
        beginCbx->addItem(tr("房子 %1").arg(i));
    }
    beginCbx->setEditable(false);
    endLbl = new QLabel(tr("终点: "));
    endCbx = new QComboBox();
    for (int i = 0; i < max_vertexes; i++)
    {
        endCbx->addItem(tr("房子 %1").arg(i));
    }
    endCbx->setEditable(false);
//    //水平布局
//    QHBoxLayout* beginHLayout = new QHBoxLayout;
//    beginHLayout->addWidget(beginLbl);
//    beginHLayout->addWidget(beginCbx);
//    QHBoxLayout* endHLayout = new QHBoxLayout;
//    endHLayout->addWidget(endLbl);
//    endHLayout->addWidget(endCbx);
    //垂直布局
    QVBoxLayout* beVLayout = new QVBoxLayout;
//    beVLayout->addLayout(beginHLayout);
//    beVLayout->addLayout(endHLayout);
    beVLayout->addWidget(beginLbl);
    beVLayout->addWidget(beginCbx);
    beVLayout->addWidget(endLbl);
    beVLayout->addWidget(endCbx);
    //GroupBox
    beGbx = new QGroupBox(tr("起点、终点"));
    beGbx->setStyleSheet(QString(gbxStyle));
    beGbx->setLayout(beVLayout);
    beGbx->setFixedWidth(gbxWidth);

    //算法ComboBox
    algthmCbx = new QComboBox;
    algthmCbx->addItem(tr("A星算法"));
    algthmCbx->addItem(tr("迪杰斯特拉算法"));
    algthmCbx->addItem(tr("动态规划算法"));
    algthmCbx->addItem(tr("增强学习算法"));
    //垂直布局
    QVBoxLayout* algthmVLayout = new QVBoxLayout;
    algthmVLayout->addWidget(algthmCbx);
    //GroupBox
    algthmGbx = new QGroupBox(tr("算法选择"));
    algthmGbx->setStyleSheet(QString(gbxStyle));
    algthmGbx->setLayout(algthmVLayout);
    algthmGbx->setFixedWidth(gbxWidth);

    //控制按钮
    ctrlStartBtn = new QPushButton(tr("开始"));
    ctrlPauseBtn = new QPushButton(tr("暂停"));
    ctrlStopBtn = new QPushButton(tr("结束"));
    ctrlResetBtn = new QPushButton(tr("重置"));
    //垂直布局
    QVBoxLayout* ctrlVLayout = new QVBoxLayout;
    ctrlVLayout->addWidget(ctrlStartBtn);
    ctrlVLayout->addWidget(ctrlPauseBtn);
    ctrlVLayout->addWidget(ctrlStopBtn);
    ctrlVLayout->addWidget(ctrlResetBtn);
    //GroupBox
    ctrlGbx = new QGroupBox(tr("控制"));
    ctrlGbx->setStyleSheet(QString(gbxStyle));
    ctrlGbx->setLayout(ctrlVLayout);
    ctrlGbx->setFixedWidth(gbxWidth);

    //窗体垂直布局
    QVBoxLayout* mainVLayout = new QVBoxLayout;
    mainVLayout->addWidget(beGbx);
    mainVLayout->addWidget(algthmGbx);
    mainVLayout->addWidget(ctrlGbx);
    //窗体水平布局
    QSpacerItem *spaceLeft = new QSpacerItem(mapWidth, 0, QSizePolicy::Minimum,QSizePolicy::Minimum);
    QHBoxLayout* mainHLayout = new QHBoxLayout;
    mainHLayout->addSpacerItem(spaceLeft);
    mainHLayout->addLayout(mainVLayout);

    //设置窗体布局
    this->setLayout(mainHLayout);

    connect(&timer,
            SIGNAL(timeout()),
            this,
            SLOT(timeSlot()));

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

}


/* *
 * function:    重置 carPos, pathQpos
 * date:        2018/9/11
 * */
void MapDrive::reset()
{
    this->carPos = -1;
    this->pathQpos.clear();
    memset(this->path, -1, sizeof(this->path));

    this->update();
}


/* *
 * function:    设置Control按钮是否可用
 * parameter:
 *      start:  开始按钮是否可用
 *      pause:  暂停按钮是否可用
 *      stop:   停止按钮是否可用
 *      reset:  重置按钮是否可用
 * date:        2018/9/11
 * */
void MapDrive::setCtrlBtn(bool start, bool pause, bool stop, bool reset)
{
    this->ctrlStartBtn->setEnabled(start);
    this->ctrlPauseBtn->setEnabled(pause);
    this->ctrlStopBtn->setEnabled(stop);
    this->ctrlResetBtn->setEnabled(reset);
}


/* *
 * function:    路径规划
 * return:      -1则为失败
 * date:        1018/9/11
 * */
int MapDrive::routePlanFun()
{
    int begin = this->beginCbx->currentIndex();
    int end = this->endCbx->currentIndex();

    //起点与终点相同
    if (begin == end)
    {
        QMessageBox::warning(this,
                             tr("全局级规划路径"),
                             tr("起点与终点不能相同！"),
                             QMessageBox::Ok);
        return -1;
    }

    //初始化carPos
    this->carPos = 0;

    //获取算法
    int algthmIndex = this->algthmCbx->currentIndex();

    /* *
     * 搜索
     * 0:   AStar
     * 1:   Dijkstra
     * 2:   DP
     * 3:   QLearning
     * */
    switch (algthmIndex)
    {
    case 0://AStar
        //搜索
        this->routePlan->aStar(begin, end, this->path);
        //获取速度
        this->routePlan->getSpeedRecord(this->path, this->speed);
        break;
    case 1://Dijkstra
        //搜索
        this->routePlan->Dijkstra(begin, end, this->path);
        //获取速度
        this->routePlan->getSpeedRecord(this->path, this->speed);
        break;
    case 2://DP
        //搜索
        this->routePlan->dynamicProgram(begin, end, this->path);
        //获取速度
        this->routePlan->getSpeedRecord(this->path, this->speed);
        break;
    case 3://QLearning
        //搜索
        this->routePlan->qLearning(begin, end, this->path);
        //获取速度
        this->routePlan->getSpeedRecord(this->path, this->speed);
        break;
    default:
        return -1;
    }

    //清空pathQpos
    this->pathQpos.clear();
    for (int i = 0; i < max_vertexes && this->path[i] != -1; i++)
    {
        QPoint* tmp = new QPoint(this->nodePos[this->path[i]][0],
                                 this->nodePos[this->path[i]][1]);
        //更新pathQpos
        this->pathQpos.append(tmp);
    }

    return 0;
}


/* *
 * function:    读取mapDrive的地图
 * return:      -1则为失败
 * date:        2018/9/11
 * */
int MapDrive::readMap()
{
    QFile file(QString(":/data/mapdrive.txt"));

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<tr("文件打开失败");
        return -1;
    }

    QTextStream text(&file);

    //读取坐标
    for (int i = 0; i < max_vertexes; i++)
    {
        int tmpx, tmpy;
        text>>tmpx>>tmpy;

        this->nodePos[i][0] = tmpx;
        this->nodePos[i][1] = tmpy;

        qDebug()<<QString("Pos %1: ").arg(i)<<this->nodePos[i][0]<<", "<<this->nodePos[i][1];
    }

    return 0;
}


/* *
 * function:    重绘地图
 * date:        2018/9/11
 * */
void MapDrive::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //地图
    painter.drawPixmap(0, 0,
                       mapWidth, mapHeight,
                       mapImg);

    //背景
    painter.drawPixmap(mapWidth, 0,
                       windowWidth - mapWidth, mapHeight,
                       backImg);

    //路径
    painter.setPen(QPen(Qt::red, 10));
    int size = this->pathQpos.size();
    for (int i = 0; i < size - 1; i++)
    {
        painter.drawLine(*(this->pathQpos[i]), *(this->pathQpos[i + 1]));
    }

    //小车
    if (this->carPos >= 0)
    {
        painter.drawPixmap(this->carQpos.x() - carWidth / 2, this->carQpos.y() - carHeight / 2,
                           carWidth, carHeight,
                           carImg);
    }

    //结点
    for (int i = 0; i < max_vertexes; i++)
    {
        QPoint r(this->nodePos[i][0] - 30, this->nodePos[i][1] + 40);
        QFont font;
        font.setBold(true);
        font.setPointSize(10);
        painter.setPen(QColor(255, 0, 0));
        painter.setFont(font);
        painter.drawText(r, tr("房子 %1").arg(i));
    }

}


/* *
 * function:    通过鼠标按下，按顺序进行映射
 * paramter:
 *      event:  获取鼠标状态
 * date:        2018/9/10
 * */
void MapDrive::mousePressEvent(QMouseEvent *event)
{

    //获取鼠标位置
    QPoint point = event->pos();
    qDebug()<<point.x()<<","<<point.y();

}


/* *
 * function:    定时器槽，重绘地图，更新小车QPoint位置
 * date:        2018/9/11
 * */
void MapDrive::timeSlot()
{
    //计数
    static int count;
    //步数
    static int Steps;
    //步长X
    static int xStep;
    //步长Y
    static int yStep;

    //开始
    if (this->carQpos.x() == this->nodePos[this->path[0]][0] &&
        this->carQpos.y() == this->nodePos[this->path[0]][1])
    {
        //初始化count
        count = 0;
        //初始化xStep
        if (this->nodePos[this->path[carPos + 1]][0] - this->nodePos[this->path[carPos]][0] > 0)
        {
            xStep = pixXStep;
        }
        else
        {
            xStep = -pixXStep;
        }
        //初始化Steps
        Steps = int((this->nodePos[this->path[carPos + 1]][0] - this->nodePos[this->path[carPos]][0]) / (float)xStep);
        //初始化yStep
        yStep = int((this->nodePos[this->path[carPos + 1]][1] - this->nodePos[this->path[carPos]][1]) / (float)(this->nodePos[this->path[carPos + 1]][0] - this->nodePos[this->path[carPos]][0]) * xStep);

        qDebug()<<"xStep: "<<xStep;
        qDebug()<<"Steps: "<<Steps;
        qDebug()<<"yStep: "<<yStep;
    }

    //到达下一个结点
    if (count == Steps)
    {
        //重置计数
        count = 0;

        //更新小车位置
        this->carPos++;
        this->carQpos.setX(this->nodePos[this->path[carPos]][0]);
        this->carQpos.setY(this->nodePos[this->path[carPos]][1]);

        //更新路线
        this->pathQpos.pop_front();

        this->update();

        //到达终点
        if (this->path[carPos + 1] == -1)
        {

            qDebug()<<"arrived";
            QMessageBox::information(this, tr("全局级"), tr("小车到达终点"));
            this->ctrlStopBtnClickedSlot();

            return;
        }

        //更新步长X
        if (this->nodePos[this->path[carPos + 1]][0] - this->nodePos[this->path[carPos]][0] > 0)
        {
            xStep = pixXStep;
        }
        else
        {
            xStep = -pixXStep;
        }

        //更新步数
        Steps = int((this->nodePos[this->path[carPos + 1]][0] - this->nodePos[this->path[carPos]][0]) / (float)xStep);

        //更新步长Y
        yStep = int((this->nodePos[this->path[carPos + 1]][1] - this->nodePos[this->path[carPos]][1]) / (float)(this->nodePos[this->path[carPos + 1]][0] - this->nodePos[this->path[carPos]][0]) * xStep);

        qDebug()<<"xStep: "<<xStep;
        qDebug()<<"Steps: "<<Steps;
        qDebug()<<"yStep: "<<yStep;

        return;
    }

    //更新小车Qpoint位置
    this->carQpos.setX(this->carQpos.x() + xStep);
    this->carQpos.setY(this->carQpos.y() + yStep);

    //更新路线
    this->pathQpos[0]->setX(this->carQpos.x());
    this->pathQpos[0]->setY(this->carQpos.y());

    count++;

    this->update();
}


/* *
 * function:    按下开始按钮，计算路径或者继续开车，开启定时器
 * return:      -1则为失败
 * date:        2018/9/11
 * */
int MapDrive::ctrlStartBtnClickedSlot()
{
    assert(!this->timer.isActive());

    //结束后需重新规划路径
    if (this->carPos == -1)
    {
        //路径规划失败
        if (this->routePlanFun() == -1)
        {
            return -1;
        }
        //初始化小车位置
        this->carPos = 0;
        //初始化小车QPoint位置
        this->carQpos.setX(this->nodePos[this->path[carPos]][0]);
        this->carQpos.setY(this->nodePos[this->path[carPos]][1]);
    }

    //开始定时器
    qDebug()<<"timer start";
    timer.start(int(timeMax / this->speed[carPos]));

    //关闭开始、重置按钮，开启暂停、结束按钮
    this->setCtrlBtn(false, true, true, false);

    return 0;
}


/* *
 * function:    按下暂停按钮，停止定时器
 * date:        2018/9/11
 * */
void MapDrive::ctrlPauseBtnClickedSlot()
{
    assert(this->timer.isActive());

    //停止定时器
    timer.stop();

    //开启开始、结束、重置按钮
    this->setCtrlBtn(true, false, true, true);
}


/* *
 * function:    按下结束按钮，停止定时器
 * date:        2018/9/11
 * */
void MapDrive::ctrlStopBtnClickedSlot()
{
    //停止定时器
    timer.stop();

    //开启重置按钮，关闭开始、暂停、结束按钮
    this->setCtrlBtn(false, false, false, true);
}


/* *
 * function:    按下重置按钮，重置状态
 * date:        2018/9/11
 * */
void MapDrive::ctrlResetBtnClickedSlot()
{
    assert(!this->timer.isActive());

    //重置 carPos, pathQpos
    this->reset();

    //开启开始按钮，关闭暂停、结束、重置按钮
    this->setCtrlBtn(true, false, false, false);

}



