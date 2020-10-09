#include "hexwidget.h"
#include "ui_hexwidget.h"

hexWidget::hexWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hexWidget)
{
    resize(400,400);

    this->setWindowTitle("十六进制计算");
    b.setParent(this);
    b.setText("返回");

    connect(&b,&QPushButton::clicked,this,&hexWidget::sendhex);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    movewidget = false;//窗口移动

    ui->setupUi(this);
}

hexWidget::~hexWidget()
{
    delete ui;
}

void hexWidget::sendhex()
{
    emit hexSignal();
}

void hexWidget::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时
    if (event->button() == Qt::LeftButton)
    {
        movewidget = true;
        //记录鼠标的世界坐标
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标
        m_windowPoint = this->frameGeometry().topLeft();
    }

}

void hexWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可
        this->move(m_windowPoint + relativePos );
    }

}

void hexWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态
        movewidget = false;
    }

}
//控制窗口移动}

void hexWidget::enterEvent(QEvent *)
{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
    if(rect.top()<0)
    {
        rect.setX(rc.x());
        rect.setY(0);
        move(rc.x(),-2);
    }
}

void hexWidget::leaveEvent(QEvent *)
{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
    if(rect.top()<0)
    {
        move(rc.x(),-rc.height()+2);
    }
}

