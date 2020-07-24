#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , canvas(nullptr)
{
    ui->setupUi(this);

    renderLoop = new RenderLoop(width(), height(), nullptr);
    loopThread = new QThread(this);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(fpsTimeOut()));

    renderLoop->moveToThread(loopThread);
    connect(loopThread, SIGNAL(finished()),renderLoop, SLOT(deleteLater()));
    connect(loopThread, SIGNAL(started()), renderLoop, SLOT(loop()));
    connect(renderLoop, SIGNAL(frameOut(unsigned char*)), this, SLOT(receiveFrameBuffer(unsigned char*)));

    loopThread->start();
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    renderLoop->stop();
    loopThread->quit();
    loopThread->wait();
    delete canvas;
    delete loopThread;
    delete ui;
}

void MainWindow::fpsTimeOut()
{
    int fps = renderLoop->getFps();
    renderLoop->setFpsZero();
    this->setWindowTitle(QString("Render fps: %1").arg(fps));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    if(canvas){
        QPainter painter(this);
        painter.drawImage(0,0,*canvas);
    }
    QMainWindow::paintEvent(event);
}

void MainWindow::receiveFrameBuffer(unsigned char *image)
{
    if(canvas)delete canvas;
    canvas = new QImage(image, width(),height(),QImage::Format_RGBA8888);
    update();
}

