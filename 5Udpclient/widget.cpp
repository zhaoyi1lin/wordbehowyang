
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    mSocket = new QUdpSocket(this);

    QObject::connect(mSocket,&QUdpSocket::readyRead,this,[&](){

        QHostAddress addr;
        quint16 port;

        QByteArray arr;
        arr.resize(mSocket->bytesAvailable());
        mSocket->readDatagram(arr.data(),arr.size(),&addr,&port);

        ui->textBrowser->insertPlainText(addr.toString()+":"+QString(arr)+"\n");


    ui->setupUi(this);
}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_send_clicked()
{
    QByteArry arr = ui
}

