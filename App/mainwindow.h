#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeUniverse.h"
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TreeUniverse *tu;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

signals:
    void close();
};

#endif // MAINWINDOW_H
