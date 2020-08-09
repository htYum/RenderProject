#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QThread>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>

#include "RenderLoop/renderloop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

public slots:
    void fpsTimeOut();
    void receiveFrameBuffer(unsigned char* image);
private:
    void paintEvent(QPaintEvent* event) override;

    Ui::MainWindow *ui;
    QImage* canvas;
    QTimer* timer;
    QThread* loopThread;
    RenderLoop* renderLoop;

    bool firstMouseMove;
    QPoint lastMousePos;

};
#endif // MAINWINDOW_H
