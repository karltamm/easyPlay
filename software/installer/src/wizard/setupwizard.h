#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <artifactshandler.h>
#include <copypage.h>
#include <endpage.h>
#include <firefoxhandler.h>
#include <installationdestpage.h>
#include <intropage.h>
#include <QWizard>

#define SELECTED_DIR_PATH_FIELD     "selectedDirPath"
#define INSTALLATION_FEEDBACK_FIELD "installationFeedback"

class SetupWizard : public QWizard {
  Q_OBJECT
 public:
  explicit SetupWizard(QWidget* parent = nullptr);

 private:
  FirefoxHandler* firefoxHandler;
  ArtifactsHandler* artifactsHandler;
  IntroPage* introPage;
  InstallationDestPage* installationDestPage;
  CopyPage* copyPage;
  EndPage* endPage;
};

// TODO: rm "?" from GUI

#endif  // SETUPWIZARD_H
