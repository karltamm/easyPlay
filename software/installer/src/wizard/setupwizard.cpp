#include "setupwizard.h"

SetupWizard::SetupWizard(QWidget* parent)
    : QWizard{parent},
      firefoxHandler{new FirefoxHandler(this)},
      artifactsHandler{new ArtifactsHandler(this)},
      introPage{new IntroPage(firefoxHandler, this)},
      installationDestPage{new InstallationDestPage(this)},
      copyPage{new CopyPage(artifactsHandler, firefoxHandler, this)},
      endPage{new EndPage(this)} {
  setWindowTitle("EasyPlay Driver Installer");

  addPage(introPage);
  addPage(installationDestPage);
  addPage(copyPage);
  addPage(endPage);
}
