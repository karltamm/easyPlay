#ifndef SETUP_WIZARD_H
#define SETUP_WIZARD_H

#include <QWizard>

#include "ui/installationPage.h"
#include "ui/introPage.h"

class SetupWizard : public QWizard {
  Q_OBJECT
 public:
  explicit SetupWizard(QWidget* parent = nullptr);

 private:
  IntroPage* introPage;
  InstallationPage* installationPage;
};

#endif  // SETUP_WIZARD_H
