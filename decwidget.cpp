#include "decwidget.h"
#include "ui_decwidget.h"
#include "floatnumber.h"
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QDialog>
#include <QDebug>

decWidget::decWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::decWidget)
{
    resize(400,400);

    this->setWindowTitle("十进制计算");
    b.setParent(this);
    b.setText("返回");

    connect(&b,&QPushButton::clicked,this,&decWidget::senddec);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    movewidget = false;//窗口移动


    ui->setupUi(this);
}

decWidget::~decWidget()
{
    delete ui;
}

void decWidget::senddec()
{
    emit decSignal();
}

void decWidget::mousePressEvent(QMouseEvent *event)
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

void decWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可
        this->move(m_windowPoint + relativePos );
    }

}

void decWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态
        movewidget = false;
    }

}
//控制窗口移动}

void decWidget::enterEvent(QEvent *)
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

void decWidget::leaveEvent(QEvent *)
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



void decWidget::on_Button_1_clicked()
{

}

void decWidget::on_Button_2_clicked()
{

}

void decWidget::on_Button_3_clicked()
{

}

void decWidget::on_Button_4_clicked()
{

}

void decWidget::on_Button_5_clicked()
{

}

void decWidget::on_Button_6_clicked()
{

}

void decWidget::on_Button_7_clicked()
{

}

void decWidget::on_Button_8_clicked()
{

}

void decWidget::on_Button_9_clicked()
{

}

void decWidget::on_Button_0_clicked()
{
    if(this->tmp != " ")
        {
            this->tmp += this->ui->Button_0->text();
            this->ui->lbl_display->setText(this->tmp);
        }

}

void decWidget::on_ButtonAdd_clicked()
{

}

void decWidget::on_ButtonSub_clicked()
{

}

void decWidget::on_ButtonMult_clicked()
{

}

void decWidget::on_ButtonDiv_clicked()
{

}

void decWidget::on_ButtonDot_clicked()
{

}

void decWidget::on_ButtonLeft_clicked()
{

}

void decWidget::on_ButtonRight_clicked()
{

}

void decWidget::on_ButtonEqual_clicked()
{

}

void decWidget::on_ButtonEX_clicked()
{

}

void decWidget::on_ButtonSQ_clicked()
{

}

void decWidget::on_ButtonCE_clicked()
{

}

void decWidget::on_ButtonAE_clicked()
{

}
