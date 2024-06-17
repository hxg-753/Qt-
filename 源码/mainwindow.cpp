#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Qt五子棋+扫雷+聊天软件");

    server = new QTcpServer(this);
    socket = NULL;
    socket = new QTcpSocket(this);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::ClientConnect);
    tcpsocket = NULL;
    //分配空间，指定父对象
    tcpsocket = new QTcpSocket(this);

    connect(tcpsocket,&QTcpSocket::connected,
            [=]()
            {
                ui->textEdit_server->setText("成功和服务器建立连接");
                visiterLink=1;

            });
    connect(tcpsocket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray array = tcpsocket->readAll();
        ui->textEdit_server->append("服务器："+array);
        if(array=="我不玩了，哈哈")
        {
            isOn=0;
            vectorSet();
            fieldInit();
            ui->lineEdit->setText("对方已认输");
            gameMode=-1;
            hostReady=0;visiterReady=0;
        }
        if(array=="结束")
        {
            isOn=0;
            vectorSet();
            fieldInit();
            ui->lineEdit->setText("对方已结束");
            gameMode=-1;
            hostReady=0;visiterReady=0;
            linkFlag=9999;
            visiterLink=0;
            tcpsocket->disconnectFromHost();
            tcpsocket->close();
            ui->pushButtonConnect->setText("连接");
        }
        if(hostReady==0)
            hostInput(array);
    });

    pushButtonSet();
    t[225]=ui->saolms1;
    t[226]=ui->saolms2;
    t[227]=ui->saolms3;
    ui->lineEdit_port->setGeometry(0,0,0,0);
    ui->btn_listen->setGeometry(0,0,0,0);
    ui->label->setGeometry(0,0,0,0);
    ui->link->setGeometry(0,0,0,0);
    ui->textEdit_server->setGeometry(0,0,0,0);
    ui->lineEdit1->setGeometry(0,0,0,0);
    ui->btn_server->setGeometry(0,0,0,0);
    ui->lineEditIP->setGeometry(0,0,0,0);
    ui->pushButtonConnect->setGeometry(0,0,0,0);
    ui->background2->setGeometry(1000,0,301,761);
    fieldInit();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));//设置字体
    for (int i=0;i<15;i++)
    {
        painter.drawLine(i*50+40,40,i*50+40,740);
    }
    for (int i=0;i<15;i++)
    {
        painter.drawLine(40,i*50+40,740,i*50+40);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    server->close();
    server->deleteLater();
}
// /////////////////////////////////////////////////////////////////////////////////
//为所有的按钮进行初始化
//这个简单多了(￣▽￣)／
// /////////////////////////////////////////////////////////////////////////////////
void MainWindow:: fieldInit()
{
    ui->background->setGeometry(0,0,0,0);
    ui->background->setStyleSheet("background-color:white");
    for(int j=0;j<15;++j)
    {
        for(int i=0;i<15;++i)
        {
            t[i+15*j]->setText(" ");
            t[i+15*j]->setGeometry(20+i*50,20+j*50,40,40);
            t[i+15*j]->setStyleSheet
            (
                "QPushButton{"
                "background-color:rgba(238,220,200,0);"
                "border-radius:19.4px;"
                "}"
             );
        }
    }
    ui->lineEdit->setText("欢迎使用");
    t[225]->setGeometry(0,0,0,0);
    t[226]->setGeometry(0,0,0,0);
    t[227]->setGeometry(0,0,0,0);
//QString::number(1+i+j*15)（测试用，显示按键序号）
}

//全局函数  棋盘构建  用来把全局变量数组a初始化
//PS：实在不知道应该放在哪一个类里
void vectorSet()
{
     for(int i=0;i<15;i++)
     {
         for(int j=0;j<15;j++)
         {
           a[i][j]=0;
         }
     }
}

