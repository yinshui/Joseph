#include "josephcircle.h"
#include "ui_josephcircle.h"
#include "linklist.h"
#define  SIZE   150
#define TABLE 250
#define PI 3.1415926
typedef int Status;
/* 用于比较两个值是否相等的具体函数，与LocateElem中的函数指针定义相同，调用时代入
   int LocateElem(sqlist L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)) */
Status MyCompare(ElemType e1, ElemType e2)
{
    if (e1->text().toInt()==e2->text().toInt())
        return TRUE;
    else
        return FALSE;
}

void sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime()<reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

JosephCircle::JosephCircle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JosephCircle)
{
    ui->setupUi(this);
    //显示图片
    QImage *image=new QImage(":/round.png");

    QLabel *label=new QLabel(this);
    label->setGeometry(this->width()/2-TABLE/2,this->height()/2-TABLE/2+20,TABLE,TABLE);
    QImage* imgScaled = new QImage;
    *imgScaled=image->scaled(TABLE,TABLE,Qt::KeepAspectRatio);
    label->setPixmap(QPixmap::fromImage(*imgScaled));
    label->show();
}

JosephCircle::~JosephCircle()
{
    delete ui;
}

void JosephCircle::on_lineEdit_textEdited(const QString &arg1)
{
    linefromedit=arg1;
}

Status JosephCircle::Paint(){
    LNode *p = lll->head;
    double d;
    d=2*PI/n;
    for(int i=0;i<n;i++){
        p->data->move(this->width()/2+SIZE*sin(i*d),this->height()/2-SIZE*cos(i*d));
        QFont ft;
        ft.setPointSize(20);
        p->data->setFont(ft);
        p->data->setVisible(true);
        p=p->next;
    }
    return OK;
}

Status JosephCircle::rePaint(){
    LNode *p = lll->head;
    for(int i=0;i<n;i++){
        p->data->setVisible(false);
        p=p->next;
    }
    return OK;
}

void JosephCircle::on_lineEdit_editingFinished()
{
    if(linefromedit.isEmpty())
        QMessageBox::information(this,"tips","Please input data");
    else{
        n=linefromedit.toInt();
        N=n;
        dice = new QLabel(this);
        lll =new LinkList;
        for (int i=n; i>0; i-=1)
            ListInsert(1, i);
        Paint();
        num =new QLabel(this);
        result = new QString[n];
    }
}

void JosephCircle::on_pushButton_clicked()
{
    srand((unsigned)time(NULL));    //随机数
    dice->setText(QString::number(rand() % 6+1));//生成随机数，并转换为字符串

    dice->setMinimumSize(55,0);
    dice->setGeometry(400, 10, 150, 50);
    QFont ft;
    ft.setPointSize(30);
    dice->setFont(ft);
    dice->show();
    for(int i=0;i<15;i++){
        dice->setVisible (true);
        sleep(100);
        dice->setVisible (false); //标签不可视
        dice->setText(QString::number(rand() % 6+1));
    }
    dice->setVisible (true);
    LNode *newhead;
    newhead=ListTraverse();
    sleep(200);
    rePaint();
    lll->head=newhead;
    lll->ListDelete(n,&result[N-n]);
    n=n-1;
    num->setVisible(false);
    Paint();
    if(n==1){
        QMessageBox::information(this,"congratulations","Congratulations player "+lll->head->data->text()+" th");
        result[N-1]=lll->head->data->text();
        QString a="result:";
        for(int j=0;j<N;j++){
            a+=result[j];
        }
        QLabel *aa=new QLabel(a,this);
        aa->setGeometry(200, 400, 150, 50);
        QFont ft;
        ft.setPointSize(15);    //字体的缩小
        aa->setFont(ft);
        aa->setStyleSheet("color:red;");
        aa->show();
        //        this->close();
    }
}

/* 在指定位置前插入一个新元素 为了QLabel在QMainwindow里啊*/
Status JosephCircle::ListInsert(int i, int e)
{
    LNode *s, *p = lll->head;	//p指向头结点
    int      pos  = 1;  //因为p已指向首元，故起始位置是1

    /* 如果新结点成为首元，则需要改变head的值，其它位置插入则head不变 */
    if (i != 1) {
    /* 寻找第i-1个结点 */
    while(p && pos<i-1) {
        p=p->next;
        pos++;
        }

    if (p==lll->head || pos>i-1)  //i值非法则返回
        return ERROR;
    }

    s = new LNode;
    if (s==NULL)
    return OVERFLOW;

    s->data = new QLabel(QString::number(e),this); 	//新结点数据域赋值
    if (i != 1) {
        //插入位置非首元，此时p指向第i-1个结点
    s->next = p->next;	//新结点的next是p->next
    p->next = s;		//第i-1个的next是新结点
    }
    else {
        //插入位置是首元
        s->next = p;	//此时p就是L（包括L=NULL的情况）
        lll->head = s;		//头指针指向新结点
        if(lll->head->next==NULL)
            lll->head->next = s;
        if(p!=NULL){
            while(p->next!=lll->head->next)
                p=p->next;
            p->next=lll->head;
        }
    }
    return OK;
}

/* 遍历线性表 数m个人*/
LNode *JosephCircle::ListTraverse()
{
    LNode *p = lll->head;
    LNode *q = lll->head;
    double d;
    d=2*PI/n;
    for(int i=0;i<dice->text().toInt();i++){
        num->setVisible(false);
        num->setText(QString::number(i+1));
        num->move(this->width()/2+SIZE*sin(i*d)+50,this->height()/2-SIZE*cos(i*d));
        QFont ft;
        ft.setPointSize(30);
        num->setFont(ft);
        num->setStyleSheet("color:red;");
        num->setVisible(true);
        sleep(500);
        p=p->next;
    }
    if(dice->text().toInt()%n!=0)
        for(int j=1;j<dice->text().toInt()%n;j++)
            q=q->next;
    else{
        for(int j=0;j<n-1;j++)
            q=q->next;
    }
    return q;
}
