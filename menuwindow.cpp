#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "snake.h"
#include <QLabel>
#include <QDialog>
#include <QPushButton>

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    //this->resize(750,520);

    this->setStyleSheet("QPushButton{color:rgb(0,0,0);"
                                                      "}");
            ui->pushButton_2->setParent(this);ui->pushButton->setParent(this);ui->pushButton_3->setParent(this);ui->pushButton_4->setParent(this);
            ui->pushButton_2->setText(tr("游戏开始"));
            ui->pushButton->setText(tr("游戏帮助"));
            ui->pushButton_3->setText(tr("关于游戏"));
            //帮助文档：玩家通过上下左右方向键来控制蛇的游动方向，通过鼠标点击游戏上方的暂停、返回主菜单以及继续符号来控制游戏的暂停和开始以及返回主菜单，其他规则和一般贪吃蛇规则相同，然而难度有点低，不适合大学生进行娱乐。
            //关于文档：本游戏为简化版的贪吃蛇，游戏难度对智商要求不高，实现的功能很简单，包括计算分数、计时、蛇的游动与生长。游戏为胡天伟、江鸿、黄松顶三人合力完成。
            ui->pushButton_4->setText(tr("结束游戏"));
            this->resize(400,600);
            ui->pushButton_2->resize(150,40); ui->pushButton->resize(150,40); ui->pushButton_3->resize(150,40); ui->pushButton_4->resize(150,40);
            ui->pushButton_2->move(130,170);ui->pushButton->move(130,230);ui->pushButton_3->move(130,290);ui->pushButton_4->move(130,350);

            ui->pushButton_2->show();ui->pushButton->show();ui->pushButton_3->show();ui->pushButton_4->show();
            ui->pushButton_2->setStyleSheet(tr("background-image: url(:/new/push.jpg)"));
            ui->pushButton->setStyleSheet(tr("background-image: url(:/new/push.jpg)"));
            ui->pushButton_3->setStyleSheet(tr("background-image: url(:/new/push.jpg)"));
            ui->pushButton_4->setStyleSheet(tr("background-image: url(:/new/push.jpg)"));
            ui->pushButton_2->setFont(QFont("游戏开始",11,QFont::Bold));
            ui->pushButton->setFont(QFont("游戏帮助",11,QFont::Bold));
            ui->pushButton_3->setFont(QFont("关于游戏",11,QFont::Bold));
            ui->pushButton_4->setFont(QFont("游戏结束",11,QFont::Bold));
            //this->setStyleSheet(tr("border-image:url(:/new/prefix1/C:/Users/妖黎/Desktop/24595313_202301379033_2.jpg)"));
            this->setStyleSheet(tr("border-image:url(:/new/menu.jpg)"));

}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_pushButton_2_clicked()
{
    this->close();
    MainWindow *w = new MainWindow;
    w->show();
    w->startGame();
}

void MenuWindow::on_pushButton_clicked()
{
    QDialog *dlg1 = new QDialog();
    dlg1->show();
    QFont ft1;
    ft1.setPointSize(12);
    QLabel *lb1 = new QLabel(dlg1);
    lb1->setFont(ft1);
    lb1->move(60,50);
    lb1->setText(tr("玩家通过上下左右方向键来控制蛇的游动方向，\n"
                    "通过鼠标点击游戏上方的暂停、返回主菜单以及\n"
                    "继续符号来控制游戏的暂停和开始以及返回主菜\n"
                    "单，其他规则和一般贪吃蛇规则相同，然而难度\n"
                    "有点低，不适合大学生进行娱乐。"
    ));
    lb1->show();
    QPushButton *pb1 = new QPushButton(dlg1);
    pb1->setText(tr("确定"));
    connect(pb1,&QPushButton::clicked,dlg1,&QDialog::close);
    pb1->show();
    pb1->move(280,300);
}

void MenuWindow::on_pushButton_3_clicked()
{
    QDialog *dlg2 = new QDialog();
    dlg2->show();
    QFont ft2;
    ft2.setPointSize(12);
    QLabel *lb2 = new QLabel(dlg2);
    lb2->setFont(ft2);
    lb2->move(60,50);
    lb2->setText(tr("本游戏为简化版的贪吃蛇，游戏难度对智商要求\n"
                    "不高，实现的功能很简单，包括结算分数、计时\n"
                    "、蛇的游动与生长。游戏为胡天伟、江鸿、黄松\n"
                    "顶三人合力完成。"
    ));
    lb2->show();
    QPushButton *pb2 = new QPushButton(dlg2);
    pb2->setText(tr("确定"));
    connect(pb2,&QPushButton::clicked,dlg2,&QDialog::close);
    pb2->show();
    pb2->move(280,300);
}

void MenuWindow::on_pushButton_4_clicked()
{
    this->close();
}