//所有的按键执行的都是这货，判断落子以及游戏状况
int MainWindow::linkPushbutton(int i, int j)
{
//kaigaun判断游戏是否进行中，gameMode判断是什么游戏
    if(isOn==1 and gameMode==1)
    {
        if(a[i][j]!=0)
            return 0;
        else
        {
                ui->lineEdit->setText("落子成功");
                t[j+i*15]->setStyleSheet
                (
                    "QPushButton{"
                    "background-color:red;"
                    "border-radius:19.4px;"
                    "}"
                 );
                t[j+i*15]->setText("○");
                int temp= isGameOver(i,j,1);
                if(temp==223)
                {
                     ui->lineEdit->setText("恭喜玩家获胜");
                     isOn=0;
                }
                else
                {
                    temp=computerGo();
                    if(temp==555)
                    {
                        ui->lineEdit->setText("电脑获胜");
                        isOn=0;
                    }
                    else
                        ui->lineEdit->setText("请玩家落子");
                }
                return 1;
        }
    }
    else if(gameMode==-1)
        ui->lineEdit->setText("请选择模式");
    else if(gameMode==2 and isOn==1)
    {
        if(player==1)
        {
            if(a[i][j]!=0)
                return 0;
            else
            {
                    ui->lineEdit->setText("落子成功");
                    t[j+i*15]->setStyleSheet
                    (
                        "QPushButton{"
                        "background-color:red;"
                        "border-radius:19.4px;"
                        "}"
                     );
                    t[j+i*15]->setText("○");
                    int temp= isGameOver(i,j,1);
                    if(temp==223)
                    {
                         ui->lineEdit->setText("恭喜玩家1获胜");
                         isOn=0;
                    }
                    else
                    {
                        ui->lineEdit->setText("请玩家2落子");
                        player=2;
                    }
              }
          }
        else if(player==2)
        {
            if(a[i][j]!=0)
                return 0;
            else
            {
                    ui->lineEdit->setText("落子成功");
                    t[j+i*15]->setStyleSheet
                    (
                        "QPushButton{"
                        "background-color:blue;"
                        "border-radius:19.4px;"
                        "}"
                     );
                    t[j+i*15]->setText("●");
                    int temp= isGameOver(i,j,2);
                    if(temp==223)
                    {
                         ui->lineEdit->setText("恭喜玩家2获胜");
                         isOn=0;
                    }
                    else
                    {
                        ui->lineEdit->setText("请玩家1落子");
                        player=1;
                    }
              }
          }
    }
    else if(gameMode==3 and isOn==1)
    {
        if(boomFindcishu==0)
        {
            boomPut(i,j);
            ui->lineEdit->setText("当前为扫雷，已选规格");
            boomFind(i,j);
            boomFindcishu=1;
        }
        else
            boomFind(i,j);
    }






    else if(gameMode==4 and isOn==1)
    {
        if(player==1)
        {
            if(a[i][j]!=0)
                return 0;
            else
            {
                    ui->lineEdit->setText("落子成功");
                    t[j+i*15]->setStyleSheet
                    (
                        "QPushButton{"
                        "background-color:red;"
                        "border-radius:19.4px;"
                        "}"
                     );
                    t[j+i*15]->setText("○");
                    int temp= isGameOver(i,j,1);
                    visiterReady=0;
                    if(temp==223)
                    {
                         ui->lineEdit->setText("恭喜您获胜");
                         isOn=0;
                         QString ii = QString::number(i);
                         QString jj = QString::number(j);
                         QString wz="["+ii+","+jj+"]";
                         socket->write(wz.toUtf8().data());
                         ui->textEdit_server->append("您："+wz);
                    }
                    else
                    {
                        ui->lineEdit->setText("请对方落子");
                        player=2;
                        QString ii = QString::number(i);
                        QString jj = QString::number(j);
                        QString wz="["+ii+","+jj+"]";
                        socket->write(wz.toUtf8().data());
                        ui->textEdit_server->append("您："+wz);
                    }
              }
          }
    }

    else if(gameMode==5 and isOn==1)
    {

        if(player==2)
        {
            if(a[i][j]!=0)
                return 0;
            else
            {
                    ui->lineEdit->setText("落子成功");
                    t[j+i*15]->setStyleSheet
                    (
                        "QPushButton{"
                        "background-color:blue;"
                        "border-radius:19.4px;"
                        "}"
                     );
                    t[j+i*15]->setText("●");
                    int temp= isGameOver(i,j,2);
                    hostReady=0;
                    if(temp==223)
                    {
                         ui->lineEdit->setText("恭喜您获胜");
                         isOn=0;
                         QString ii = QString::number(i);
                         QString jj = QString::number(j);
                         QString wz="["+ii+","+jj+"]";
                         tcpsocket->write(wz.toUtf8().data());
                         ui->textEdit_server->append("您："+wz);
                    }
                    else
                    {
                        ui->lineEdit->setText("请对方落子");
                        player=1;
                        QString ii = QString::number(i);
                        QString jj = QString::number(j);
                        QString wz="["+ii+","+jj+"]";
                        tcpsocket->write(wz.toUtf8().data());
                        ui->textEdit_server->append("您："+wz);
                    }
              }
          }
    }

    return 1;
}


