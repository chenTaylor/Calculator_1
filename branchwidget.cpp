#include "branchwidget.h"
#include "ui_branchwidget.h"
#include <QPushButton>

branchWidget::branchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::branchWidget)
{

    b1.setParent(this);
    b1.setText("关闭");
    b1.setGeometry(340,0,60,40);  //按钮位置，大小

    b2.setParent(this);
    b2.setText("十进制计算");
    b2.setGeometry(0,200,400,60);

    b3.setParent(this);
    b3.setText("二进制计算");
    b3.setGeometry(0,270,400,60);

    b4.setParent(this);
    b4.setText("十六进制计算");
    b4.setGeometry(0,340,400,60);

    connect(&b1,&QPushButton::pressed,this,&branchWidget::close);

    /*自定义槽，普通函数的用法
     * 槽函数需要和信号一致（参数，返回值）
     * 由于信号都是没有返回值，所以槽函数一定没有返回值
     */

    this->setWindowTitle("计算器");

    connect(&b2,&QPushButton::clicked,this,&branchWidget::dec);  //十进制
    connect(&b3,&QPushButton::clicked,this,&branchWidget::bin);  //二进制
    connect(&b4,&QPushButton::clicked,this,&branchWidget::hex);  //十六进制

    //处理子窗口的信号
    connect(&w1,&decWidget::decSignal,this,&branchWidget::dealdec); //十进制
    connect(&w2,&binWidget::binSignal,this,&branchWidget::dealbin);  //二进制
    connect(&w3,&hexWidget::hexSignal,this,&branchWidget::dealhex);  //十六进制

    resize(400,400);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    movewidget = false;//窗口移动


    ui->setupUi(this);
}

branchWidget::~branchWidget()
{
    delete ui;
}

void branchWidget::dec()
{
    //子窗口显示
    w1.show();
    //主窗口隐藏
    this->hide();
}

void branchWidget::dealdec()
{
    //子窗口隐藏
    w1.hide();
    //主窗口显示
    show();
}

void branchWidget::bin()
{
    //子窗口显示
    w2.show();
    //主窗口隐藏
    this->hide();
}

void branchWidget::dealbin()
{
    //子窗口隐藏
    w2.hide();
    //主窗口显示
    show();
}

void branchWidget::hex()
{
    //子窗口显示
    w3.show();
    //主窗口隐藏
    this->hide();
}

void branchWidget::dealhex()
{
    //子窗口隐藏
    w3.hide();
    //主窗口显示
    show();
}

void branchWidget::sendxyz()
{
    emit xyzSignal();
}

void branchWidget::paintEvent(QPaintEvent *event)
{

    QPixmap pixmap = QPixmap("D:/qt_user/1.png").scaled(this->size());//nature、ballon、sea
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
}

void branchWidget::on_bin_Pushbutton_clicked()   //自定义按钮函数 点击传值。

{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
}

void branchWidget::mousePressEvent(QMouseEvent *event)
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

void branchWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可
        this->move(m_windowPoint + relativePos );
    }

}

void branchWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态
        movewidget = false;
    }

}
//控制窗口移动}

void branchWidget::enterEvent(QEvent *)
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

void branchWidget::leaveEvent(QEvent *)
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


