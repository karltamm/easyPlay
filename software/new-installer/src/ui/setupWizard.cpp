#include "ui/setupWizard.h"

SetupWizard::SetupWizard(QWidget* parent)
    : QWizard{parent},
      introPage{new IntroPage{this}},
      installationPage{new InstallationPage{this}} {
  this->setWizardStyle(QWizard::ModernStyle);
  this->setWindowTitle("EasyPlay Device Client Installer");
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setOption(QWizard::NoBackButtonOnStartPage);

  this->addPage(this->introPage);
  this->addPage(this->installationPage);
}