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

    QMainWindow::setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
    case Qt::Key_W:
        renderLoop->processKey('W');
        break;
    case Qt::Key_A:
        renderLoop->processKey('A');
        break;
    case Qt::Key_S:
        renderLoop->processKey('S');
        break;
    case Qt::Key_D:
        renderLoop->processKey('D');
        break;
    case Qt::Key_Q:
        renderLoop->processKey('Q');
        break;
    case Qt::Key_E:
        renderLoop->processKey('E');
        break;
    default:
        break;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton)){
        firstMouseMove = true;
    }
    if(firstMouseMove){
        firstMouseMove = false;
        lastMousePos = event->pos();
    }
    else{
        QPoint delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();
        renderLoop->processMouse(delta.x(), delta.y());
    }
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

