#include "deccounter.h"
#include "ui_deccounter.h"
#include <QDebug>
#include <QDesktopWidget>

decCounter::decCounter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::decCounter)
{
    //不显示标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    QDesktopWidget * desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2,(desktop->height() - this->height())/2);
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setAlignment(Qt::AlignRight);//设置显示居右
    ui->lineEdit->setStyleSheet("font-size:18px");//设置字体大小为18px
    ui->lineEdit->setText("0");//设置初试文本为0

    lefts=0;
    //fist connect,next init
    connect(this,&decCounter::whichBtn,&decCounter::enableOp);
    connect(this,&decCounter::whichBtn,&decCounter::enableLeft);
    connect(this,&decCounter::whichBtn,&decCounter::enableEqual);
    connect(this,&decCounter::whichBtn,&decCounter::enableRight);
    connect(this,&decCounter::whichBtn,&decCounter::enableDigit);
    init();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
}

decCounter::~decCounter()
{
    delete ui;
}
/*
 *public function
 */
//初始化操作.不仅开头调用，每次计算完结果都会调用。
void decCounter::init()
{
    if(!expStack.isEmpty())
        expStack.clear();
    if(!opStack.isEmpty())
        opStack.clear();
    opStack.push('#');
    complete=true;
    emit whichBtn(INIT);
}

void decCounter::digitBtn(char ch)
{
    QString s = ui->lineEdit->text();
    if(!complete)
        ui->lineEdit->setText(s+ch);
    else
    {
        ui->lineEdit->setText(QString(ch));
        complete = false;
    }
    emit whichBtn(DIGIT);
}

/*
 *SLOT function
 */
void decCounter::enableDigit(int type)
{
    bool enable=true;
    if(RIGHT==type)
        enable=false;
    ui->btn0->setEnabled(enable);
    ui->btn1->setEnabled(enable);
    ui->btn2->setEnabled(enable);
    ui->btn3->setEnabled(enable);
    ui->btn4->setEnabled(enable);
    ui->btn5->setEnabled(enable);
    ui->btn6->setEnabled(enable);
    ui->btn7->setEnabled(enable);
    ui->btn8->setEnabled(enable);
    ui->btn9->setEnabled(enable);
    ui->btnDot->setEnabled(enable);
}
void decCounter::enableOp(int type)
{
    bool enable = false;
    switch(type)
    {
    case RIGHT:
    case DIGIT:enable = true;
        break;
    case INIT:
    case OPERA:
    case LEFT:enable = false;
        break;
    default:return;
    }
    ui->btnMuti->setEnabled(enable);
    ui->btnDivi->setEnabled(enable);
    ui->btnAdd->setEnabled(enable);
    ui->btnSub->setEnabled(enable);
}
void decCounter::enableLeft(int type)
{
    bool enable = false;
    switch(type)
    {
    case RIGHT:
    case DIGIT:
        break;
    case INIT:
    case LEFT:
    case OPERA:enable = true;
        break;
    default:return;
    }
    ui->btnLeft->setEnabled(enable);
}
void decCounter::enableRight(int type)
{
    bool enable = false;
    switch(type)
    {
    case INIT:
    case OPERA:
        break;
    case LEFT:enable = true;
    case RIGHT:
    case DIGIT:
        if(lefts)
            enable = true;
        break;
    default:return;
    }
    ui->btnRight->setEnabled(enable);
}
void decCounter::enableEqual(int type)
{
    bool enable = false;
    switch(type)
    {
    case OPERA:
    case LEFT:
        break;
    case RIGHT:
    case DIGIT:
        enable = true;
        break;
    default:return;
    }
    ui->btnEqual->setEnabled(enable);
}
////////////////////////////////////
void decCounter::on_btn0_clicked()
{
    digitBtn('0');
}

void decCounter::on_btn1_clicked()
{
    digitBtn('1');

}

void decCounter::on_btn2_clicked()
{
    digitBtn('2');
}

void decCounter::on_btn3_clicked()
{
    digitBtn('3');
}

void decCounter::on_btn4_clicked()
{
    digitBtn('4');
}

void decCounter::on_btn5_clicked()
{
    digitBtn('5');
}

void decCounter::on_btn6_clicked()
{
    digitBtn('6');
}

void decCounter::on_btn7_clicked()
{
    digitBtn('7');
}

void decCounter::on_btn8_clicked()
{
    digitBtn('8');
}

void decCounter::on_btn9_clicked()
{
    digitBtn('9');
}

void decCounter::on_btnDot_clicked()
{
    //如果是小数点,那么不能以小数点打头
    QString s = ui->lineEdit->text();
    if(!complete)
        ui->lineEdit->setText(s+".");
}
///////////////////////////////////////////////////
//加号和减号应做特殊处理。因为也可以理解为正负号
///////////////////////////////////////////////////
void decCounter::on_btnAdd_clicked()
{
    QString s = ui->lineEdit->text();
    ui->lineEdit->setText(s+"+");
    emit whichBtn(OPERA);
}

