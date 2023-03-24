#ifndef COPYPAGE_H
#define COPYPAGE_H

#include <artifactshandler.h>
#include <firefoxhandler.h>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVBoxLayout>
#include <QWizardPage>

#define MIN_LOADER_ANIMATION_DURATION_MS 3000
#define COPY_TIMER_INTERVAL_MS           100

class CopyPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit CopyPage(ArtifactsHandler* artifactsHandler, FirefoxHandler* firefoxHandler, QWidget* parent = nullptr);

 signals:
  void copyFinished(bool success);

 private:
  ArtifactsHandler* artifactsHandler;
  FirefoxHandler* firefoxHandler;
  bool filesCopied;
  QTimer* copyTimer;
  quint64 elapsedTime;
  QMovie* movie_loader;
  QLabel* label_loader;
  QVBoxLayout* layout;

  void initializePage();
  bool isComplete() const;
  void handleEvents();
  void setUpGui();
  void setUpCopyTimer();
};

#endif  // COPYPAGE_H
