#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <artifactshandler.h>
#include <firefoxhandler.h>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWizardPage>

class IntroPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit IntroPage(ArtifactsHandler* artifactsHandler, FirefoxHandler* firefoxHandler, QWidget* parent = nullptr);

 private:
  ArtifactsHandler* artifactsHandler;
  FirefoxHandler* firefoxHandler;
  QVBoxLayout* layout;
  QLabel* label_intro;
  QLabel* label_requirementsHeader;
  QLabel* label_requirements;

  void setUpGui();
  bool validatePage();
  void showErrorMessage(QString message);
  bool handlePrevInstallation();
};

#endif  // INTROPAGE_H