void decCounter::on_btnSub_clicked()
{
    QString s = ui->lineEdit->text();
    ui->lineEdit->setText(s+"-");
    emit whichBtn(OPERA);
}
//////////////////////////////////////////////////////
void decCounter::on_btnMuti_clicked()
{
    QString s = ui->lineEdit->text();
    ui->lineEdit->setText(s+"*");
    emit whichBtn(OPERA);
}

void decCounter::on_btnDivi_clicked()
{
    QString s = ui->lineEdit->text();
    ui->lineEdit->setText(s+"/");
    emit whichBtn(OPERA);
}
////////////////////////////////////////////
void decCounter::on_btnLeft_clicked()
{
    QString s = ui->lineEdit->text();
    if(!complete)
        ui->lineEdit->setText(s+"(");
    else
    {
        ui->lineEdit->setText("(");
        complete = false;
    }
    emit whichBtn(LEFT);
    lefts++;
}

void decCounter::on_btnRight_clicked()
{
    QString s = ui->lineEdit->text();
    if(!complete)
        ui->lineEdit->setText(s+")");
    lefts--;
    emit whichBtn(RIGHT);
}
//得到运算符的优先级
int decCounter::getLevel(const QChar &oper)
{
    switch(oper.cell())
    {
    case '#':
    case '(':return 0;
    case '+':
    case '-':return 1;
    case '*':
    case '/':
    case '%':return 2;
    }
    return 0;
}
//转换为后缀表达式，实现最主要功能
void decCounter::toPostfix()
{
    QString exp = ui->lineEdit->text();
    //QString exp = "0.3/(5*2+1)",postfix;

    int j=0;
    qDebug()<<j;
    for(int i=0;i<exp.length();i++)
    {qDebug()<<i<<exp[i];
        if(exp[i].isDigit()||exp[i]=='.')
        {
            postfix.push_back(exp[i]);
        }
        else if(exp[i]=='(')
        {
            opStack.push(exp[i]);
        }
        else if(exp[i]==')')
        {
            postfix.push_back(' ');
            while(opStack.top()!='(')
            {
                postfix.push_back(opStack.pop());qDebug()<<postfix;
            }
            opStack.pop();
        }
        else if(getLevel(exp[i])>getLevel(opStack.top()))
        {
            postfix.push_back(' ');qDebug()<<"postfix";
            opStack.push(exp[i]);
        }
        else
        {
            postfix.push_back(' ');qDebug()<<postfix;
            while(getLevel(exp[i])<=getLevel(opStack.top()))
                postfix.push_back(opStack.pop());
            opStack.push(exp[i]);
        }
    }
    while(opStack.top()!='#')
    {
        QChar c = opStack.pop();
        postfix.push_back(' ');
        postfix.push_back(c);
    }
    qDebug()<<postfix;
}
//
void decCounter::evaluation()
{
    QString tem;
    QStack<double> ans;
    for(int i=0;i<postfix.size();i++)
    {
        qDebug()<<postfix[i]<<i;
        if(postfix[i].isDigit()||postfix[i]=='.')
            tem.push_back(postfix[i]);
        else if(postfix[i]==' ')
        {
            if(!tem.isEmpty())
            {
                ans.push(tem.toDouble());
                tem.clear();
            }
            qDebug()<<ans.top()<<tem.isEmpty();
        }
        else
        {
            double a,b;
            a=ans.pop();qDebug()<<a<<"a";
            b=ans.pop();qDebug()<<b<<"b";
            switch(postfix[i].cell())
            {
            case '+':ans.push(b+a);break;
            case '-':ans.push(b-a);break;
            case '*':ans.push(b*a);break;
            case '/':ans.push(b/a);break;
            case '%':ans.push((int)a%(int)b);break;
            }
            qDebug()<<ans.top()<<"top";
        }

    }
    //qDebug()<<ans.top();
    ui->lineEdit->setText(QString::number(ans.top()));
}
//等于号的槽函数。
void decCounter::on_btnEqual_clicked()
{
    //如果还没输入，那么等于号不起作用
    if(ui->lineEdit->text()=="0")
        return;

    toPostfix();
    evaluation();
    init();
}


void decCounter::on_btnClear_clicked()
{
    init();
    ui->lineEdit->setText("0");
}


void decCounter::on_btnBack_clicked()
{
    QString s = ui->lineEdit->text();
    s=s.mid(0,s.size()-1);
    ui->lineEdit->setText(s);
}

void decCounter::on_btnExit_clicked()
{
    this->close();
}

void decCounter::paintEvent(QPaintEvent *event)
{

    QPixmap pixmap = QPixmap("D:/qt_user/calculator/2.jpg").scaled(this->size());//nature、ballon、sea
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
}

//{控制窗口移动
void decCounter::mousePressEvent(QMouseEvent *event)
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

void decCounter::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可
        this->move(m_windowPoint + relativePos );
    }

}

void decCounter::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态
        movewidget = false;
    }

}
//控制窗口移动}

void decCounter::enterEvent(QEvent *)
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

void decCounter::leaveEvent(QEvent *)
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
