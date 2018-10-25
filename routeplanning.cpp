#include "routeplanning.h"
/*
 * 构造函数
 * 函数功能：初始化十字链表
 * */
routePlanning::routePlanning()
{

    graphPath=new path[25];
    graphPoint=new headPoint[16];

    graphPoint[0].headPointID=0;
    graphPoint[0].firstin=graphPath+0;
    graphPath[0].distance=4.2;
    graphPath[0].speed=1.33;
    graphPath[0].mark=0;
    graphPath[0].ivex=0;
    graphPath[0].ilink=graphPath+1;
    graphPath[1].distance=3.4;
    graphPath[1].speed=1.50;
    graphPath[1].mark=1;
    graphPath[1].ivex=0;
    graphPath[1].ilink=NULL;

    graphPoint[1].headPointID=1;
    graphPoint[1].firstin=graphPath+0;
    graphPath[0].jvex=1;
    graphPath[0].jlink=graphPath+2;
    graphPath[2].distance=4.4;
    graphPath[2].speed=1.71;
    graphPath[2].mark=2;
    graphPath[2].ivex=1;
    graphPath[2].ilink=graphPath+3;
    graphPath[3].distance=4.1;
    graphPath[3].speed=1.20;
    graphPath[3].mark=3;
    graphPath[3].ivex=1;
    graphPath[3].ilink=NULL;

    graphPoint[2].headPointID=2;
    graphPoint[2].firstin=graphPath+4;
    graphPath[4].ivex=2;
    graphPath[4].distance=5.6;
    graphPath[4].speed=4.00;
    graphPath[4].mark=4;
    graphPath[4].ilink=graphPath+5;
    graphPath[5].distance=3.5;
    graphPath[5].speed=3.00;
    graphPath[5].mark=5;
    graphPath[5].ivex=2;
    graphPath[5].ilink=graphPath+1;
    graphPath[1].jvex=2;
    graphPath[1].jlink=NULL;

    graphPoint[3].headPointID=3;
    graphPoint[3].firstin=graphPath+11;
    graphPath[11].ivex=3;
    graphPath[11].distance=2.9;
    graphPath[11].speed=1.09;
    graphPath[11].mark=11;
    graphPath[11].ilink=graphPath+2;
    graphPath[2].jvex=3;
    graphPath[2].jlink=graphPath+12;
    graphPath[12].distance=3.5;
    graphPath[12].speed=1.50;
    graphPath[12].mark=12;
    graphPath[12].ivex=3;
    graphPath[12].ilink=NULL;

    graphPoint[4].headPointID=4;
    graphPoint[4].firstin=graphPath+4;
    graphPath[4].jvex=4;
    graphPath[4].jlink=graphPath+6;
    graphPath[6].distance=2.0;
    graphPath[6].speed=1.33;
    graphPath[6].mark=6;
    graphPath[6].ivex=4;
    graphPath[6].ilink=graphPath+7;
    graphPath[7].distance=2.9;
    graphPath[7].speed=2.00;
    graphPath[7].mark=7;
    graphPath[7].ivex=4;
    graphPath[7].ilink=graphPath+3;
    graphPath[3].jvex=4;
    graphPath[3].jlink=graphPath+8;
    graphPath[8].distance=5.2;
    graphPath[8].speed=1.50;
    graphPath[8].mark=8;
    graphPath[8].ivex=4;
    graphPath[8].ilink=NULL;

    graphPoint[5].headPointID=5;
    graphPoint[5].firstin=graphPath+9;
    graphPath[9].distance=5.0;
    graphPath[9].speed=2.4;
    graphPath[9].mark=9;
    graphPath[9].ivex=5;
    graphPath[9].ilink=graphPath+5;
    graphPath[5].jvex=5;
    graphPath[5].jlink=graphPath+10;
    graphPath[10].distance=4.0;
    graphPath[10].speed=1.33;
    graphPath[10].mark=10;
    graphPath[10].ivex=5;
    graphPath[10].ilink=graphPath+8;
    graphPath[8].jvex=5;
    graphPath[8].jlink=NULL;

    graphPoint[6].headPointID=6;
    graphPoint[6].firstin=graphPath+11;
    graphPath[11].jvex=6;
    graphPath[11].jlink=graphPath+18;
    graphPath[18].ivex=6;
    graphPath[18].ilink=NULL;
    graphPath[18].distance=3.2;
    graphPath[18].speed=3.00;
    graphPath[18].mark=18;

    graphPoint[7].headPointID=7;
    graphPoint[7].firstin=graphPath+13;
    graphPath[13].distance=3.2;
    graphPath[13].speed=1.20;
    graphPath[13].mark=13;
    graphPath[13].ivex=7;
    graphPath[13].ilink=graphPath+6;
    graphPath[6].jvex=7;
    graphPath[6].jlink=graphPath+12;
    graphPath[12].jvex=7;
    graphPath[12].jlink=graphPath+14;
    graphPath[14].distance=3.4;
    graphPath[14].speed=0.92;
    graphPath[14].mark=14;
    graphPath[14].ivex=7;
    graphPath[14].ilink=NULL;

    graphPoint[8].headPointID=8;
    graphPoint[8].firstin=graphPath+9;
    graphPath[9].jvex=8;
    graphPath[9].jlink=graphPath+7;
    graphPath[7].jvex=8;
    graphPath[7].jlink=graphPath+15;
    graphPath[15].distance=3.0;
    graphPath[15].speed=0.75;
    graphPath[15].mark=15;
    graphPath[15].ivex=8;
    graphPath[15].ilink=graphPath+16;
    graphPath[16].distance=4.2;
    graphPath[16].speed=12.00;
    graphPath[16].mark=16;
    graphPath[16].ivex=8;
    graphPath[16].ilink=NULL;

    graphPoint[9].headPointID=9;
    graphPoint[9].firstin=graphPath+17;
    graphPath[17].distance=2.2;
    graphPath[17].speed=6.00;
    graphPath[17].mark=17;
    graphPath[17].ivex=9;
    graphPath[17].ilink=graphPath+10;
    graphPath[10].jvex=9;
    graphPath[10].jlink=NULL;

    graphPoint[10].headPointID=10;
    graphPoint[10].firstin=graphPath+13;
    graphPath[13].jvex=10;
    graphPath[13].jlink=graphPath+18;
    graphPath[18].jvex=10;
    graphPath[18].jlink=graphPath+19;
    graphPath[19].distance=4.5;
    graphPath[19].speed=0.80;
    graphPath[19].mark=19;
    graphPath[19].ivex=10;
    graphPath[19].ilink=NULL;

    graphPoint[11].headPointID=11;
    graphPoint[11].firstin=graphPath+20;
    graphPath[20].distance=2.2;
    graphPath[20].speed=1.71;
    graphPath[20].mark=20;
    graphPath[20].ivex=11;
    graphPath[20].ilink=graphPath+21;
    graphPath[21].distance=4.2;
    graphPath[21].speed=0.80;
    graphPath[21].mark=21;
    graphPath[21].ivex=11;
    graphPath[21].ilink=graphPath+15;
    graphPath[15].jvex=11;
    graphPath[15].jlink=graphPath+14;
    graphPath[14].jvex=11;
    graphPath[14].jlink=NULL;

    graphPoint[12].headPointID=12;
    graphPoint[12].firstin=graphPath+17;
    graphPath[17].jvex=12;
    graphPath[17].jlink=graphPath+22;
    graphPath[22].distance=3.0;
    graphPath[22].speed=1.75;
    graphPath[22].mark=22;
    graphPath[22].ivex=12;
    graphPath[22].ilink=graphPath+16;
    graphPath[16].jvex=12;
    graphPath[16].jlink=NULL;

    graphPoint[13].headPointID=13;
    graphPoint[13].firstin=graphPath+20;
    graphPath[20].jvex=13;
    graphPath[20].jlink=graphPath+19;
    graphPath[19].jvex=13;
    graphPath[19].jlink=graphPath+23;
    graphPath[23].distance=2.8;
    graphPath[23].speed=1.09;
    graphPath[23].mark=23;
    graphPath[23].ivex=13;
    graphPath[23].ilink=NULL;

    graphPoint[14].headPointID=14;
    graphPoint[14].firstin=graphPath+22;
    graphPath[22].jvex=14;
    graphPath[22].jlink=graphPath+21;
    graphPath[21].jvex=14;
    graphPath[21].jlink=graphPath+24;
    graphPath[24].distance=2.2;
    graphPath[24].speed=1.86;
    graphPath[24].mark=24;
    graphPath[24].ivex=14;
    graphPath[24].ilink=NULL;

    graphPoint[15].headPointID=15;
    graphPoint[15].firstin=graphPath+24;
    graphPath[24].jvex=15;
    graphPath[24].jlink=graphPath+23;
    graphPath[23].jvex=15;
    graphPath[23].jlink=NULL;

}

