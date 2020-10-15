#include "binwidget.h"
#include "ui_binwidget.h"

binWidget::binWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::binWidget)
{
    resize(400,400);

    this->setWindowTitle("二进制计算");
    b.setParent(this);
    b.setText("返回");


    connect(&b,&QPushButton::clicked,this,&binWidget::sendbin);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);


    movewidget = false;//窗口移动

    ui->setupUi(this);
}

binWidget::~binWidget()
{
    delete ui;
}

void binWidget::sendbin()
{
    emit binSignal();
}

void binWidget::mousePressEvent(QMouseEvent *event)
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

void binWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可
        this->move(m_windowPoint + relativePos );
    }

}

void binWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态
        movewidget = false;
    }

}
//控制窗口移动}

void binWidget::enterEvent(QEvent *)
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

void binWidget::leaveEvent(QEvent *)
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




void binWidget::on_Button1_clicked()
{

}

void binWidget::on_Button2_clicked()
{

}

void binWidget::on_ButtonAdd_clicked()
{

}

void binWidget::on_ButtonSub_clicked()
{

}

void binWidget::on_ButtonAnd_clicked()
{

}

void binWidget::on_ButtonOr_clicked()
{

}

void binWidget::on_ButtonNot_clicked()
{

}

void binWidget::on_ButtonEqual_clicked()
{

}

void binWidget::on_ButtonAE_clicked()
{

}

void binWidget::on_pushButton_10_clicked()
{

}
