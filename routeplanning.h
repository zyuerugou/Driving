#ifndef ROUTEPLANNING_H
#define ROUTEPLANNING_H

#define max_vertexes 16
#define max_path_vertexes 25
#define MAX_POWER 10000
#define ROW    16
#define COLUMN 16
#define STATE_NUM 16
#define ACTION_NUM 16
#define alph 0.8
#include <iostream>
#include "stdlib.h"
#include "math.h"
#include<cstring>
#include<cmath>
#include <cstdlib>

using namespace std;


struct path{//表节点
    float speed;//路上最佳速度
    float distance;//距离
    int mark;
    int ivex;
    path* ilink;
    int jvex;
    path* jlink;
    path(){
        speed=1;
        distance=1;
        mark=0;
        ivex=-1;
        ilink=this;
        jvex=-1;
        jlink=this;
    }
};

struct headPoint{//点节点
    int headPointID;//节点号
    int x;
    int y;
    path* firstin;//所连接的第一条路径
    headPoint(){
        x=-1;
        y=-1;
    }
};

class routePlanning
{
private:
    headPoint* graphPoint;
    path* graphPath;
    float a[100][100];
    float b[100][100];
    /*Q(s,a),学习函数,初始化为0*/
    float Q[100][100];
    /*初始化的顺序*/
    int initial_can_go[10];//存储可以做的action
    int a_can_go[10];//存储可以做的action
    int NUM=0;
    //Qlearning算法奖励矩阵
    float R[100][100]={{-1,1.33/4.2,1.5/3.4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                       {1.33/4.2,-1,-1,1.71/4.4,1.2/4.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                       {1.5/3.4,-1,-1,-1,4.0/5.6,3.0/3.5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                       {-1,1.71/4.4,-1,-1,-1,-1,1.09/2.9,1.5/35,-1,-1,-1,-1,-1,-1,-1,-1},
                       {-1,1.2/4.1,4.0/5.6,-1,-1,1.5/5.2,-1,2.0/2.9,1.33/2.0,-1,-1,-1,-1,-1,-1,-1},
                       {-1,-1,3.0/3.5,-1,1.5/5.2,-1,-1,-1,2.4/5.0,1.33/4.0,-1,-1,-1,-1,-1,-1},
                       {-1,-1,-1,1.09/2.9,-1,-1,-1,-1,-1,-1,3.0/3.2,-1,-1,-1,-1,-1},
                       {-1,-1,-1,1.5/3.5,1.33/2.0,-1,-1,-1,-1,-1,1.2/3.4,0.92/3.2,-1,-1,-1,-1},
                       {-1,-1,-1,-1,2.0/2.9,2.4/5.0,-1,-1,-1,-1,-1,0.75/3.00,12.0/4.2,-1,-1,-1},
                       {-1,-1,-1,-1,-1,1.33/4.0,-1,-1,-1,-1,-1,-1,6.0/2.2,-1,-1,-1},
                       {-1,-1,-1,-1,-1,-1,3.0/3.2,1.2/3.2,-1,-1,-1,-1,-1,0.8/4.5,-1,-1},
                       {-1,-1,-1,-1,-1,-1,-1,0.92/3.4,0.75/3.0,-1,-1,-1,-1,1.71/2.2,0.8/4.2,-1},
                       {-1,-1,-1,-1,-1,-1,-1,-1,12.0/4.2,6.0/2.2,-1,-1,-1,-1,0.75/3.0,-1},
                       {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.8/4.5,1.71/2.2,-1,-1,-1,1.09/2.8},
                       {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.8/4.2,0.75/3.0,-1,-1,0.86/2.2},
                       {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1.09/2.8,0.86/2.2,-1}};
public:
    routePlanning();
    ~routePlanning();
    float getSpeed(int startPoint,int endPoint);//获得单个速度
    float getDistance(int startPoint,int endPoint);//获得单个路程
    void getDistanceRecord(int* record,float* speedRecord);//获得一条路径的速度
    void getSpeedRecord(int* record,float* speedRecord);//获得一条路径的路程
    float dynamicProgram(int beginPoint,int endPoint,int* record,int recordNum=0,int* passPoint=NULL,int passPointNum=0);//动态规划算法核心代码
    float Dijkstra(int startPoint,int endPoint, int *pathPoint);//dijstra算法核心代码
    void setEuclideanmetric(int pos[max_vertexes][2]);//函数功能：Astar算法中欧拉距离的初始化赋值
    float h(int startPoint,int endPoint);//函数功能：Atar算法中的h（x）的计算
    float aStar(int startPoint,int endPoint,int* pathPoint);//Astar算法核心代码
    void get_go_value(float a[100][100],int can_go[10],int state);//函数功能：得到所有的下一个状态
    float get_max_value(float Q[100][100],int state);//函数功能：得到下一个状态的最大奖励
    int get_max_tab(float Q[100][100],int state);//函数功能：得到最大奖励的下一个状态
    int learning_G(int initial, float R[100][100],float Q[100][100],int flag);//函数功能：Qlearning训练算法
    float qLearning(int startPoint,int endPoint,int* pathPoint);//函数功能：总的QLearning调用函数
};

#endif // ROUTEPLANNING_H