//重开当前模式
void MainWindow::on_chongkai_clicked()
{

    if(gameMode==1)
    {
        isOn=1;
        vectorSet();
        fieldInit();
        gameMode=1;
        isOn=1;
        ui->lineEdit->setText("当前为与电脑对战");
    }
    if(gameMode==2)
    {
        isOn=1;
        vectorSet();
        fieldInit();
        gameMode=2;
        isOn=1;
        ui->lineEdit->setText("红色玩家1，蓝色玩家2");
    }
    if(gameMode==3)
    {
        isOn=1;
        vectorSet();
        for (int i=0;i<15;i++)
        {
            for (int j=0;j<15;j++)
            {
                aa[i][j]=0;
            }
        }
        for(int j=0;j<boomFindField;++j)
        {
            for(int i=0;i<boomFindField;++i)
            {
                t[i+15*j]->setText(" ");
                t[i+15*j]->setStyleSheet("background-color:black");
            }
        }
        gameMode=3;
        isOn=1;
        ui->lineEdit->setText("当前为扫雷,可选择规格");
        boomFindcishu=0;
    }
    if(gameMode==-1)
        ui->lineEdit->setText("未选择模式");
}
//与电脑对战模式
void MainWindow::on_pushButton_clicked()
{
    if(isOn==0)
    {
        t[225]->setGeometry(0,0,0,0);
        t[226]->setGeometry(0,0,0,0);
        t[227]->setGeometry(0,0,0,0);
        vectorSet();
        fieldInit();
        gameMode=1;
        isOn=1;
        ui->lineEdit->setText("当前为与电脑对战");
    }
    else
    {
        ui->lineEdit->setText("请完成当前游戏");
    }
}
//与玩家对战模式
void MainWindow::on_pushButton_226_clicked()
{
    if(isOn==0)
    {
        t[225]->setGeometry(0,0,0,0);
        t[226]->setGeometry(0,0,0,0);
        t[227]->setGeometry(0,0,0,0);
        vectorSet();
        fieldInit();
        gameMode=2;
        isOn=1;
        ui->lineEdit->setText("红色玩家1，蓝色玩家2");
    }
    else
    {
        ui->lineEdit->setText("请完成当前游戏");
    }
}
//服务器模式
void MainWindow::on_fuwuqi_clicked()
{
    ui->background2->setGeometry(0,0,0,0);
    ui->pushButton_230->setText("隐藏网络模块");
    ui->lineEdit_port->setGeometry(0,0,0,0);
    ui->btn_listen->setGeometry(0,0,0,0);
    ui->label->setGeometry(0,0,0,0);
    ui->link->setGeometry(0,0,0,0);
    ui->textEdit_server->setGeometry(0,0,0,0);
    ui->lineEdit1->setGeometry(0,0,0,0);
    ui->btn_server->setGeometry(0,0,0,0);
    ui->lineEditIP->setGeometry(0,0,0,0);
    ui->pushButtonConnect->setGeometry(0,0,0,0);

    ui->lineEdit_port->setGeometry(1010,20,221,31);
    ui->btn_listen->setGeometry(1250,10,41,41);
    ui->label->setGeometry(1010,70,70,30);
    ui->link->setGeometry(1080,70,210,30);
    ui->textEdit_server->setGeometry(1010,110,281,511);
    ui->lineEdit1->setGeometry(1010,660,211,41);
    ui->btn_server->setGeometry(1250,660,41,41);
}
//客户端模式
void MainWindow::on_kehuduan_clicked()
{
    ui->background2->setGeometry(0,0,0,0);
    ui->pushButton_230->setText("隐藏网络模块");
    ui->lineEdit_port->setGeometry(0,0,0,0);
    ui->btn_listen->setGeometry(0,0,0,0);
    ui->label->setGeometry(0,0,0,0);
    ui->link->setGeometry(0,0,0,0);
    ui->textEdit_server->setGeometry(0,0,0,0);
    ui->lineEdit1->setGeometry(0,0,0,0);
    ui->btn_server->setGeometry(0,0,0,0);
    ui->lineEditIP->setGeometry(0,0,0,0);
    ui->pushButtonConnect->setGeometry(0,0,0,0);

    ui->lineEditIP->setGeometry(1010,20,221,31);
    ui->lineEdit_port->setGeometry(1010,70,221,31);
    ui->pushButtonConnect->setGeometry(1250,40,41,41);
    ui->textEdit_server->setGeometry(1010,120,281,521);
    ui->lineEdit1->setGeometry(1010,660,211,41);
    ui->btn_server->setGeometry(1250,660,41,41);
}

