#ifndef HEXWIDGET_H
#define HEXWIDGET_H

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
class hexWidget;
}

class hexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit hexWidget(QWidget *parent = nullptr);
    ~hexWidget();

    void sendhex();


signals:
    //信号必须有signals关键字来声明
    //使用：emit mysignal();
    void hexSignal();

public slots:

private:
    Ui::hexWidget *ui;

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
};


#endif // HEXWIDGET_H
