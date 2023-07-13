#include "ui/setupWizard.h"

SetupWizard::SetupWizard(QWidget* parent)
    : QWizard{parent},
      introPage{new IntroPage{this}},
      installationPage{new InstallationPage{this}},
      filesCreationPage{new FilesCreationPage{this}} {
  this->setWizardStyle(QWizard::ModernStyle);
  this->setWindowTitle("EasyPlay Device Client Installer");
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  this->setOption(QWizard::NoCancelButtonOnLastPage);
  this->setOption(QWizard::NoBackButtonOnStartPage);
  this->setOption(QWizard::NoBackButtonOnLastPage);

  this->addPage(this->introPage);
  this->addPage(this->installationPage);
  this->addPage(this->filesCreationPage);
  // this->addPage(this->introPage);  // TODO: replace
}