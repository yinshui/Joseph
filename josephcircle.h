#ifndef JOSEPHCIRCLE_H
#define JOSEPHCIRCLE_H
#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <QTime>
#include <ctime>    //产生随机数
#include <QDebug>
#include "linklist.h"
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define FOVERFLOW	-2

typedef int Status;
namespace Ui {
class JosephCircle;
}

class JosephCircle : public QMainWindow
{
    Q_OBJECT

public:
    explicit JosephCircle(QWidget *parent = 0);
    ~JosephCircle();
    Status ListInsert(int i, int e);
    LNode *ListTraverse();
    Status Paint();
    Status rePaint();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_editingFinished();

private:
    Ui::JosephCircle *ui;
    QLabel *dice;//扔骰子的m
    QLabel *num;//报数
    QString linefromedit;//接收来自LineEdit的数据
    int n=0;//人数的n
    int N=0;
    LinkList *lll;
    QString *result;
};

#endif // JOSEPHCIRCLE_H
