#include "mainwindow.h"
#include <QApplication>

int a[15][15];
int aa[15][15];
int isOn=0;//游戏是否正在进行
int max;//最大连子
int maxi,maxj;//构成最大连子的坐标
int gameMode=-1;//游戏模式选择
int player=1;//玩家1/2
int boomNum=20;//雷数量设置
int boomFindcishu=0;//是否第一次扫雷
int boomFindField=12;
int linkFlag=9999;//通信模式
int hostLink=0;
int visiterLink=0;
int hostReady=0;
int visiterReady=0;
int main(int argc, char *argv[])
{
    vectorSet();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
