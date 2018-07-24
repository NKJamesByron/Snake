//#include "snake.h"
#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QTextCodec>
#include <QToolBar>
#include "menuwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>

using namespace std;

MainWindow::MainWindow(QWidget * parent)
{

    //this->resize(1000,800);


        /*timer_0 = new QTimer(this);
        connect(timer_0,SIGNAL(timeout()),this,SLOT(qtimeSlot_0()));
        timer_0->setInterval(1000);
        timer_0->start(1000);*/

        //QLabel *label = new QLabel(this);
        //ui->label->move(510,0+MenuBarSize);
        //ui->label->resize(240,510);
    this->startTimer(1000);






    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    setWindowTitle(tr("贪吃蛇游戏"));

    MenuBarSize = 90;//菜单栏所占的位置
    setFixedSize(750,510+MenuBarSize);

    lb=new QLabel(this);
        QFont ft;
        ft.setPointSize(12);
        lb->move(510,0+MenuBarSize);
        lb->resize(240,510);
        lb->setText(tr("    得 分: 0分"));
        lb->setFont(ft);
        lb->setFont(QFont("关于游戏",14,QFont::Bold));
        lb->setStyleSheet(tr("color:rgb(153,0,204);"
                                "border-image:url(:/new/menu.jpg)"));
        lb->show();


    dealMenu();
    IsDie = false;
    bRun = false; //开始的时侯不开始游戏
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    //connect(timer,SIGNAL(showPoint()),this,SLOT(showPoint()));
    times = 200;
    timer->start(times);

    /*QFont ft;
    ft.setPointSize(12);
    QLabel *label = new QLabel(this);
    label->move(510,0+MenuBarSize);
    label->resize(240,510);
    label->setText(tr("     得分: %1").arg(snake.point));
    label->setFont(ft);
    */


}

MainWindow::~MainWindow()
{
}

/*void MainWindow::showPoint(void)
{

    lb->clear();
    lb->setText(tr("     得分: %1").arg(snake.point));
    lb->show();

    update();
}*/

void MainWindow::timeout(void)
{
    //int point_01 = 0;
    if(hard_m == false) {
        snake.hard_s = false;
    } else {
        snake.hard_s = true;
    }

    if (bRun == false)
    {
        timer->stop();
        return;
    }
    snake.Move();
    IsDie = snake.IsDie();
    if (IsDie)
    {
        //停止计时器，输出游戏结束信息
        timer->stop();
        bRun = false;
        QMessageBox::information(this, tr("游戏结束"),
                tr("游戏结束\n你的得分：%1").arg(snake.length-1));
        IsDie = false;
        snake.Clear();
        return;
    }

        lb->clear();
        lb->setText(tr("      得分: %1").arg(snake.length-1));

    /*if(snake.point > point_01)
    {
        QFont ft;
        ft.setPointSize(12);
        QLabel *label = new QLabel(this);
        label->move(510,0+MenuBarSize);
        label->resize(240,510);
        label->setText(tr("     得分: %1").arg(snake.point));
        point_01 = snake.point;
    }*/

    update();
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setBrush(QColor::fromRgb(168,216,168));
    painter.drawRect(0, 0, size().width(), size().height());
    if (IsDie || !bRun)
    {
        return;
    }
    vector<Node> node;
    Node food;
    snake.OutputSnake(node, food);
    //画果子
    painter.setBrush(Qt::red);
    painter.drawEllipse(10*food.x, 10*food.y+MenuBarSize, 10, 10);
    //画墙
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0+MenuBarSize, 510, 10);  //上
    painter.drawRect(0, 500+MenuBarSize, 510, 10); //下
    painter.drawRect(0, 0+MenuBarSize, 10, 510); //左
    painter.drawRect(500, 0+MenuBarSize, 10, 510); //右

    if(hard_m == true) {

        painter.drawRect(100,190,260,10);
        painter.drawRect(150,490,260,10);
        painter.drawRect(100,240,10,260);
        painter.drawRect(400,190,10,260);
    }

    //画蛇，蛇头跟蛇身用不同的颜色
    //蛇头
    painter.setBrush(Qt::yellow);
    painter.drawRect(10*node[0].x, 10*node[0].y+MenuBarSize, 10, 10);
    //蛇身
    painter.setBrush(Qt::blue);
    int n = node.size();
    for (int i = 1; i < n; i++)
    {
        //蛇身比蛇头小一点，这样每节之间有个间隙，看得清楚
        painter.drawRect(10*node[i].x, 10*node[i].y+MenuBarSize, 9, 9);
    }
    node.clear();
    QWidget::paintEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    int direct = 0;
    switch (event->key())
    {
    case Qt::Key_Up:
        direct = 1;
        break;
    case Qt::Key_Right:
        direct = 2;
        break;
    case Qt::Key_Down:
        direct = 3;
        break;
    case Qt::Key_Left:
        direct = 4;
        break;
    case Qt::Key_U:
        speedUp();
        break;
    case Qt::Key_D:
        speedDown();
        break;
    default:
        break;
    }
    snake.ChangeDirector(direct);
    QWidget::keyPressEvent(event);
}

