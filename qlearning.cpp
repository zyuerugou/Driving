#include "qlearning.h"
#include <QDebug>

QLearning::QLearning()
{
    //R矩阵初始化
    memset(R, 0.0f, sizeof(R));

    initRQ();
}


/* *
 * function:    初始化 Q矩阵、totalR
 * date:        2018/9/11
 * */
void QLearning::initRQ()
{
    //Q矩阵初始化
    memset(Q, 0.0f, sizeof(Q));

    //totalR初始化
    totalR[0] = 0.0f;
}


/* *
 * function:    获取最优动作的Q值
 * return:      最优动作的Q值
 * parameter:
 *      time:   时刻
 *      state:  状态
 * date:        2018/9/7
 * */
float QLearning::getBestActQValue(int time, int state)
{
    assert(time >= 0 && time < totalTime);
    assert(state >= 0 && state < stateNum);

    //初始化maxQ
    float maxQ = Q[time][state][left];
    //查找最大Q值
    for (int i = 1; i < actNum; i++)
    {
        if (maxQ < Q[time][state][i])
        {
            maxQ = Q[time][state][i];
        }
    }

    return maxQ;
}



/* *
 * function:    获取最优的下一个动作
 * return:      下一个动作；-1则为失败
 * parameter:
 *      time:   时刻
 *      state:  当前状态
 * date:        2018/9/7
 * */
int QLearning::getBestAct(int time, int state)
{
    assert(time >= 0 && time < totalTime);
    assert(state >= 0 && state < stateNum);

    //初始化bestAct
    int bestAct = 0;

    //寻找bestAct
    for (int i = 1; i < actNum; i++)
    {
        if (this->Q[time][state][bestAct] < this->Q[time][state][i])
        {
            bestAct = i;
        }
    }

//    //bestAct对应的回报是负值
//    if (this->Q[time][state][bestAct] < 0)
//    {
//        qDebug()<<"Error: bestAct.Q < 0";
//        return -1;
//    }

    //是否有同样回报的bestAct
    int count = 0;
    QVector<int> bestAction;
    for (int i = 0; i < actNum; i++)
    {
        if (this->Q[time][state][bestAct] == this->Q[time][state][i])
        {
            count++;
            bestAction.append(i);
        }
    }

    if (count == 1)
    {
        //没有同样回报的bestAct
        return bestAct;
    }
    else
    {
        //有同样回报的bestAct
        return bestAction[rand() % bestAction.size()];
    }

    return -1;
}


/* *
 * function:    获取下一个动作，e-greedy
 * return:      下一个动作；-1则为失败
 * parameter:
 *      state:  当前状态
 *      e:      采取探索的概率
 * date:        2018/9/7
 * */
int QLearning::getNextAct(int time, int state, float e)
{
    assert(time >= 0 && time < totalTime);
    assert(state >= 0 && state < stateNum);
    assert(e >= 0.0f && e <= 1.0f);

    //获取探索的概率
    float tmp = (float)(rand() % 100) / 100.0f;

    if (tmp < e)
    {
        //探索
        return rand() % actNum;
    }
    else
    {
        //经验，获取最大回报的Action
        return this->getBestAct(time, state);
    }

    return -1;
}


/* *
 * function:    根据当前状态和动作，获取下一个状态
 * return:      下一个状态；-1则为失败
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
int QLearning::getNextState(int state, int act)
{
    assert(state >= 0 && state < stateNum);
    assert(act >= 0 && act < actNum);

    switch (act)
    {
    case left:     //左转
        //上边界
        if (state == 0)
        {
            return -1;
        }
        return state - 1;

    case straight:     //直行
        return state;

    case right:     //右转
        //下边界
        if (state == stateNum - 1)
        {
            return -1;
        }
        return state + 1;

    default:
        return -1;
    }
}


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
int QLearning::setR(float map[totalTime][stateNum])
{
    for (int i = 0; i < totalTime - 1; i++)
    {
        for (int j = 0; j < stateNum; j++)
        {
            for (int k = 0; k < actNum; k++)
            {
                //获取下一个状态
                int nextState = this->getNextState(j, k);
                //获取失败
                if (nextState == -1)
                {
                    this->R[i][j][k] = noWay; 
                }
                else
                {
                    //获取成功
                    this->R[i][j][k] = map[i + 1][nextState];
                }

                //转向惩罚
                if (k != straight)
                {
                    this->R[i][j][k] += punish;
                }
            }
        }
    }

    return 0;
}


/* *
 * function:    进行学习
 * return:      -1则为失败
 * parameter:
 *      num:    迭代代数
 *      gamma:  衰减率
 *      e:      探索概率
 * date:        2018/9/11
 * */
