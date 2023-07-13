#ifndef FILES_CREATION_PAGE_H
#define FILES_CREATION_PAGE_H

#include <QFutureWatcher>
#include <QLabel>
#include <QMovie>
#include <QPair>
#include <QTimer>
#include <QVBoxLayout>
#include <QWizardPage>

class FilesCreationPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit FilesCreationPage(QWidget* parent = nullptr);

 signals:
  void copyFinished(bool success);

 private:
  QFutureWatcher<QPair<bool, QString>> copyWatcher;
  quint64 copyAnimationDurationMs;
  QTimer* copyTimer;
  QMovie* movie_loader;
  QLabel* label_loader;
  QVBoxLayout* layout;
  bool filesCopied;

  void initializePage();    // TODO: override
  bool isComplete() const;  // TODO: override
  void setUpGui();
  void createFiles();
};

#endif  // FILES_CREATION_PAGE_H
