#ifndef FILES_CREATION_PAGE_H
#define FILES_CREATION_PAGE_H

#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVBoxLayout>
#include <QWizardPage>

// TODO: mv
#define MIN_LOADER_ANIMATION_DURATION_MS 3000
#define COPY_TIMER_INTERVAL_MS           100

class FilesCreationPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit FilesCreationPage(QWidget* parent = nullptr);

 signals:
  void copyFinished(bool success);

 private:
  quint64 elapsedTime;
  QTimer* copyTimer;
  QMovie* movie_loader;
  QLabel* label_loader;
  QVBoxLayout* layout;
  bool filesCopied;

  void initializePage();
  bool isComplete() const;
  void handleEvents();
  void setUpGui();
  void setUpCopyTimer();
};

#endif  // FILES_CREATION_PAGE_H
