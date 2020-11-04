#ifndef DECCOUNTER_H
#define DECCOUNTER_H

#include <QMainWindow>
#include <QStack>
#include <QPushButton>
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
#include <QPainter>
#include <QPaintEvent>
#include <QString>
#include <QTextCodec>

const int INIT = 0;
const int DIGIT = 1;
const int OPERA = 2;
const int LEFT = 3;
const int RIGHT = 4;

namespace Ui {
class decCounter;
}

class decCounter : public QMainWindow
{
    Q_OBJECT

public:
    explicit decCounter(QWidget *parent = 0);
    ~decCounter();
    void init();
    int getLevel(const QChar& oper);//得到运算符等级
    void toPostfix();//转换成后缀表达式
    void evaluation();//求值
    void digitBtn(char ch);

signals:
    void whichBtn(int type);

private slots:
    void enableDigit(int type);
    void enableOp(int type);
    void enableLeft(int type);
    void enableRight(int type);
    void enableEqual(int type);

    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();

    void on_btnDot_clicked();
    void on_btnAdd_clicked();
    void on_btnSub_clicked();
    void on_btnMuti_clicked();
    void on_btnDivi_clicked();
    void on_btnEqual_clicked();
    void on_btnLeft_clicked();
    void on_btnRight_clicked();
    void on_btnClear_clicked();

    void on_btnBack_clicked();
    void on_action_about_triggered();
    void on_btnExit_clicked();

private:
    Ui::decCounter *ui;

    void paintEvent(QPaintEvent *);

    QStack<QChar> expStack;//后缀表达式栈
    QStack<QChar> opStack;//运算符栈
    QString postfix;//存储后缀表达式
    bool complete;//表达式是否计算完成
    int lefts;

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
};

#endif // DECCOUNTER_H
