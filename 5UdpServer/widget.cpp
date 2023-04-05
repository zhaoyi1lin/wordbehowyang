
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


//启动
void Widget::on_pushButton_2_clicked()
{
    //1.创建qudpsocket对象
    mSocket = new QUdpSocket(this);
    //2.连接接受数据信号和槽

    QObject::connect(mSocket,&QUdpSocket::readyRead,this,[&](){
        //数据缓冲区

        QByteArray arr;
        //调整缓冲区大小和受到的数据大小一致
        arr.resize(mSocket->bytesAvailable());
        //接受数据
        mSocket->readDatagram(arr.data(),arr.size(),&addr,&port);
        //显示

        ui->textBrowser->insertPlainText(addr.toString()+":"+QString(arr)+"\n");
        //发送

        ui->lineEdit->setEnabled(true);
        ui->pushButton_send->setEnabled(true);

    });
    //3.绑定
    mSocket->bind(QHostAddress::Any,ui->spinBox->value());

    //禁止端口号和启动按钮
    ui->spinBox->setEnabled(false);
    ui->pushButton_2->setEnabled(false);

}


void Widget::on_pushButton_send_clicked()
{
    //获取发送的数据
    QByteArray arr = ui->lineEdit->text().toUtf8();
    //发送

    mSocket->writeDatagram(arr,addr,port);
    //显示

    ui->textBrowser->insertPlainText("send:"+QString(arr)+"\n");

    ui->lineEdit->clear();

}

