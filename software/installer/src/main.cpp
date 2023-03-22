#include "mainwindow.h"

#include <Windows.h>
#include <QApplication>
#include <QDebug>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  HKEY key;
  auto result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Mozilla\\Mozilla Firefox 111.0\\bin"), 0, KEY_QUERY_VALUE, &key);
  if (result != ERROR_SUCCESS) {
    if (result == ERROR_FILE_NOT_FOUND) {
      qDebug() << "\nKey not found";
    } else {
      qDebug() << "\nError opening key";
    }
  }

  return a.exec();
}
