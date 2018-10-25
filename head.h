/* *
 * file:    head.h
 *          公用的宏和全局常量
 * date:    2018/9/8
 * */

#ifndef HEAD_H
#define HEAD_H

//#define NDEBUG
#include <assert.h>

#define totalTime 50    //总时间
#define stateNum 3      //状态数量
#define actNum 3        //动作数量

const int carWidth = 60;        //car宽
const int carHeight = 60;       //car高
const int roadWidth = 1000;     //road宽
const int roadHeight = 206;     //road高
const int obackWidth = 248;     //上背景宽
const int obackHeight = 122;    //上背景高
const int dbackWidth = 382;     //下背景宽
const int dbackHeight = 105;    //下背景高
const int rewGbxWidth = 340;    //rewordGroupBox宽
const int rewGbxHeight = 120;   //rewordGroupBox高
const int qVGbxWidth = rewGbxWidth;//qValueGroupBox宽
const int qVGbxHeight = 80;     //qValueGroupBox高
const int ctrlGbxWidth = roadWidth - rewGbxWidth - 30;//controlGroupBox宽
const int ctrlGbxHeight = rewGbxHeight + qVGbxHeight;//controlGroupBox高
const int windowWidth = roadWidth;//窗体宽
const int windowHeight = obackHeight + roadHeight + dbackHeight + ctrlGbxHeight + 20;//窗体高

const char btnStyle[] = "QPushButton{\
                                font-size:20px;\
                                font-weight:bold;\
                                border:0;\
                                width:60px;\
                                height:50px;\
                                color:#ccc;\
                                background-color:rgba(80,80,80,80);\
                                border-radius:5px}"\
                        "QPushButton:hover {\
                                background-color:rgba(100,100,100,100);\
                                color:#fff}"\
                        "QPushButton:pressed{\
                                background-color:rgb(85, 170, 255);\
                                border-style: inset; }";

const char gbxStyle[] = "QGroupBox {\
                                    background-color: rgba(80,80,80,80);\
                                    color:#ccc}";

const char sliderStyle[] = "QSlider::groove:horizontal {\
                                    height: 6px;\
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));\
                            }\
                            QSlider::handle:horizontal {\
                                    width: 1px;\
                                    background: rgb(0, 160, 230);\
                                    margin: -6px 6px -6px 6px;\
                                    border-radius: 9px;\
                            }";

const int noWay = -100;      //障碍
const int goodWay = 0;          //可以通行
const int bestWay = 100;        //奖励
const int punish = -5;          //转向惩罚
const int timeMin = 100;         //定时器最小定时
const int timeMax = 1000;       //定时器最大定时


#endif // HEAD_H
