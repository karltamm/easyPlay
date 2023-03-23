#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <artifactshandler.h>
#include <firefoxhandler.h>
#include <installationdestpage.h>
#include <intropage.h>
#include <QWizard>

class SetupWizard : public QWizard {
  Q_OBJECT
 public:
  explicit SetupWizard(QWidget* parent = nullptr);

 private:
  FirefoxHandler* firefoxHandler;
  ArtifactsHandler* artifactsHandler;
  IntroPage* introPage;
  InstallationDestPage* installationDestPage;
};

// TODO: rm "?" from GUI

#endif  // SETUPWIZARD_H
