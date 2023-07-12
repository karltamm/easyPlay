#ifndef SETUP_WIZARD_H
#define SETUP_WIZARD_H

#include <QWizard>

#include "ui/installationPage.h"
#include "ui/introPage.h"

#define SELECTED_DIR_PATH_FIELD     "selectedDirPath"
#define INSTALLATION_FEEDBACK_FIELD "installationFeedback"

class SetupWizard : public QWizard {
  Q_OBJECT
 public:
  explicit SetupWizard(QWidget* parent = nullptr);

 private:
  IntroPage* introPage;
  InstallationPage* installationPage;
};

#endif  // SETUP_WIZARD_H
