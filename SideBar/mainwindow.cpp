#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sidebardockwidget.h"

#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addDockWidget(Qt::LeftDockWidgetArea, new SideBarDockWidget(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    qDebug() << "MainWindow::mousePressEvent()";
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    qDebug() << "MainWindow::mouseReleaseEvent()";
}

bool MainWindow::event(QEvent* e) {
    if (e->type() == QEvent::MouseButtonRelease) {
        qDebug() << "MainWindow::EVENT RELEASE";
    }
    return QMainWindow::event(e);
}
