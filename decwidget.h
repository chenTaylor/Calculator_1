#ifndef DECWIDGET_H
#define DECWIDGET_H

#include <QWidget>
#include <QPushButton>
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
#include <QDialog>
#include <QStack>
#include <QLineEdit>

namespace Ui {
class decWidget;
}

class decWidget : public QWidget
{
    Q_OBJECT

public:
    explicit decWidget(QWidget *parent = nullptr);
    ~decWidget();

    void senddec();


signals:
    //信号必须有signals关键字来声明
    //使用：emit mysignal();
    void decSignal();

public slots:

private:
    Ui::decWidget *ui;

    QPushButton b;

    //控制输出和布局
    QGridLayout *mainLayout;
    QTimer *switchTime;
    QStringList strListImport;

    //控制窗口移动
    bool movewidget;
    QPoint m_startPoint;
    QPoint m_windowPoint;




protected:
    //控制窗口移动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    QPushButton Button_1;
    QPushButton Button_2;
    QPushButton Button_3;
    QPushButton Button;
    QPushButton Button_5;
    QPushButton Button_6;
    QPushButton Button_7;
    QPushButton Button_8;
    QPushButton Button_9;
    QPushButton Button_0;
    QPushButton ButtonAdd;
    QPushButton ButtonSub;
    QPushButton ButtonMult;
    QPushButton ButtonDiv;
    QPushButton ButtonDot;
    QPushButton ButtonLeft;
    QPushButton ButtonRight;
    QPushButton ButtonEqual;
    QPushButton ButtonEX;
    QPushButton ButtonSQ;
    QPushButton ButtonCE;
    QPushButton ButtonAE;

    QLineEdit* lineEdit;

    //声明需要的变量
    //第一个数，第二个数，运算结果
    float num1,num2,result;
    QString S; //用于显示在lineEdit里面的字符串
    //等号运算符的时候，判断是加、减、乘、除的哪一个
    char sign;
    int mark; //若点击过加减乘除，mark=2,默认是1



private slots:
    void on_Button_1_clicked();
    void on_Button_2_clicked();
    void on_Button_3_clicked();
    void on_Button_4_clicked();
    void on_Button_5_clicked();
    void on_Button_6_clicked();
    void on_Button_7_clicked();
    void on_Button_8_clicked();
    void on_Button_9_clicked();
    void on_Button_0_clicked();
    void on_ButtonAdd_clicked();
    void on_ButtonSub_clicked();
    void on_ButtonMult_clicked();
    void on_ButtonDiv_clicked();
    void on_ButtonDot_clicked();
    void on_ButtonLeft_clicked();
    void on_ButtonRight_clicked();
    void on_ButtonEqual_clicked();
    void on_ButtonEX_clicked();
    void on_ButtonSQ_clicked();
    void on_ButtonCE_clicked();
    void on_ButtonAE_clicked();
};

#endif // DECWIDGET_H
