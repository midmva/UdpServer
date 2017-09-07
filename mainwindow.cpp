#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QtMath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    udp_server(new QUdpSocket(this)),
    timer(new QTimer(this)),
    time(new QTime())
{
    ui->setupUi(this);
    QObject::connect(timer,&QTimer::timeout,this,&MainWindow::slotSendDatagramm);
    time->start();
    timer->start(40);
}

MainWindow::~MainWindow()
{
    timer->stop();
    timer->deleteLater();
    delete time;
    udp_server->deleteLater();
    delete ui;
}

void MainWindow::slotSendDatagramm()
{
    static int i;
    for (int j = 0; j<1;j++){
        Packet packet;
        packet.time_ms = time->elapsed();
        packet.value_ch[0] = (qreal)qCos(M_PI / 150 * (i)+0*0.25*M_PI) * 100;//+ui->verticalSlider_1->value()*0.00001*qrand();
        packet.value_ch[1] = (qreal)qCos(M_PI / 50 * (i)+1*0.25*M_PI) * 100;//+ui->verticalSlider_2->value()*0.00001*qrand();
        packet.value_ch[2] = (qreal)qCos(M_PI / 50 * (i)+2*0.25*M_PI) * 100;//+ui->verticalSlider_3->value()*0.00001*qrand();
        packet.value_ch[3] = (qreal)qCos(M_PI / 50 * (i)+3*0.25*M_PI) * 100;//+ui->verticalSlider_4->value()*0.00001*qrand();
        packet.value_ch[4] = (qreal)qCos(M_PI / 50 * (i)+4*0.25*M_PI) * 100;//+ui->verticalSlider_5->value()*0.00001*qrand();
        packet.value_ch[5] = (qreal)qCos(M_PI / 50 * (i)+5*0.25*M_PI) * 100;//+ui->verticalSlider_6->value()*0.00001*qrand();
        packet.value_ch[6] = (qreal)qCos(M_PI / 50 * (i)+6*0.25*M_PI) * 100;//+ui->verticalSlider_7->value()*0.00001*qrand();
        packet.value_ch[7] = (qreal)qCos(M_PI / 50 * (i)+7*0.25*M_PI) * 100;//+ui->verticalSlider_8->value()*0.00001*qrand();
        i++;
        QByteArray baDatagram(reinterpret_cast<const char*>(&packet),sizeof(Packet));
        udp_server->writeDatagram(baDatagram, QHostAddress::LocalHost, 48660);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    timer->setInterval(arg1);
}
