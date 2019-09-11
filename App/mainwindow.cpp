#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "runthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tu(new TreeUniverse())
{
    ui->setupUi(this);
    ui->centralWidget->setTreeUnivers(tu);
    QActionGroup * mode = new QActionGroup(ui->menuTools);
    mode->addAction(ui->actionBrush);
    mode->addAction(ui->actionErase);
    mode->addAction(ui->actionRandom);
    connect(ui->actionBrush, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::BRUSH);});
    connect(ui->actionErase, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::ERASED);});
    connect(ui->actionRandom, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::RANDOM);});
    connect(ui->actionRun_once, &QAction::triggered, [this](){tu->runStep(); ui->centralWidget->update();});

    RunThread* thread = new RunThread(this, tu);
    connect(ui->actionRun, &QAction::triggered, [this, thread](){
        ui->centralWidget->setInAction(true);
        ui->actionPause->setEnabled(true);
        ui->actionRun->setEnabled(false);
        thread->wakeUp();
    });
    connect(thread, &RunThread::update, [this](){ui->centralWidget->update();});
    connect(ui->actionPause, &QAction::triggered,[this, thread](){
        ui->centralWidget->setInAction(false);
        ui->actionPause->setEnabled(false);
        ui->actionRun->setEnabled(true);
        thread->pause();
    });
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