//析构函数
routePlanning::~routePlanning()
{
    delete [] graphPath;
    delete [] graphPoint;
}

//路径规划————动态规划
/*
 * 起始节点：begainPoint
 * 截止节点：endPoint
 * 路径标记：record   //标记出最优路径
 * 路径层级标记：record（一般默认，只是递归需要）
 * 已经路过的节点：passPoint（一般默认，只是递归需要）
 * 路过节点层级标记：passPointNum（一般默认，只是递归需要）
*/
float routePlanning::dynamicProgram(int beginPoint,int endPoint,int* record,int recordNum,int* passPoint,int passPointNum)
{
    path* pathPointer;
    //headPoint* headPointer;
    int *newRecord=new int[16];
    for(int i=0;i<16;i++){//更新标记路径初始化
        newRecord[i]=-1;
    }
    float w=0,minw=10000;
    if(beginPoint==endPoint){//最后一个节点
        record[recordNum]=beginPoint;
        for(int i=recordNum+1;i<16;i++){//最后一个节点之后的节点回归初始化
            record[i]=-1;
        }
        return 0;
    }

    //headPointer=carLocation+beginPoint;

    //循环递归————遍历经过节点的路径
    for(pathPointer=graphPoint[beginPoint].firstin;pathPointer!=NULL;){

        //十字链表中i，j地位相同
        if(pathPointer->ivex==beginPoint){//屏蔽已经路过的路径
            int j=0;
            for(;j<passPointNum;j++){
                if(pathPointer->jvex==passPoint[j]){
                    break;
                }
            }
            if(j<passPointNum)
                goto cont;


            int* passPointNew=new int[passPointNum+1];//更新路过的路径
            for(int i=0;i<passPointNum;i++)
            {
                passPointNew[i]=passPoint[i];
            }
            passPointNew[passPointNum]=beginPoint;

            //递归遍历下一个节点的路径
            w=pathPointer->distance/pathPointer->speed + dynamicProgram(pathPointer->jvex,endPoint,newRecord,recordNum+1,passPointNew,passPointNum+1);

            //找出最小代价的子路径及其值
            if(w<minw)
            {
                minw=w;
                for(int i=recordNum+1;i<16;i++){
                    record[i]=newRecord[i];
                }
            }

            //清除内存
            delete(passPointNew);

        }else if(pathPointer->jvex==beginPoint){
            int j=0;
            for(;j<passPointNum;j++){//屏蔽已路过的路径
                if(pathPointer->ivex==passPoint[j]){
                    break;
                }
            }
            if(j<passPointNum)
                goto cont;


            int* passPointNew=new int[passPointNum+1];//更新已路过的路径
            for(int i=0;i<passPointNum;i++)
            {
                passPointNew[i]=passPoint[i];
            }
            passPointNew[passPointNum]=beginPoint;
            //递归调用————遍历下一个节点的路径
            w=pathPointer->distance/pathPointer->speed + dynamicProgram(pathPointer->ivex,endPoint,newRecord,recordNum+1,passPointNew,passPointNum+1);
            //找出最优子路径
            if(w<minw)
            {
                minw=w;
                for(int i=recordNum+1;i<16;i++){
                    record[i]=newRecord[i];
                }
            }
            delete[] passPointNew;

        }else{//路径错误
            printf("DATA ERROR!!!");
            exit(1);
        }
        //更新节点指向下一条路径
        cont:if(pathPointer->ivex==beginPoint){
            pathPointer=pathPointer->ilink;
        }else if(pathPointer->jvex==beginPoint){
            pathPointer=pathPointer->jlink;
        }



    }
    //更新路径标记
    record[recordNum]=beginPoint;

    //清除内存
    delete[] newRecord;
    delete pathPointer;
    //delete(headPointer);
    //返回最短权值
    return minw;

}

