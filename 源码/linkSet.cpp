#include "mainwindow.h"
#include "ui_mainwindow.h"

// ////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////
//以下开始通信程序设置/////
// //////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_btn_listen_clicked()
{
    if ( ui->btn_listen->text()=="监听")
    {
        linkFlag=0;
        //从输入框获取端口号
        int port =  ui->lineEdit_port->text().toInt();
        //侦听指定端口的所有ip
        if (!server->listen(QHostAddress::Any, port))
        {
            //若出错，则输出错误信息
            qDebug() << server->errorString();
            return;
        }
        //修改按键文字
         ui->btn_listen->setText("取消");
    }
    else
    {
        isOn=0;
        vectorSet();
        fieldInit();
        ui->lineEdit->setText("已结束连接");
        socket->write("结束");
        ui->textEdit_server->append("您：结束连接");
        hostReady=0;visiterReady=0;
        gameMode=-1;

        linkFlag=9999;
        hostLink=0;
        server->close();
        socket->close();
        socket->disconnectFromHost();
        ui->btn_listen->setText("监听");
        ui->link->setText("");
    }
}



//发送信息
void MainWindow::on_btn_server_clicked()
{
    if(linkFlag==0)
        socket->write( ui->lineEdit1->text().toUtf8().data());
    if(linkFlag==1)
        tcpsocket->write(ui->lineEdit1->text().toUtf8().data());
    ui->textEdit_server->append("您：" +ui->lineEdit1->text());
    ui->lineEdit1->setText("");
}


void MainWindow::on_pushButtonConnect_clicked()
{
    if ( ui->pushButtonConnect->text()=="连接")
    {
        //获取服务器端口和IP
        linkFlag=1;
        QString ip = ui->lineEditIP->text();
        qint16 port = ui->lineEdit_port->text().toInt();
        //主动和服务器建立连接
        tcpsocket->connectToHost(QHostAddress(ip),port);
        //修改按键文字
        ui->pushButtonConnect->setText("断开");
    }
    else
    {
        isOn=0;
        vectorSet();
        fieldInit();
        ui->lineEdit->setText("已结束连接");
        tcpsocket->write("结束");
        ui->textEdit_server->append("您：结束连接");
        hostReady=0;visiterReady=0;
        gameMode=-1;

        linkFlag=9999;
        visiterLink=0;
        tcpsocket->disconnectFromHost();
        tcpsocket->close();
        ui->pushButtonConnect->setText("连接");
    }
}


//连接客户端
void MainWindow::ClientConnect()
{
    while (server->hasPendingConnections())
    {
        //连接上后通过socket获取连接信息
        socket = server->nextPendingConnection();
        QString str = QString("[%1:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        ui->textEdit_server->append(str);
        ui->textEdit_server->append("成功连接");
        hostLink=1;
        //为连接服务器的ip
        ui->link->setText(str);
        //监听客户端是否有消息发送
        connect(socket, &QTcpSocket::readyRead, this, &MainWindow::ReadData1);
    }
}

//获取客户端信息
void MainWindow::ReadData1()
{
    QString str = QString(socket->readAll());
    ui->textEdit_server->append("客户端："+str);
    if(str=="我不玩了，哈哈")
    {
        isOn=0;
        vectorSet();
        fieldInit();
        ui->lineEdit->setText("对方已认输");
        hostReady=0;visiterReady=0;
        gameMode=-1;
    }
    if(str=="结束")
    {
        isOn=0;
        vectorSet();
        fieldInit();
        ui->lineEdit->setText("对方已结束");
        hostReady=0;visiterReady=0;
        gameMode=-1;
    }
    if(visiterReady==0)
        visiterInput(str);
}

//客户端落子
void MainWindow::visiterInput(QString str)
{
    if(str[0]=="[" and str[str.length()-1]=="]")
    {
        int k,i,j;
        k=str.indexOf(",");//7
        i=str.mid(1,k-1).toInt();
        j=str.mid(k+1,str.length()-k-2).toInt();
        t[j+i*15]->setStyleSheet
        (
            "QPushButton{"
            "background-color:blue;"
            "border-radius:19.4px;"
            "}"
         );
        t[j+i*15]->setText("●");
        int temp= isGameOver(i,j,2);
        visiterReady=1;
        if(temp==223)
        {
             ui->lineEdit->setText("对方获胜");
             isOn=0;
        }
        else
        {
            ui->lineEdit->setText("请您落子");
            player=1;
        }
    }
}

void MainWindow::hostInput(QString str)
{
    if(str[0]=="[" and str[str.length()-1]=="]")
    {
        int k,i,j;
        k=str.indexOf(",");//7
        i=str.mid(1,k-1).toInt();
        j=str.mid(k+1,str.length()-k-2).toInt();
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
        hostReady=1;
        if(temp==223)
        {
             ui->lineEdit->setText("恭喜对方获胜");
             isOn=0;
        }
        else
        {
            ui->lineEdit->setText("请您落子");
            player=2;
        }
    }
}
