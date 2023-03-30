#include "setupwizard.h"

SetupWizard::SetupWizard(QWidget* parent)
    : QWizard{parent},
      firefoxHandler{new FirefoxHandler(this)},
      artifactsHandler{new ArtifactsHandler(this)},
      introPage{new IntroPage(artifactsHandler, firefoxHandler, this)},
      installationDestPage{new InstallationDestPage(this)},
      copyPage{new CopyPage(artifactsHandler, firefoxHandler, this)},
      endPage{new EndPage(this)} {
  setWizardStyle(QWizard::ModernStyle);
  setWindowTitle("EasyPlay Driver Installer");
  setOption(QWizard::NoCancelButtonOnLastPage);
  setOption(QWizard::NoBackButtonOnStartPage);
  setOption(QWizard::NoBackButtonOnLastPage);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  addPage(introPage);
  addPage(installationDestPage);
  addPage(copyPage);
  addPage(endPage);
}
