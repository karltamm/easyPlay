#ifndef INTRO_PAGE_H
#define INTRO_PAGE_H

// TODO:rm
// #include <artifactshandler.h>
// #include <firefoxhandler.h>
// #include <javahandler.h>

#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWizardPage>

class IntroPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit IntroPage(QWidget* parent = nullptr);

 private:
  // TODO: rm
  //   JavaHandler* javaHandler;
  //   ArtifactsHandler* artifactsHandler;
  //   FirefoxHandler* firefoxHandler;

  QVBoxLayout* layout;
  QLabel* label_intro;
  QLabel* label_requirementsHeader;
  QLabel* label_requirements;

  void setUpGui();
  bool validatePage();
  void showErrorMessage(QString message);
  bool handlePrevInstallation();
};

#endif  // INTRO_PAGE_H
