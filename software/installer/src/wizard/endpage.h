#ifndef ENDPAGE_H
#define ENDPAGE_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWizardPage>

class EndPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit EndPage(QWidget* parent = nullptr);

 private:
  QLabel* label_feedback;
  QVBoxLayout* layout;

  void initializePage();
  void setUpGui();
};

#endif  // ENDPAGE_H