//网络对战
void MainWindow::on_pushButton_229_clicked()
{
    if(isOn==0)
    {
        if(hostLink==0 and visiterLink==0)
            ui->lineEdit->setText("请先连接");
        else if(hostLink==1 and visiterLink==0)
        {
            vectorSet();
            fieldInit();
            gameMode=4;
            isOn=1;
            ui->lineEdit->setText("我方红色先行");
            socket->write("我方已准备");
            ui->textEdit_server->append("我方已准备");
            player=1;
            hostReady=0;visiterReady=0;
        }
        else if(hostLink==0 and visiterLink==1)
        {
            vectorSet();
            fieldInit();
            gameMode=5;
            isOn=1;
            ui->lineEdit->setText("对方红色先行");
            tcpsocket->write("我方已准备");
            ui->textEdit_server->append("我方已准备");
            player=1;
            hostReady=0;visiterReady=0;
        }
        else
        {
            ui->lineEdit->setText("不可一对多");
        }
    }
    else
    {
        ui->lineEdit->setText("请完成当前游戏");
    }
}


//扫雷模式
void MainWindow::on_pushButton_228_clicked()
{
    if(isOn==0)
    {
        ui->background->setGeometry(40,40,700,700);
        ui->background->setStyleSheet("background-color:white");
        ui->background->lower();
        t[225]->setGeometry(80,745,121,31);
        t[226]->setGeometry(280,745,121,31);;
        t[227]->setGeometry(480,745,121,31);
        gameMode=3;
        isOn=1;
        ui->lineEdit->setText("当前为扫雷,可选择规格");

        for(int j=0;j<12;++j)
        {
            for(int i=0;i<12;++i)
            {
                t[i+15*j]->setText(" ");
                t[i+15*j]->setStyleSheet("background-color:black");
                t[i+15*j]->setGeometry(90+i*50,90+j*50,48,48);
            }
        }
        for(int j=12;j<15;++j)
        {
            for(int i=0;i<15;++i)
            {
                t[i+15*j]->setGeometry(0,0,0,0);
            }
        }
        for(int j=0;j<15;++j)
        {
            for(int i=12;i<15;++i)
            {
                t[i+15*j]->setGeometry(0,0,0,0);
            }
        }
        vectorSet();
        boomFindcishu=0;
    }
    else
        ui->lineEdit->setText("请完成当前游戏");
}
void MainWindow::on_saolms1_clicked()
{
    if(isOn==1 and gameMode==3)
    {
        if(boomFindcishu==0)
        {
            isOn=1;
            boomFindField=9;
            boomNum=10;
            for(int j=0;j<boomFindField;++j)
            {
                for(int i=0;i<boomFindField;++i)
                {
                    t[i+15*j]->setText(" ");
                    t[i+15*j]->setStyleSheet("background-color:black");
                    t[i+15*j]->setGeometry(120+i*60,120+j*60,58,58);
                }
            }
            for(int j=boomFindField;j<15;++j)
            {
                for(int i=0;i<15;++i)
                {
                    t[i+15*j]->setGeometry(0,0,0,0);
                }
            }
            for(int j=0;j<15;++j)
            {
                for(int i=boomFindField;i<15;++i)
                {
                    t[i+15*j]->setGeometry(0,0,0,0);
                }
            }
            vectorSet();
            ui->lineEdit->setText("9x9/10");
        }
        else
            ui->lineEdit->setText("请完成当前游戏");
    }
    else
        ui->lineEdit->setText("点玩扫雷后选择");
}
void MainWindow::on_saolms2_clicked()
{
    if(isOn==1 and gameMode==3)
    {
        if( boomFindcishu==0)
        {
            isOn=1;
            boomFindField=12;
            boomNum=20;
            for(int j=0;j<boomFindField;++j)
            {
                for(int i=0;i<boomFindField;++i)
                {
                    t[i+15*j]->setText(" ");
                    t[i+15*j]->setStyleSheet("background-color:black");
                    t[i+15*j]->setGeometry(90+i*50,90+j*50,48,48);
                }
            }
            for(int j=boomFindField;j<15;++j)
            {
                for(int i=0;i<15;++i)
                {
                    t[i+15*j]->setGeometry(0,0,0,0);
                }
            }
            for(int j=0;j<15;++j)
            {
                for(int i=boomFindField;i<15;++i)
                {
                    t[i+15*j]->setGeometry(0,0,0,0);
                }
            }
            vectorSet();
            ui->lineEdit->setText("12x12/20");
        }
        else
            ui->lineEdit->setText("请完成当前游戏");
    }
    else
        ui->lineEdit->setText("点玩扫雷后选择");
}