/*===============================================

                单源最短路径

                Dijkstra 算法

            适用条件：所有边的权非负

            !!注意：
            1.输入的图的权必须非负
            2.顶点标号从0开始


================================================*/
/*
 * startPoint 开始节点的标号
 * endPoint 结束节点的标号
 * pathPoint 最短路径路径
 * */
float routePlanning::Dijkstra(int startPoint,int endPoint, int *pathPoint)
{
    int i,j, mark[max_vertexes]/*遍历过的节点记录*/,pathMark[max_vertexes][max_vertexes]/*路径记录*/;
    float djPower[max_vertexes];//权值记录
    headPoint* vexPoint;
    path* linkPoint;
    //初始化路径记录
    for (i=0;i<max_vertexes;i++){
        for(j=0;j<max_vertexes;j++){
            pathMark[i][j]=-1;
        }
    }
    pathMark[startPoint][0]=startPoint;

    for (i=0; i<max_vertexes; i++) mark[i]=-1;

    //权值标记初始化为无穷
    for (i=0; i<max_vertexes; i++)
    {
        djPower[i]=MAX_POWER;
    }
    //第一个遍历过的节点——起始节点
    mark[0]=startPoint;
    //起始节点到自己的代价为0
    djPower[startPoint]=0;

    //遍历
    for(vexPoint=graphPoint+startPoint;;)
    {
        float min=10000;
        int minVex=-1;

        //遍历，更新权值表
        for(linkPoint=vexPoint->firstin;linkPoint!=NULL;)
        {
            if(linkPoint->ivex==vexPoint->headPointID){
                //十字链表中i，j地位相同
                if(djPower[linkPoint->jvex]>djPower[linkPoint->ivex]+linkPoint->distance/linkPoint->speed)
                {
                    //更新权值表
                    djPower[linkPoint->jvex]=djPower[linkPoint->ivex]+linkPoint->distance/linkPoint->speed;
                    //更新最短路径
                    for(i=0;i<max_vertexes && pathMark[linkPoint->ivex][i]!=-1;i++){
                        pathMark[linkPoint->jvex][i]=pathMark[linkPoint->ivex][i];
                    }
                    pathMark[linkPoint->jvex][i]=linkPoint->jvex;
                    for(i=i+1;i<max_vertexes;i++){
                        pathMark[linkPoint->jvex][i]=-1;
                    }
                }
                linkPoint=linkPoint->ilink;
            }else if(linkPoint->jvex==vexPoint->headPointID){
                if(djPower[linkPoint->ivex]>djPower[linkPoint->jvex]+linkPoint->distance/linkPoint->speed)
                {
                    //更新权值表
                    djPower[linkPoint->ivex]=djPower[linkPoint->jvex]+linkPoint->distance/linkPoint->speed;
                    //更新最短路径
                    for(i=0;i<max_vertexes && pathMark[linkPoint->jvex][i]!=-1;i++){
                        pathMark[linkPoint->ivex][i]=pathMark[linkPoint->jvex][i];
                    }
                    pathMark[linkPoint->ivex][i]=linkPoint->ivex;
                    for(i=i+1;i<max_vertexes;i++){
                        pathMark[linkPoint->ivex][i]=-1;
                    }
                }
                linkPoint=linkPoint->jlink;
            }else{
                cout<<"DATA ERROR!!!";//数据错误
                exit(0);
            }
        }

        //将最短路径加入mark
        for(j=0;j<max_vertexes;j++){

            if(djPower[j]<min){
                for(i=0;i<max_vertexes;i++){
                    if(mark[i]==j){
                        break;
                    }
                }
                if(i==max_vertexes){
                    min=djPower[j];
                    minVex=j;
                }
            }
        }
        for (i=0;i<max_vertexes;i++){
            if(mark[i]==-1){
                mark[i]=minVex;
                break;
            }
        }
        //数据错误，溢出
        if(i==max_vertexes-1){
            cout<<"DATA OVERFLOW!!!";
            break;
        }
        //更新节点
        vexPoint=graphPoint+minVex;
    }
    for(i=0;i<max_vertexes;i++){
        pathPoint[i]=pathMark[endPoint][i];
    }
    return djPower[endPoint];//返回到最终路径的权值
}

