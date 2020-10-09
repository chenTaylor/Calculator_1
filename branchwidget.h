#ifndef BRANCHWIDGET_H
#define BRANCHWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "decwidget.h"   //子窗口头文件
#include "binwidget.h"
#include "hexwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QGridLayout>
#include <QTimer>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QApplication>
#include <QString>


namespace Ui {
class branchWidget;
}

class branchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit branchWidget(QWidget *parent = nullptr);
    ~branchWidget();

    void paintEvent(QPaintEvent *);

    void dec();
    void dealdec();

    void bin();
    void dealbin();

    void hex();
    void dealhex();

    void sendxyz();


private:
    Ui::branchWidget *ui;


    QPushButton b1;
    QPushButton b2;
    QPushButton b3;
    QPushButton b4;

    decWidget w1;
    binWidget w2;
    hexWidget w3;

    //控制输出和布局
    QGridLayout *mainLayout;
    QTimer *switchTime;
    QStringList strListImport;

    //控制窗口移动
    bool movewidget;
    QPoint m_startPoint;
    QPoint m_windowPoint;

signals:
    //信号必须有signals关键字来声明
    //使用：emit mysignal();
    void xyzSignal();

private slots:
    void on_bin_Pushbutton_clicked();

protected:
    //控制窗口移动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // BRANCHWIDGET_H
