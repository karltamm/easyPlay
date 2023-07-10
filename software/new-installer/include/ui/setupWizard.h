#ifndef SETUP_WIZARD_H
#define SETUP_WIZARD_H

// TODO: rm
// #include <artifactshandler.h>
// #include <copypage.h>
// #include <endpage.h>
// #include <firefoxhandler.h>
// #include <installationdestpage.h>
// #include <intropage.h>

#include <QWizard>

#include "ui/introPage.h"

// TODO: rm or move
#define SELECTED_DIR_PATH_FIELD     "selectedDirPath"
#define INSTALLATION_FEEDBACK_FIELD "installationFeedback"

class SetupWizard : public QWizard {
  Q_OBJECT
 public:
  explicit SetupWizard(QWidget* parent = nullptr);

 private:
  // TODO: rm
  //   FirefoxHandler* firefoxHandler;
  //   ArtifactsHandler* artifactsHandler;
  IntroPage* introPage;
  //   InstallationDestPage* installationDestPage;
  //   CopyPage* copyPage;
  //   EndPage* endPage;
};

#endif  // SETUP_WIZARD_H