/*void routePlanning::setEuclideanmetric(int *pos)
{
    for(int i=0;i<max_vertexes;i++)
    {
        graphPoint[i].x=*(pos+2*i);
        graphPoint[i].y=*(pos+2*i+1);
    }
}*/

/*
 * 函数功能：Astar算法中欧拉距离的初始化赋值
 * pos：坐标点的二维数组
 * */
void routePlanning::setEuclideanmetric(int pos[max_vertexes][2])
{
    for(int i=0;i<max_vertexes;i++)
    {
        graphPoint[i].x=pos[i][0];
        graphPoint[i].y=pos[i][1];
    }
}
/*
 * 函数功能：Atar算法中的h（x）的计算
 * startPoint：当前点
 * endPoint：终止点
 * */
float routePlanning::h(int startPoint,int endPoint)
{
    //没调用过setEuclideanmetric就按点的序号来
    if((graphPoint[startPoint].x==-1)){
        return abs(startPoint-endPoint);
    }else{//调用过setEuclideanmetric就算图中的欧拉距离
        return float(sqrt(pow((graphPoint[startPoint].x-graphPoint[endPoint].x),2)+pow((graphPoint[startPoint].y-graphPoint[endPoint].y),2)));
    }
}

/*
 * 函数功能：Astar算法核心代码
 * 起始节点：begainPoint
 * 截止节点：endPoint
 * 路径标记：pathPoint   //标记出最优路径
 * */
