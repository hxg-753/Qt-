#include "mainwindow.h"
#include "ui_mainwindow.h"

// ////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////
//以下开始五子棋程序设置/////
// //////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////

//落子判断
int MainWindow::isGameOver(int x1,int y1,int z)
{
    a[x1][y1]=z;

//判断落子位置同一行是否有五子
    int zong=1;
    //前面数量
    for(int i=y1-1;i>=0;i--)
    {
       if(a[x1][i]==z)
           zong++;
       else
           break;
    }
    //后面数量
    for(int i=y1+1;i<15;i++)
    {
        if(a[x1][i]==z)
            zong++;
        else
            break;
    }
   if(zong>=5)
        return 223;
   //落子同行数量大于等于5


   //判断落子位置同列上是否有五子
   zong=1;
   for(int i=x1-1;i>=0;i--)
   {
     if(a[i][y1]==z)
        zong++;
     else
        break;
   }
   for(int i=x1+1;i<15;i++)
   {
        if(a[i][y1]==z)
            zong++;
        else
        break;
   }
    if(zong>=5)
        return 223;
    //判断左斜线是否有五子
    zong=1;
    for(int i=1;i<5;i++)
    {
      //边界判断，最开始不写直接完蛋
      if(x1-i<0 || y1-i<0)
            break;
      if(a[x1-i][y1-i]==z)
            zong++;
      else
            break;
    }
    for(int i=1;i<5;i++)
    {
       if(x1+i>=15 || y1+i >=15)
            break;
       if(a[x1+i][y1+i]==z)
            zong++;
       else
            break;
    }
    if(zong>=5)
        return 223;
  //判断右斜线是否有五子;
    zong=1;
    for(int i=1;i<5;i++)
    {
        if(x1-i<0 || y1+i>=15)
            break;
        if(a[x1-i][y1+i]==z)
            zong++;
        else
            break;
    }

    for(int i=1;i<5;i++)
    {
        if(x1+i>=15 || y1-i<0)
            break;
        if(a[x1+i][y1-i]==z)
            zong++;
        else
            break;
     }
    if(zong>=5)
        return 223;
    return -1;
}

