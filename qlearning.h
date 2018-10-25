/* *
 * Class:   QLearning
 *          Q-Learning实现
 * Run:
 *          setR
 *          learning
 *          chooseAction
 * date:    2018/9/7
 * */



#ifndef QLEARNING_H
#define QLEARNING_H

#include <QVector>
#include <cstring>
#include <cstdlib>

#include "head.h"


class QLearning
{
public:
    QLearning();

    /* *
     * function:    初始化 Q矩阵、totalR
     * date:        2018/9/11
     * */
    void initRQ();

    /* *
     * function:    获取最优动作的Q值
     * return:      最优动作的Q值
     * parameter:
     *      time:   时刻
     *      state:  状态
     * date:        2018/9/7
     * */
    float getBestActQValue(int time, int state);

    /* *
     * function:    获取最优的下一个动作
     * return:      下一个动作；-1则为失败
     * parameter:
     *      time:   时刻
     *      state:  当前状态
     * date:        2018/9/7
     * */
    int getBestAct(int time, int state);

    /* *
     * function:    获取下一个动作，e-greedy
     * return:      下一个动作；-1则为失败
     * parameter:
     *      state:  当前状态
     *      e:      采取探索的概率
     * date:        2018/9/7
     * */
    int getNextAct(int time, int state, float e);

    /* *
     * function:    根据当前状态和动作，获取下一个状态
     * return:      下一个状态，-1则为失败
     * parameter:
     *      state:  当前状态
     *              0:  lane0
     *              1:  lane1
     *              2:  lane2
     *      act:    当前动作
     *              0:  left
     *              1:  straight
     *              2:  right
     * date:        2018/9/7
     * */
    int getNextState(int state, int act);

    /* *
     * function:    根据map，设置R矩阵
     * result:      -1则为失败
     * parameter:
     *      map:    二维矩阵表示是否可以通行，
     *              noWay:      障碍
     *              goodWay:    可通行
     *              bestWay:    奖励
     * date:        2018/9/7
     * */
    int setR(float map[totalTime][stateNum]);

    /* *
     * function:    进行学习
     * return:      -1则为失败
     * parameter:
     *      num:    迭代代数
     *      gamma:  衰减率
     *      e:      探索概率
     * date:        2018/9/11
     * */
    int learning(int num, float gamma, float e);

    /* *
     * function:    选择动作
     * return:      状态序列；-1则为失败
     * parameter:
     *      state:  初始状态
     * date:        2018/9/7
     * */
    QVector<int> chooseAction(int state);

    /* *
     * function:    根据time，获取累计R值
     * return:      累计R值
     * parameter:
     *      time:   时刻
     * date:        2018/9/10
     * */
    float getTotalR(int time);

    /* *
     * function:    根据time，state，获取当前状态的各个Act的Q值
     * return:      各个Act的Q值
     * parameter:
     *      time:   时刻
     *      state:  状态
     * date:        2018/9/10
     * */
    float* getCurrentActQ(int time, int state);

    /* *
     * function:    根据time，state，获取当前状态的各个Act的R值
     * return:      各个Act的R值
     * parameter:
     *      time:   时刻
     *      state:  状态
     * date:        2018/9/11
     * */
    float* getCurrentActR(int time, int state);

    /* *
     * function:    根据time，state，获取当前状态
     * return:      当前状态
     * parameter:
     *      time:   时刻
     * date:        2018/9/17
     * */
    int getCurrentState(int time);

private:
    //R矩阵
    float R[totalTime][stateNum][actNum];
    //Q矩阵
    float Q[totalTime][stateNum][actNum];

    //R累计
    float totalR[totalTime];

    //state序列
    QVector<int> state;

    enum {
        left = 0,                   //左转
        straight = 1,               //直行
        right = 2                   //右转
    };
};

#endif // QLEARNING_H
