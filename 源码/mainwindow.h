#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include <ctime>
#include <QPainterPath>
#include <qpainter.h>

#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字

namespace Ui {
class MainWindow;
}

extern int max;
extern int maxi,maxj;
extern int isOn;
extern int gameMode;
extern int player;
extern int boomNum;
extern int boomFindcishu;
extern int boomFindField;
extern int a[15][15];
extern int aa[15][15];
extern int linkFlag;
extern int hostLink;
extern int visiterLink;
extern int hostReady;
extern int visiterReady;
void vectorSet();


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int linkPushbutton(int i, int j);

    int computerGo();

    int isGameOver(int x1,int y1,int z);

    void boomFind(int i,int j);

    void fieldInit();

    void paintEvent(QPaintEvent *);

    void pushButtonSet();

    void boomPut(int n,int m);

    void visiterInput(QString str);

    void hostInput(QString str);

private slots:

    void on_chongkai_clicked();

    void on_pushButton_clicked();

    void on_pushButton_226_clicked();

    void on_pushButton_227_clicked();

    void on_pushButton_228_clicked();

    void on_saolms1_clicked();

    void on_saolms2_clicked();

    void on_saolms3_clicked();

    void ClientConnect();

    void ReadData1();

    void on_btn_server_clicked();

    void on_btn_listen_clicked();

    void on_pushButtonConnect_clicked();

    void on_fuwuqi_clicked();

    void on_kehuduan_clicked();

    void on_pushButton_229_clicked();

    void on_pushButton_230_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *t[228];
    QTcpServer* server;
    QTcpSocket* socket;
    QTcpSocket *tcpsocket;
};

#endif // MAINWINDOW_H