int QLearning::learning(int num, float gamma, float e)
{
    assert(num > 0);
    assert(gamma > 0.0f && gamma < 1.0f);

    //训练
    for (int i = 0; i < num; i++)
    {
        //每一代迭代

        //初始化状态
        int state = rand() % stateNum;
        //每一次状态变换
        for (int t = 0; t < totalTime - 1; t++)
        {
            //获取下一个动作
            int nextAct = this->getNextAct(t, state, e);
            //获取动作失败
            if (nextAct == -1)
            {
                //做直行处理
                nextAct = straight;
            }

            //获取下一个状态
            int nextState = this->getNextState(state, nextAct);
            //获取下一个状态失败
            if (nextState == -1)
            {
                //做直行处理
                nextState = state;
            }

            //更新Q矩阵
            Q[t][state][nextAct] = R[t][state][nextAct] + gamma * this->getBestActQValue(t + 1, nextState);

            //更新状态
            state = nextState;

        }
    }

    return 0;
}


/* *
 * function:    选择动作
 * return:      状态序列；-1则为失败
 * parameter:
 *      state:  初始状态
 * date:        2018/9/7
 * */
QVector<int> QLearning::chooseAction(int state)
{
    assert(state >= 0 && state < stateNum);

    //初始化
    this->state.clear();

    //计算状态序列
    for (int t = 0; t < totalTime - 1; t++)
    {
        //获取bestAct
        int nextAct = this->getBestAct(t, state);

        qDebug()<<t<<": "<<state<<", "<<nextAct;

        //获取失败
        if (nextAct == -1)
        {
            this->state.clear();
            this->state.append(-1);
            break;
        }
        //更新totalR
        this->totalR[t + 1] = this->totalR[t] + this->R[t][state][nextAct];
        //更新state
        int tmp = this->getNextState(state, nextAct);
        //更新成功
        if (tmp != -1)
        {
            state = tmp;
        }

        //将bestAct加入动作序列
        this->state.append(state);

    }

    qDebug()<<"action size: "<<this->state.size();

    return this->state;
}


/* *
 * function:    根据time，获取累计R值
 * return:      累计R值
 * parameter:
 *      time:   时刻
 * date:        2018/9/10
 * */
float QLearning::getTotalR(int time)
{
    assert(time >= 0 && time < totalTime);

    return this->totalR[time];
}


/* *
 * function:    根据time，state，获取当前状态的各个Act的Q值
 * return:      各个Act的Q值
 * parameter:
 *      time:   时刻
 *      state:  状态
 * date:        2018/9/10
 * */
float* QLearning::getCurrentActQ(int time, int state)
{
    assert(time >= 0 && time < totalTime);
    assert(state >=0 && state <stateNum);

    float* currentActQ = new float[actNum];

    //获取当前时刻当前状态的各个actQ
    for (int i = 0; i < actNum; i++)
    {
        currentActQ[i] = this->Q[time][state][i];
    }

    return currentActQ;
}


/* *
 * function:    根据time，state，获取当前状态的各个Act的R值
 * return:      各个Act的R值
 * parameter:
 *      time:   时刻
 *      state:  状态
 * date:        2018/9/11
 * */
float* QLearning::getCurrentActR(int time, int state)
{
    assert(time >= 0 && time < totalTime);
    assert(state >=0 && state <stateNum);

    float* currentActR = new float[actNum];

    //获取当前时刻当前状态的各个actQ
    for (int i = 0; i < actNum; i++)
    {
        currentActR[i] = this->R[time][state][i];
    }

    return currentActR;
}


/* *
 * function:    根据time，state，获取当前状态
 * return:      当前状态
 * parameter:
 *      time:   时刻
 * date:        2018/9/17
 * */
int QLearning::getCurrentState(int time)
{
    assert(!this->state.isEmpty());
    assert(this->state[0] != -1);
    assert(time >= 0 && time < this->state.size());

    return this->state[time];
}