void MainWindow::on_saolms3_clicked()
{
    if(isOn==1 and gameMode==3)
    {
        if(boomFindcishu==0)
        {
            isOn=1;
            boomFindField=12;
            boomNum=35;
            for(int j=0;j<boomFindField;++j)
            {
                for(int i=0;i<boomFindField;++i)
                {
                    t[i+15*j]->setText(" ");
                    t[i+15*j]->setStyleSheet("background-color:black");
                    t[i+15*j]->setGeometry(90+i*50,90+j*50,48,48);
                }
            }
            for(int j=boomFindField;j<15;++j)
            {
                for(int i=0;i<15;++i)
                {
                    t[i+15*j]->setGeometry(0,0,0,0);
                }
            }
            for(int j=0;j<15;++j)
            {
                for(int i=boomFindField;i<15;++i)
                {
                    t[i+15*j]->setGeometry(0,0,0,0);
                }
            }         
           vectorSet();
            ui->lineEdit->setText("12x12/35");
        }
        else
            ui->lineEdit->setText("请完成当前游戏");
    }
    else
         ui->lineEdit->setText("点玩扫雷后选择");
}

//强制结束当前游戏
void MainWindow::on_pushButton_227_clicked()
{
    isOn=0;
    vectorSet();
    fieldInit();
    ui->lineEdit->setText("已结束，可选择模式");
    if(gameMode==4)
    {
        socket->write("我不玩了，哈哈");
        ui->textEdit_server->append("您：我不玩了，哈哈");
        hostReady=0;visiterReady=0;
    }
    if(gameMode==5)
    {
        tcpsocket->write("我不玩了，哈哈");
        ui->textEdit_server->append("您：我不玩了，哈哈");
        hostReady=0;visiterReady=0;
    }
    gameMode=-1;
}

void MainWindow::on_pushButton_230_clicked()
{
    if ( ui->pushButton_230->text()=="隐藏网络模块")
    {
         ui->background2->setGeometry(1000,0,301,761);
         ui->pushButton_230->setText("显示网络模块");
    }
    else
    {
        ui->background2->setGeometry(0,0,0,0);
        ui->pushButton_230->setText("隐藏网络模块");
    }
}
