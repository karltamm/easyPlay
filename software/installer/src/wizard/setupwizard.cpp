#include "setupwizard.h"

SetupWizard::SetupWizard(QWidget* parent)
    : QWizard{parent},                               //
      firefoxHandler{new FirefoxHandler(this)},      //
      artifactsHandler{new ArtifactsHandler(this)},  //
      introPage{new IntroPage(firefoxHandler, this)} {
  addPage(introPage);
  setWindowTitle("EasyPlay Driver Installer");
}

// TODO: rename install to dest
// TODO: check if java is installed. if not, abort the installer and show message
// TODO: when installing program, save installation path to registry value
// TODO: pass installation path to firefox handler, so it could add needed key/value to registry
// TODO: check if program is already installed when installing
// TODO: if program is already installed, then delete program folder based on the registry key