//电脑进行落子判断
int  MainWindow::computerGo()
{
    int t1=0;
    // 判断自己有没有四子的情况
    for(int i=0;i<15;i++)
    {
         for(int j=0;j<15;j++)
         {
            //双循环对每一个格子分析
            int heng=1;
            int shu=1;
            int zuoxie=1;
            int youxie=1;
            //格子有子
            if(a[i][j]!=0)
                continue;

            //判断横线
            for(int jishu=1;jishu<5;++jishu)
            {
               if(j-jishu<0)
                    break;
               if(a[i][j-jishu]==2)
                 heng++;
               else
                    break;
            }
             for(int jishu=1;jishu<5;++jishu)
            {
                if(j+jishu>=15)
                    break;
                if(a[i][j+jishu]==2)
                    heng++;
                else
                    break;
            }

            //判断竖线
            for(int jishu=1;jishu<5;++jishu)
            {
                if(i-jishu<0)
                   break;
                if(a[i-jishu][j]==2)
                    shu++;
                else
                    break;
            }
            for(int jishu=1;jishu<5;++jishu)
            {
                if(i+jishu>=15)
                    break;
                if(a[i+jishu][j]==2)
                    shu++;
                else
                    break;
            }

            //判断左斜线
            for(int jishu=1;jishu<5;++jishu)
            {
                if(i-jishu<0 || j-jishu<0)
                    break;
                if(a[i-jishu][j-jishu]==2)
                    zuoxie++;
                else
                    break;
            }
            for(int jishu=1;jishu<5;++jishu)
            {
              if(i+jishu>=15 || j+jishu>=15)
                 break;
              if(a[i+jishu][j+jishu]==2)
                zuoxie++;
              else
                break;
            }

            for(int jishu=1;jishu<5;++jishu)  //判断右斜线
            {
                if(i-jishu<0 || j+jishu>=15)
                    break;
                if(a[i-jishu][j+jishu]==2)
                    youxie++;
                else
                    break;
            }
            for(int jishu=1;jishu<5;++jishu)
            {
              if(i+jishu>=15 || j-jishu<0)
                break;
              if(a[i+jishu][j-jishu]==2)
                youxie++;
              else
                break;
            }
            int jishu[4]={heng,shu,zuoxie,youxie};
            int max=jishu[0];
            for (int i=0;i<4;++i)
            {
                if(jishu[i]>max)
                    max=jishu[i];
            }

            //算上这个格子有五个，落子
            if(max>=5)
            {
             a[i][j]=2;
             t[j+i*15]->setStyleSheet
             (
                 "QPushButton{"
                 "background-color:blue;"//背景色
                 "border-radius:19.4px;"
                 "}"
              );
             t[j+i*15]->setText("●");
             return 555;
            }
        }
    }
    //堵对手
     for(int i=0;i<15;i++)
     {
        for(int j=0;j<15;j++)
        {
            //对手在这个格子周子周围棋子
            int dheng=0;
            int dshu=0;
            int dzuoxie=0;
            int dyouxie=0;

        if(a[i][j]!=0)
            continue;

        for(int jishu=1;jishu<5;++jishu)
        {
            if(j-jishu<0)
               break;
            if(a[i][j-jishu]==1)
                dheng++;
            else
                break;
        }
        for(int jishu=1;jishu<5;++jishu)
        {
           if(j+jishu>=15)
              break;
           if(a[i][j+jishu]==1)
             dheng++;
           else
              break;
        }
        for(int jishu=1;jishu<5;++jishu)
        {
            if(i-jishu<0)
                break;
            if(a[i-jishu][j]==1)
                dshu++;
            else
                break;
        }

        for(int jishu=1;jishu<5;++jishu)
        {
            if(i+jishu>=15)
                break;
            if(a[i+jishu][j]==1)
                dshu++;
            else
                break;
        }
        for(int jishu=1;jishu<5;++jishu)  //判断左斜线
        {
            if(i-jishu<0 || j-jishu<0)
                break;
            if(a[i-jishu][j-jishu]==1)
                dzuoxie++;
            else
                break;
        }
        for(int jishu=1;jishu<5;++jishu)
        {
          if(i+jishu>=15 || j+jishu>=15)
                break;
          if(a[i+jishu][j+jishu]==1)
            dzuoxie++;
          else
            break;
        }
        for(int jishu=1;jishu<5;++jishu)  //判断右斜线
        {
            if(i-jishu<0 || j+jishu>=15)
                break;
            if(a[i-jishu][j+jishu]==1)
                dyouxie++;
            else
                break;
        }
        for(int jishu=1;jishu<5;++jishu)
        {
          if(i+jishu>=15 || j-jishu<0)
                break;
          if(a[i+jishu][j-jishu]==1)
            dyouxie++;
          else
            break;
        }
        int jishu[4]={dheng,dshu,dzuoxie,dyouxie};

        int max=jishu[0];
        for (int i=0;i<4;++i)
        {
            if(jishu[i]>max)
             max=jishu[i];
        }

//        对手有四子或五子，一定要堵
//        防止。。空。。的情况
        if(max>=4)
        {
           //对手填上这个格子就有五个了
           //那么堵
           a[i][j]=2;
           t[j+i*15]->setStyleSheet
           (
               "QPushButton{"
               "background-color:blue;"
               "border-radius:19.4px;"
               "}"
            );
           t[j+i*15]->setText("●");
           return 0;
        }

         //对手填上这个就有四个了，分情况，看之前堵了没有
         if(max==3)
          {
            if(max==dheng)  //水平线有三子
            {
                int jishu;
//                看看前面几个棋子
                int qian=0;
                for(jishu=1;jishu<=3;++jishu)
                {
//                    边界
                   if(j-jishu<0)
                      break;

                   if(a[i][j-jishu]==1)
                     qian++;
                   else
                     break;
                }
//                说明三个挨着
                if(qian==3)
                {
//                  落了这个边界就给堵上了
                   if(j-jishu==0)
                   {

                   }
//                   落了以后堵不上
                   else if(j-jishu-1>=0)
                   {
//                      之前没有堵
                     if(a[i][j-jishu-1]!=2)
                     {
                       a[i][j]=2;
                       t[j+i*15]->setStyleSheet
                       (
                           "QPushButton{"
                           "background-color:blue;"
                           "border-radius:19.4px;"
                           "}"
                        );
                       t[j+i*15]->setText("●");
                       return 0;
                     }
                   }
                }
                //前二后一
                else if(qian==2)
                {
//                    落了能堵上
                    if(j-jishu==0)
                    {

                    }
 //                   落了以后堵不上
                    else if(j-jishu>=1)
                    {
 //                      之前没有堵
                      if(a[i][j-jishu-1]!=2)
                      {
                        a[i][j]=2;
                        t[j+i*15]->setStyleSheet
                        (
                            "QPushButton{"
                            "background-color:blue;"
                            "border-radius:19.4px;"
                            "}"
                         );
                        t[j+i*15]->setText("●");
                        return 0;
                      }
                    }

                }
                //前一后二
                else if(qian==1)
                {
//                    落了边界能堵上
                      if(j-jishu==0)
                      {

                      }
//                    落了以后堵不上
                      else if(j-jishu>=1)
                      {
                     //之前没有堵
                          if(a[i][j-jishu-1]!=2)
                          {
                              a[i][j]=2;
                              t[j+i*15]->setStyleSheet
                              (
                                  "QPushButton{"
                                  "background-color:blue;"
                                  "border-radius:19.4px;"
                                  "}"
                               );
                              t[j+i*15]->setText("●");
                              return 0;
                          }
                      }
                }
            } //水平线三子情况判断结束
            else if(max==dshu) //竖直线有三子的情况
            {
                int jishu;
                int qian=0;
                for(jishu=1;jishu<=3;++jishu)
                {
                   if(i-jishu<0)
                        break;
                   if(a[i-jishu][j]==1)
                     qian++;
                   else
                        break;
                }
                if(qian==3)
                {
                   if(i-jishu==0)
                   {

                   }
                   else if(i-jishu-1>=0)
                   {
                        if(a[i-jishu-1][j]!=2)
                        {
                           a[i][j]=2;
                           t[j+i*15]->setStyleSheet
                           (
                               "QPushButton{"
                               "background-color:blue;"
                               "border-radius:19.4px;"
                               "}"
                            );
                           t[j+i*15]->setText("●");
                           return 0;
                        }
                   }
                }
                else if(qian==2)
                {
                    if(i-jishu==0)
                    {

                    }
                    else if(i-jishu-1>=0)
                    {
                         if(a[i-jishu-1][j]!=2)
                         {
                            a[i][j]=2;
                            t[j+i*15]->setStyleSheet
                            (
                                "QPushButton{"
                                "background-color:blue;"
                                "border-radius:19.4px;"
                                "}"
                             );
                            t[j+i*15]->setText("●");
                            return 0;
                         }
                    }
                }
                else if(qian==1)
                {
                    if(i-jishu==0)
                    {

                    }
                    else if(i-jishu-1>=0)
                    {
                         if(a[i-jishu-1][j]!=2)
                         {
                            a[i][j]=2;
                            t[j+i*15]->setStyleSheet
                            (
                                "QPushButton{"
                                "background-color:blue;"
                                "border-radius:19.4px;"
                                "}"
                             );
                            t[j+i*15]->setText("●");
                            return 0;
                         }
                    }
                }
            }  //竖直线有三子情况判断结束
            else if(max==dzuoxie)  //左斜线有三子的情况
            {
                int jishu;
                int qian=0;
                for(jishu=1;jishu<=3;++jishu)
                {
                   if(i-jishu<0 || j-jishu<0)
                      break;
                   if(a[i-jishu][j-jishu]==1)
                     qian++;
                   else
                     break;
                }
                if(qian==3)
                {
                   if(i-jishu==0 || j-jishu==0)
                   {

                   }
                   else if(i-jishu-1>=0 and j-jishu-1>=0)
                    {
                        if(a[i-jishu-1][j-jishu-1]!=2)
                        {
                            a[i][j]=2;
                            t[j+i*15]->setStyleSheet
                            (
                                "QPushButton{"
                                "background-color:blue;"
                                "border-radius:19.4px;"
                                "}"
                             );
                            t[j+i*15]->setText("●");
                            return 0;
                        }
                    }
                 }
                else if(qian==2)
                {
                    if(i-jishu==0 || j-jishu==0)
                    {

                    }
                    else if(i-jishu-1>=0 and j-jishu-1>=0)
                     {
                         if(a[i-jishu-1][j-jishu-1]!=2)
                         {
                             a[i][j]=2;
                             t[j+i*15]->setStyleSheet
                             (
                                 "QPushButton{"
                                 "background-color:blue;"
                                 "border-radius:19.4px;"
                                 "}"
                              );
                             t[j+i*15]->setText("●");
                             return 0;
                         }
                     }
                }
                else if(qian==1)
                {
                    if(i-jishu==0 || j-jishu==0)
                    {

                    }
                    else if(i-jishu-1>=0 and j-jishu-1>=0)
                     {
                         if(a[i-jishu-1][j-jishu-1]!=2)
                         {
                             a[i][j]=2;
                             t[j+i*15]->setStyleSheet
                             (
                                 "QPushButton{"
                                 "background-color:blue;"
                                 "border-radius:19.4px;"
                                 "}"
                              );
                             t[j+i*15]->setText("●");
                             return 0;
                         }
                     }
                }
            }  //左斜线三子情况判断结束
          else if(max==dyouxie) //判断右斜线有三子的情况
          {
                 int jishu;
                 int qian=0;
                 for(jishu=1;jishu<=3;++jishu)
                 {
                   //  tpx1=0;
                   if(i-jishu<0 || j+jishu >14)
                     break;
                   if(a[i-jishu][j+jishu]==1)
                     qian++;
                   else
                     break;
                 }

                 if(qian==3)
                 {
                   if(i-jishu==0 || j+jishu==14)
                   {

                   }
                   else if(i-jishu-1>=0 and j+jishu+1<=14)
                   {
                     if(a[i-jishu-1][j+jishu+1]!=2)
                     {
                       a[i][j]=2;
                       t[j+i*15]->setStyleSheet
                       (
                           "QPushButton{"
                           "background-color:blue;"
                           "border-radius:19.4px;"
                           "}"
                        );
                       t[j+i*15]->setText("●");
                       return 0;
                     }
                   }
                 }

                 else if(qian==2)
                 {
                     if(i-jishu==0 || j+jishu==14)
                     {

                     }
                     else if(i-jishu-1>=0 and j+jishu+1<=14)
                     {
                       if(a[i-jishu-1][j+jishu+1]!=2)
                       {
                         a[i][j]=2;
                         t[j+i*15]->setStyleSheet
                         (
                             "QPushButton{"
                             "background-color:blue;"
                             "border-radius:19.4px;"
                             "}"
                          );
                         t[j+i*15]->setText("●");
                         return 0;
                       }
                     }
                 }
                 else if(qian==1)
                 {
                     if(i-jishu==0 || j+jishu==14)
                     {

                     }
                     else if(i-jishu-1>=0 and j+jishu+1<=14)
                     {
                       if(a[i-jishu-1][j+jishu+1]!=2)
                       {
                         a[i][j]=2;
                         t[j+i*15]->setStyleSheet
                         (
                             "QPushButton{"
                             "background-color:blue;"
                             "border-radius:19.4px;"
                             "}"
                          );
                         t[j+i*15]->setText("●");
                         return 0;
                       }
                     }
                 }
          } //右斜线三子情况判断结束
        }  //对手有三子的情况

        }
    }
     //判断对手连子情况结束，开始连自己五子
    for(int i=0;i<15;i++)
    {
       for(int j=0;j<15;j++)
       {
         if(a[i][j]==2)
            t1++;
       }
    }
//还没有开始下
    if(t1==0)
    {
        if(a[7][7]==0)
        {
            a[7][7]=2;
            t[7+7*15]->setStyleSheet
            (
                "QPushButton{"
                "background-color:blue;"
                "border-radius:19.4px;"
                "}"
             );
            t[7+7*15]->setText("●");
        }
        else
        {
            a[6][6]=2;
            t[6+6*15]->setStyleSheet
            (
                "QPushButton{"
                "background-color:blue;"
                "border-radius:19.4px;"
                "}"
             );
            t[6+6*15]->setText("●");
        }
        return 0;
    }
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
//            求出每一个格子的最大连子数，然后下最大的那个
             int heng=0;
             int shu=0;
             int zuoxie=0;
             int youxie=0;
             if(a[i][j]!=0)
                continue;
             for(int jishu=1;jishu<5;++jishu)
             {
               if(j-jishu<0)
                    break;
               if(a[i][j-jishu]==2)
                 heng++;
               else
                break;
            }
            for(int jishu=1;jishu<5;++jishu)
            {
                if(j+jishu>=15)
                    break;
                if(a[i][j+jishu]==2)
                    heng++;
                else
                    break;
            }



            for(int jishu=1;jishu<5;++jishu)
            {
                if(i-jishu<0)
                   break;
                if(a[i-jishu][j]==2)
                    shu++;
                else
                    break;
            }
            for(int jishu=1;jishu<5;++jishu)
            {
               if(i+jishu>=15)
                    break;
                if(a[i+jishu][j]==2)
                    shu++;
                else
                    break;
            }



              for(int jishu=1;jishu<5;++jishu)
                {
                   if(i-jishu<0 || j-jishu<0)
                     break;
                    if(a[i-jishu][j-jishu]==2)
                        zuoxie++;
                    else
                        break;

                }

            for(int jishu=1;jishu<5;++jishu)
            {
              if(i+jishu>=15 || j+jishu>=15)
                 break;
              if(a[i+jishu][j+jishu]==2)
                zuoxie++;
              else
                break;
            }



            for(int jishu=1;jishu<5;++jishu)
              {
                if(i-jishu<0 || j+jishu>=15)
                    break;
                if(a[i-jishu][j+jishu]==2)
                    youxie++;
                else
                    break;
              }
            for(int jishu=1;jishu<5;++jishu)
            {
              if(i+jishu>=15 || j-jishu<0)
                break;
              if(a[i+jishu][j-jishu]==2)
                youxie++;
              else
                break;
            }

            int jishu[4]={heng,shu,zuoxie,youxie};
            int jubumax=jishu[0];
            for (int i=0;i<4;++i)
            {
                if(jishu[i]>jubumax)
                 jubumax=jishu[i];
            }
            if(jubumax>=4)
            {
             a[i][j]=2;
             return 555;
            }
            if(jubumax>max)
            {
              max=jubumax;
              maxi=i;
              maxj=j;
            }
         }
    }
    max=0;
    a[maxi][maxj]=2;
    t[maxi*15+maxj]->setStyleSheet
    (
        "QPushButton{"
        "background-color:blue;"
        "border-radius:19.4px;"
        "}"
     );
    t[maxi*15+maxj]->setText("●");
    maxi=-255;
    maxj=-255;
    return 0;
}
