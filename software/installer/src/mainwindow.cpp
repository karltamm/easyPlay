#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), firefoxHandler(new FirefoxHandler(this)) {
  ui->setupUi(this);
  qDebug() << "isFirefoxInstalled:" << firefoxHandler->isFirefoxInstalled();  // TODO: rm
}

MainWindow::~MainWindow() {
  delete ui;
}
