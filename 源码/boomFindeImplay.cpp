#include "mainwindow.h"
#include "ui_mainwindow.h"

// ////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////
//以下开始扫雷程序设置/////
// //////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////

//判断一个格子周围几个雷
int boomNumNear(int i,int j)
{
    int z=boomFindField-1;
    int zong=0;
    if(i-1>=0)
    {
        if(a[i-1][j]==3)
            zong++;
    }
    if(i-1>=0 and j-1>=0)
    {
        if(a[i-1][j-1]==3)
            zong++;
    }
    if(i-1>=0 and j+1<=z)
    {
        if(a[i-1][j+1]==3)
            zong++;
    }
    if(j-1>=0)
    {
        if(a[i][j-1]==3)
            zong++;
    }
    if(j+1<=z)
    {
        if(a[i][j+1]==3)
            zong++;
    }
    if(i+1<=z)
    {
        if(a[i+1][j]==3)
            zong++;
    }
    if(i+1<=z and j-1>=0)
    {
        if(a[i+1][j-1]==3)
            zong++;
    }
    if(i+1<=z and j+1<=z)
    {
        if(a[i+1][j+1]==3)
            zong++;
    }
    return zong;
}

//用来显示格子周围几个雷
void boomFind2()
{
    int z=boomFindField;
   for(int i=0;i<z;i++)
    {
        for(int j=0;j<z;j++)
        {
          aa[i][j]=0;
        }
    }
//   是雷标价505（sos）
    for(int i=0;i<z;i++)
    {
      for(int j=0;j<z;j++)
      {
        if(a[i][j]==3)
            aa[i][j]=505;
        else
        {
            aa[i][j]=boomNumNear(i,j);
        }
      }
    }
}

void clickLocalClear(int i,int j)
{
    int z=boomFindField;
    if(aa[i][j]==0)
    {
        a[i][j]=1000;
        if(i-1>=0)
        {
            if(a[i-1][j]!=1000)
            {
                a[i-1][j]=1000;
                clickLocalClear(i-1,j);
            }
        }
        if(i-1>=0 and j-1>=0)
        {
            if(a[i-1][j-1]!=1000)
            {
                a[i-1][j-1]=1000;
                clickLocalClear(i-1,j-1);
            }
        }
        if(i-1>=0 and j+1<z)
        {
            if(a[i-1][j+1]!=1000)
            {
                a[i-1][j+1]=1000;
                clickLocalClear(i-1,j+1);
            }
        }
        if(j-1>=0)
        {
            if(a[i][j-1]!=1000)
            {
                a[i][j-1]=1000;
                clickLocalClear(i,j-1);
            }
        }
        if(j+1<z)
        {
            if(a[i][j+1]!=1000)
            {
                a[i][j+1]=1000;
                clickLocalClear(i,j+1);
            }
        }
        if(i+1<z)
        {
            if(a[i+1][j]!=1000)
            {
                a[i+1][j]=1000;
                clickLocalClear(i+1,j);
            }
        }
        if(i+1<z and j-1>=0)
        {
            if(a[i+1][j-1]!=1000)
            {
                a[i+1][j-1]=1000;
                clickLocalClear(i+1,j-1);
            }
        }
        if(i+1<z and j+1<z)
        {
            if(a[i+1][j+1]!=1000)
            {
                a[i+1][j+1]=1000;
                clickLocalClear(i+1,j+1);
            }
        }
    }
}

void MainWindow::boomFind(int i,int j)
{
    int z=boomFindField;
    //触雷
    if(a[i][j]==3)
    {
        isOn=0;
        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            {
                if(a[i][j]!=3)
                {
                    if(aa[i][j]!=0)
                        t[j+i*15]->setText(QString::number(aa[i][j]));
                    t[j+i*15]->setStyleSheet("background-color:green");
                }

                else if(a[i][j]==3)
                {
                    t[j+i*15]->setText("雷");
                    t[j+i*15]->setStyleSheet("background-color:red");
                }
            }

        }
        ui->lineEdit->setText("游戏结束");
        isOn=0;
        boomFindcishu=0;
    }
    else
    {
        int tongji=0;
        z=boomFindField;
//        把a这个格子激发1000
        a[i][j]=1000;
        clickLocalClear(i,j);
//把激发的格子打出来
        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            {
                if(a[i][j]==1000)
                {
                    t[j+i*15]->setStyleSheet("background-color:green");
                    if(aa[i][j]!=0)
                        t[j+i*15]->setText(QString::number(aa[i][j]));
                    tongji++;
                }
            }
        }
//不是雷的格子全点了出来，赢
        if(tongji+boomNum==boomFindField*boomFindField)
        {
            isOn=0;
            for(int i=0;i<z;i++)
            {
                for(int j=0;j<z;j++)
                {
                    if(a[i][j]!=3)
                    {
                        if(aa[i][j]!=0)
                            t[j+i*15]->setText(QString::number(aa[i][j]));
                        t[j+i*15]->setStyleSheet("background-color:green");
                    }

                    else if(a[i][j]==3)
                    {
                        t[j+i*15]->setText("雷");
                        t[j+i*15]->setStyleSheet("background-color:blue");
                    }
                }

            }
            ui->lineEdit->setText("赢");
            isOn=0;
            boomFindcishu=0;
        }
    }
}

void MainWindow::boomPut(int n,int m)
{
    srand(time(0));
    for (int i=0;i<boomNum;)
    {
        int j=rand()%boomFindField;
        int k=rand()%boomFindField;
        if((j>n+1 or j<n-1) or (k>m+1 or k <m-1))
        {
            if(a[j][k]==0 )
            {
                a[j][k]=3;
                ++i;
            }
        }
        boomFind2();
    }

}
