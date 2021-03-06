#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QtGui>
#include "snake.h"
#include <QtWidgets>
//#include "mylabel.h"
#include <QTimer>
#include<QTimerEvent>
#include<QTime>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow(void);

    QLabel *lb;
    bool hard_m;
    //QLabel *label2;

    //void showPoint(void);

public slots:
    void timeout(void);   //自定义的槽函数，处理定时器时间，用于游戏更新
    void showAbout(void); //自定义的槽函数，显示关于信息
    void showHelp(void);  //自定义的槽函数，显示帮助信息
    void startGame(void); //自定义的槽函数，开始游戏
    void pauseGame(void); //自定义的槽函数，暂停游戏
    void speedUp(void); //自定义的槽函数，游戏加速
    void speedDown(void); //自定义的槽函数，游戏减速
    void returnMenu(void);
    //void showPoint(void);

protected:
    void keyPressEvent(QKeyEvent * event); //处理按键消息
    void paintEvent(QPaintEvent * event); //处理重绘消息
    //void paintEvent_h(QPaintEvent * event);

private:

    void dealMenu(void);   //处理菜单的函数
    //QTimer *timer_0;

private slots:
    //void qtimeSlot_0(void);

private:
    Snake snake; //贪食蛇的类
    bool IsDie;  //游戏是否结束
    bool bRun;  //游戏是否运行的变量
    QTimer * timer; //游戏定时器
    int times; //定时器的频率
    int MenuBarSize; //菜单栏所占的位置
    bool IsGetPoint;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif
