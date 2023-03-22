#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <logger.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),  //
      firefoxHandler(new FirefoxHandler(this)),     //
      artifactsHandler(new ArtifactsHandler(this)) {
  ui->setupUi(this);
  qDebug() << "isFirefoxInstalled:" << firefoxHandler->isFirefoxInstalled();  // TODO: rm
  artifactsHandler->copyAllArtifactsToDestDir("C:\\Users\\Karl\\Downloads");  // TODO: rm
}

MainWindow::~MainWindow() {
  delete ui;
}

// TODO: check if java is installed. if not, abort the installer and show message
// TODO: when installing program, save installation path to registry value
// TODO: pass installation path to firefox handler, so it could add needed key/value to registry
// TODO: check if program is already installed when installing
// TODO: if program is already installed, then delete program folder based on the registry key