float routePlanning::aStar(int startPoint,int endPoint,int* pathPoint)
{
    int i,j;
    float g=0;
    headPoint* vexPoint;
    path* linkPoint;
    for(i=0;i<max_vertexes;i++){//初始化标记路径
        pathPoint[i]=-1;
    }

    //循环找到路径
    pathPoint[0]=startPoint;
    for(vexPoint=graphPoint+startPoint;vexPoint->headPointID!=endPoint;)
    {
        float minw=MAX_POWER,ming=0;//标记最小估计值
        int   minp=-1;//标记最小点

        //遍历所有邻接点，找出最小的估计值的下一个点
        //十字链表中i，j地位相同
        for(linkPoint=vexPoint->firstin;linkPoint!=NULL;)
        {
            if(linkPoint->ivex==vexPoint->headPointID){

                //判断已被遍历过
                for(j=0;j<max_vertexes;j++){
                    if(linkPoint->jvex==pathPoint[j]){
                        break;
                    }
                }
                if(j!=max_vertexes){
                    goto iNext;//如果被遍历过，指向下一个路径
                }
                if(minw>g+linkPoint->distance/linkPoint->speed+h(linkPoint->jvex,endPoint)){
                    minw=g+linkPoint->distance/linkPoint->speed+h(linkPoint->jvex,endPoint);
                    ming=g+linkPoint->distance/linkPoint->speed;
                    minp=linkPoint->jvex;
                }
                iNext:linkPoint=linkPoint->ilink;//更新路径节点
            }else if(linkPoint->jvex==vexPoint->headPointID){

                //判断已被遍历过
                for(j=0;j<max_vertexes;j++){
                    if(linkPoint->ivex==pathPoint[j]){
                        break;
                    }
                }

                if(j!=max_vertexes){
                    goto jNext;//如果被遍历过，指向下一个路径
                }
                if(minw>g+linkPoint->distance/linkPoint->speed+h(linkPoint->ivex,endPoint)){
                    minw=g+linkPoint->distance/linkPoint->speed+h(linkPoint->ivex,endPoint);
                    ming=g+linkPoint->distance/linkPoint->speed;
                    minp=linkPoint->ivex;
                }
                jNext:linkPoint=linkPoint->jlink;//更新路径节点
            }else{
                cout<<"DATA ERROR!!!";//数据出错
                exit(0);
            }
        }
        if(minp==-1){
            cout<<"DATA ERROR!!!";//没有最小点，数据出错
            exit(0);
        }
        g=ming;
        vexPoint=graphPoint+minp;
        for(i=0;i<max_vertexes;i++){
            if(pathPoint[i]==-1)
                break;
        }
        pathPoint[i]=minp;

    }
    return g;

}

