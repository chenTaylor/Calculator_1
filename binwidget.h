#ifndef BINWIDGET_H
#define BINWIDGET_H

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
class binWidget;
}

class binWidget : public QWidget
{
    Q_OBJECT

public:
    explicit binWidget(QWidget *parent = nullptr);
    ~binWidget();

    void sendbin();



signals:
    //信号必须有signals关键字来声明
    //使用：emit mysignal();
    void binSignal();

public slots:

private:
    Ui::binWidget *ui;

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

    void on_Button1_clicked();
    void on_Button2_clicked();
    void on_ButtonAdd_clicked();
    void on_ButtonSub_clicked();
    void on_ButtonAnd_clicked();
    void on_ButtonOr_clicked();
    void on_ButtonNot_clicked();
    void on_ButtonEqual_clicked();
    void on_ButtonAE_clicked();
    void on_pushButton_10_clicked();
};


#endif // BINWIDGET_H
