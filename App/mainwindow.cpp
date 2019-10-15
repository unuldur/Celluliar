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
    mode->addAction(ui->actionSelection);
    connect(ui->actionBrush, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::BRUSH);});
    connect(ui->actionErase, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::ERASED);});
    connect(ui->actionRandom, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::RANDOM);});
    connect(ui->actionSelection, &QAction::triggered, [this](){ui->centralWidget->changeMode(LifeDrawing::Mode::SELECTION);});
    connect(ui->actionRun_once, &QAction::triggered, [this](){tu->runStep(); ui->centralWidget->update();});

    connect(ui->actionFill, &QAction::triggered, [this](){
        ui->centralWidget->selectionUse(SelectionMode::SelectionType::FULL);});
    connect(ui->actionDelete, &QAction::triggered, [this](){
        ui->centralWidget->selectionUse(SelectionMode::SelectionType::ERASED);});
    connect(ui->actionRandomSelect, &QAction::triggered, [this](){
        ui->centralWidget->selectionUse(SelectionMode::SelectionType::RANDOM);});

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
    connect(this, &MainWindow::close, [thread](){
        thread->wakeUp();
        thread->exit();
        delete thread;
    });
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit close();
    event->accept();
}


