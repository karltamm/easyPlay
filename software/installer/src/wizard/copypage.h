#ifndef COPYPAGE_H
#define COPYPAGE_H

#include <artifactshandler.h>
#include <QWizardPage>

class CopyPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit CopyPage(ArtifactsHandler* artifactsHandler, QWidget* parent = nullptr);

 private:
  ArtifactsHandler* artifactsHandler;

  void initializePage();  // TODO: rm
  void handleEvents();
};

#endif  // COPYPAGE_H
