#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

typedef struct {
    int time_ms;
    qreal value_ch[8];
}__attribute__((packed, aligned(4))) Packet;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udp_server;
    QTimer *timer;
    QTime *time;

private slots:
    void slotSendDatagramm();
    void on_spinBox_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