/*//函数功能：得到两点之间的速度
 * startPoint：起始节点
 * endPoint：终止节点
 * */
float routePlanning::getSpeed(int startPoint,int endPoint)
{
    headPoint* vexPoint=graphPoint+startPoint;
    path* pathPoint;
    for(pathPoint=vexPoint->firstin;pathPoint!=NULL;)
    {
        //十字链表中i，j地位相同
        if(startPoint==pathPoint->ivex){
            if(endPoint==pathPoint->jvex){
                return pathPoint->speed;
            }
            pathPoint=pathPoint->ilink;
        }else if(startPoint==pathPoint->jvex){
            if(endPoint==pathPoint->ivex){
                return pathPoint->speed;
            }
            pathPoint=pathPoint->jlink;
        }else{
            cout<<"DATA ERROR";
            exit(0);
        }

    }
    cout<<"POINT ERROR";
    return 10000;
}

/*//函数功能：得到两点之间的路程
 * startPoint：起始节点
 * endPoint：终止节点
 * */
float routePlanning::getDistance(int startPoint,int endPoint)
{
    headPoint* vexPoint=graphPoint+startPoint;
    path* pathPoint;
    for(pathPoint=vexPoint->firstin;pathPoint!=NULL;)
    {
        //十字链表中i，j地位相同
        if(startPoint==pathPoint->ivex){
            if(endPoint==pathPoint->jvex){
                return pathPoint->distance;
            }
            pathPoint=pathPoint->ilink;
        }else if(startPoint==pathPoint->jvex){
            if(endPoint==pathPoint->ivex){
                return pathPoint->distance;
            }
            pathPoint=pathPoint->jlink;
        }else{
            cout<<"DATA ERROR";
            exit(0);
        }

    }
    cout<<"POINT ERROR";
    return 10000;

}

/*//函数功能：得到路径路程记录
 * record：路径记录
 * SpeedRecord：路径的路程记录
 * */
void routePlanning::getDistanceRecord(int* record,float* DistanceRecord)
{
    for(int i=0;i<max_vertexes-1&&record[i+1]!=-1;i++){
        DistanceRecord[i]=getSpeed(record[i],record[i+1]);
    }
}

/*//函数功能：得到路径速度记录
 * record：路径记录
 * SpeedRecord：路径的速度记录
 * */
void routePlanning::getSpeedRecord(int* record,float* SpeedRecord)
{
    for(int i=0;i<max_vertexes-1&&record[i+1]!=-1;i++){
        SpeedRecord[i]=getDistance(record[i],record[i+1]);
    }
}

/*
 * 函数功能：得到所有的下一个状态
 * Q：现在的学习矩阵
 * can_go:记录下一个允许的状态
 * state：现在的状态
 * */
void routePlanning::get_go_value(float a[100][100],int can_go[10],int state)
{
    NUM=0;
    for(int i=0;i<ACTION_NUM;i++)
    {
        if(a[state][i]>=0)
        {
            can_go[NUM]=i;
            NUM++;
        }
    }
}

/*
 * 函数功能：得到下一个状态的最大奖励
 * Q：现在的学习矩阵
 * state：现在的状态
 * */
float routePlanning::get_max_value(float Q[100][100],int state)
{
    float tempmax=0;
    for(int i=0;i<ACTION_NUM;i++)
    {
        if((R[state][i]>=0)&&(Q[state][i]>tempmax))
            tempmax=Q[state][i];
    }
    return tempmax;
}

/*
 * 函数功能：得到最大奖励的下一个状态
 * Q：现在的学习矩阵
 * state：现在的状态
 * */
int routePlanning::get_max_tab(float Q[100][100],int state)
{
    float tempmax=0;
    int temptab=0;
    for(int i=0;i<ACTION_NUM;i++)
    {
        if((Q[state][i]>tempmax))
        {
            tempmax=Q[state][i];
            temptab=i;
        }
    }
    return temptab;
}
/*initial:初始状态*/
/*
 * 函数功能：Qlearning训练算法
 * initial:初始状态
 * R：训练的奖励矩阵，其中行为状态，列为动作
 * Q：学习矩阵，初始化为0
 * flag：算法收敛的标志
 * */
