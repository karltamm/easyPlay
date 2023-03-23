#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <artifactshandler.h>
#include <firefoxhandler.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:
  void installPathSelected(QString path);

 private:
  Ui::MainWindow* ui;
  FirefoxHandler* firefoxHandler;
  ArtifactsHandler* artifactsHandler;

  void handleEvents();
};
#endif  // MAINWINDOW_H
