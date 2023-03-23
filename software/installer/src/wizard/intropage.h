#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWizardPage>

class IntroPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit IntroPage(QWidget* parent = nullptr);

 private:
  QVBoxLayout* layout;
  QLabel* label_intro;
  QLabel* label_requirementsHeader;
  QLabel* label_requirements;

  void setUpGui();
};

#endif  // INTROPAGE_H
