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