int routePlanning::learning_G(int initial, float R[100][100],float Q[100][100],int flag)
{
    float Q_before,Q_new;
    int a;   //是端点
    float a_2;//是回报值，非端点
    memset(initial_can_go,0,10*sizeof(int));
    get_go_value(R,initial_can_go,initial);//返回了端点和num
    a=initial_can_go[rand()%NUM];
    a_2=get_max_value(Q,a);
    /*initial_can_go数组存放了可以进行的动作*/
    /*a为随机进行的当前action*/
    /*a_2为该action下的最大反馈*/
    /*被更新的是Q(initial,a)*/
    Q_before=Q[initial][a];
    Q[initial][a]=R[initial][a]+alph*a_2;
    Q_new=Q[initial][a];

    if(Q_before==Q_new) flag++;
    else flag=0;
    if(flag==50)     return 0;
    if(Q_new == 100) initial=rand()%STATE_NUM;
    else       initial=a;
    //cout<<"initial="<<initial<<endl;
    learning_G(initial,R,Q,flag);
    return 0;
}
/*
 * 函数功能：总的QLearning调用函数
 * startPoint：起始节点
 * endPoint：截止节点
 * pathPoint：路径记录
 * */

float routePlanning::qLearning(int startPoint,int endPoint,int* pathPoint)
{
    headPoint* vexPoint=graphPoint+endPoint;
    path* linkPoint;
    int position=startPoint;

    int flag=0;
    int initial=1;
    int k;

    //初始化路劲记录
    for(int i=0;i<max_vertexes;i++){
        pathPoint[i]=-1;
    }

    //遍历目标节点相邻节点，使其R矩阵的值为100
    for(linkPoint=vexPoint->firstin;linkPoint!=NULL;)
    {
        //十字链表中i，j地位相同
        if(linkPoint->ivex==vexPoint->headPointID){
            R[linkPoint->jvex][linkPoint->ivex]=100;
            linkPoint=linkPoint->ilink;
        }else if(linkPoint->jvex==vexPoint->headPointID){
            R[linkPoint->ivex][linkPoint->jvex]=100;
            linkPoint=linkPoint->jlink;
        }else{
            cout<<"DATA ERROR";
            exit(0);
        }
    }
    //初始化Q矩阵
    for(int i=0; i<STATE_NUM; i++)
    {
        for(int j=0; j<ACTION_NUM; j++)
        {
            Q[i][j]=0;
        }
    }
    float w=0;

    //无监督训练
    learning_G(initial,R,Q,flag);

    //输出路径
    pathPoint[0]=startPoint;
    cout<<startPoint<<"->";
    for(k=1;k<max_vertexes;k++)
    {
        int j=get_max_tab(Q,position);
        pathPoint[k]=j;
        if(k!=0){
            w=w+getDistance(pathPoint[k-1],pathPoint[k])/getSpeed(pathPoint[k-1],pathPoint[k]);
        }
        cout<<j<<"->";
        if(R[position][j]==100)
        {
            cout<<"out"<<endl;
            break;
        }
        else
            position=j;
    }
    //计算错误，可能是R的初始化问题
    //会导致死循环
    if(k==max_vertexes){
        cout<<"CALCULATION ERROR!!!";
        exit(0);
    }
    //回归R矩阵的初始状态
    vexPoint=graphPoint+endPoint;
    for(linkPoint=vexPoint->firstin;linkPoint!=NULL;)
    {
        //十字链表中i，j地位相同
        if(linkPoint->ivex==vexPoint->headPointID){
            R[linkPoint->jvex][linkPoint->ivex]=linkPoint->speed/linkPoint->distance;
            linkPoint=linkPoint->ilink;
        }else if(linkPoint->jvex==vexPoint->headPointID){
            R[linkPoint->ivex][linkPoint->jvex]=linkPoint->speed/linkPoint->distance;
            linkPoint=linkPoint->jlink;
        }else{
            cout<<"DATA ERROR";
            exit(0);
        }
    }
    return w;
}