//处理菜单的函数
void MainWindow::dealMenu(void)
{
    QMenuBar * menuBar = new QMenuBar(this);
    QToolBar *toolBar =new QToolBar(this);
    toolBar->resize(750,60);
    toolBar->move(0,MenuBarSize-60);
    //QToolButton *start_01 =new QToolButton(toolBar);

    QMenu * gameMenu = new QMenu(tr("游戏"), menuBar);
    QMenu * helpMenu = new QMenu(tr("帮助"), menuBar);
    //添加游戏菜单项
    QAction * startGame = new QAction(tr("开始游戏"), gameMenu);
    QAction * pauseGame = new QAction(tr("暂停游戏"), gameMenu);
    QAction * speedUp = new QAction(tr("游戏加速"), gameMenu);
    QAction * speedDown = new QAction(tr("游戏减速"), gameMenu);
    QAction * quitGame = new QAction(tr("结束游戏"), gameMenu);
    gameMenu->addAction(startGame);
    gameMenu->addAction(pauseGame);
    gameMenu->addAction(speedUp);
    gameMenu->addAction(speedDown);
    gameMenu->addAction(quitGame);
    menuBar->addMenu(gameMenu);
    connect(startGame, SIGNAL(triggered()), this, SLOT(startGame()));
    connect(pauseGame, SIGNAL(triggered()), this, SLOT(pauseGame()));
    connect(speedUp, SIGNAL(triggered()), this, SLOT(speedUp()));
    connect(speedDown, SIGNAL(triggered()), this, SLOT(speedDown()));
    connect(quitGame, SIGNAL(triggered()), this, SLOT(close()));
    //添加帮助和关于菜单项
    QAction * helpGame = new QAction(tr("游戏帮助"), helpMenu);
    QAction * aboutGame = new QAction(tr("关于"), helpMenu);
    helpMenu->addAction(helpGame);
    helpMenu->addAction(aboutGame);
    menuBar->addMenu(helpMenu);
    connect(helpGame, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(aboutGame, SIGNAL(triggered()), this, SLOT(showAbout()));
    //将菜单加入菜单栏
    menuBar->addMenu(helpMenu);

    //toolBar->setStyleSheet(tr("border-image:url(:/new/white.jpg)"));
    //toolBar->setStyleSheet(tr("background-color:rgb(0,170,153)"));
    toolBar->setStyleSheet(tr("background-color:rgb(136,170,0)"));
    //toolBar->setStyleSheet(tr("background-color:rgb(102,136,0)"));



    QAction *start_01 =new QAction;
    QIcon icon1(":/new/start.png");
    start_01->setIcon(icon1);
    start_01->setToolTip(tr("开始/继续"));
    start_01->toolTip();
    connect(start_01, SIGNAL(triggered()), this, SLOT(startGame()));
    toolBar->addAction(start_01);

    QAction *pause_01 =new QAction;
    QIcon icon2(":/new/pause.png");
    pause_01->setIcon(icon2);
    pause_01->setToolTip(tr("暂停"));
    pause_01->toolTip();
    connect(pause_01, SIGNAL(triggered()), this, SLOT(pauseGame()));
    toolBar->addAction(pause_01);

    QAction *speedUp_01 =new QAction;
    QIcon icon5(":/new/top.png");
    speedUp_01->setIcon(icon5);
    speedUp_01->setToolTip(tr("加速"));
    speedUp_01->toolTip();
    connect(speedUp_01, SIGNAL(triggered()), this, SLOT(speedUp()));
    toolBar->addAction(speedUp_01);

    QAction *speedDown_01 =new QAction;
    QIcon icon6(":/new/down.png");
    speedDown_01->setIcon(icon6);
    speedDown_01->setToolTip(tr("减速"));
    speedDown_01->toolTip();
    connect(speedDown_01, SIGNAL(triggered()), this, SLOT(speedDown()));
    toolBar->addAction(speedDown_01);

    QAction *return_01 =new QAction;
    QIcon icon3(":/new/undo.png");
    return_01->setIcon(icon3);
    return_01->setToolTip(tr("返回主菜单"));
    return_01->toolTip();
    connect(return_01, SIGNAL(triggered()), this, SLOT(returnMenu()));
    toolBar->addAction(return_01);

    QAction *close_01 =new QAction;
    QIcon icon4(":/new/close.png");
    close_01->setIcon(icon4);
    close_01->setToolTip(tr("退出游戏"));
    close_01->toolTip();
    connect(close_01, SIGNAL(triggered()), this, SLOT(close()));
    toolBar->addAction(close_01);

    toolBar->insertSeparator(speedUp_01);
    toolBar->insertSeparator(return_01);

    //start_01->addAction(startGame);

    //设置菜单栏
    setMenuBar(menuBar);


}

void MainWindow::showAbout(void)
{
    QMessageBox::information(this, tr("关于贪吃蛇游戏"),
                   tr("见主菜单！"));
}

void MainWindow::showHelp(void)
{
    QMessageBox::information(this, tr("游戏帮助"),
                   tr("请见主菜单！"));
}

void MainWindow::startGame(void)
{
    bRun = true;
    timer->start(times);
}

void MainWindow::pauseGame(void)
{
    bRun = false;
    timer->stop();
}

void MainWindow::speedUp(void)
{
    times -= 20;
    if (times <= 20)
    {
        times = 20;
    }
    timer->stop();
    timer->start(times);
}

void MainWindow::speedDown(void)
{
    times += 20;
    if (times >= 500)
    {
        times = 500;
    }
    timer->stop();
    timer->start(times);
}

void MainWindow::returnMenu(void)
{

    this->pauseGame();
    this->close();
    MenuWindow *m = new MenuWindow;
    m->show();
}

//void MainWindow::qtimeSlot_0(void){
//   static int count=0;
//                count++;
                  //QLabel *label = new QLabel(this);
                 // label->move(510,0+MenuBarSize);
                  //label->resize(240,510);
                 // QFont ft;
                 // ft.setPointSize(15);
                  //label->setFont(ft);
                  //label->show();
                  //label->setText(QString::number(count));
                  //delete label;
                  //label->show();
                  //delete label;
//            }
/*void MainWindow::timerEvent(QTimerEvent *event){
    static int sec=0;

    sec++;

    QLabel *label = new QLabel(this);
    label->move(510,0+MenuBarSize);
    label->resize(40,50);
    QFont ft;
    ft.setPointSize(15);
    label->setFont(ft);
   // label->show();
    label->setText(QString::number(sec));
    label->clear();
    //label->releaseShortcut(sec);
    //label->hide();
    label->show();
    update();


}*/

void MainWindow::timerEvent(QTimerEvent *event){
    static int sec=0;
       QTextEdit *text1=new QTextEdit(this);
       text1->move(520,160+MenuBarSize);
       text1->resize(340,30);
       QFont ft1;ft1.setPointSize(12);text1->setFont(ft1);
       //text1->setStyleSheet("QTextEdit {color:rgb(168,216,168);"
         //                   "border-image:gray;}");
       //text1->setStyleSheet(tr("QTextEdit {color:black;"
         //                   "background-image: rgb(168,216,168);}"));


       text1->setStyleSheet(tr("color:rgb(153,0,204);"
                               "border-image:url(:/new/menu.jpg)"));
       //text1->setStyleSheet(tr("border-image:url(:/new/menu.jpg)"));
       text1->setText(tr("     时间：%1s").arg(sec++));

       text1->setFont(QFont("关于游戏",14,QFont::Bold));
       text1->show();

}
