#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <firefoxhandler.h>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWizardPage>

class IntroPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit IntroPage(FirefoxHandler* firefoxHandler, QWidget* parent = nullptr);

 private:
  FirefoxHandler* firefoxHandler;
  QVBoxLayout* layout;
  QLabel* label_intro;
  QLabel* label_requirementsHeader;
  QLabel* label_requirements;
  QMessageBox* messageBox;

  void setUpGui();
  bool validatePage();
  void showErrorMessage(QString message);
};

#endif  // INTROPAGE_H
