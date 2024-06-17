#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::pushButtonSet()
{
//    查询资料得到了批量添加控件
    for (int j = 0; j<15; j++)
    {
        for(int i = 0;i<15;i++)
        {
            t[i+15*j] = new QPushButton(this);
            connect(t[i+15*j],QOverload<bool>::of(&QPushButton::clicked),this,[=]{linkPushbutton(j,i);});
        }
    }
}
