#include "ui/introPage.h"

// #include <logger.h> // TODO: enable
#include <QPushButton>

IntroPage::IntroPage(QWidget* parent)
    : QWizardPage{parent},
      layout{new QVBoxLayout(this)},
      label_intro{new QLabel(this)},
      label_requirementsHeader{new QLabel(this)},
      label_requirements{new QLabel(this)} {
  setUpGui();
}

void IntroPage::setUpGui() {
  this->setTitle("Introduction");

  this->label_intro->setText(
      "This installation wizard sets up EasyPlay driver.\n"
      "Driver allows the Firefox extension to communicate with the device.\n");
  this->label_intro->setWordWrap(true);

  this->label_requirementsHeader->setText("Requirements");
  this->label_requirementsHeader->setStyleSheet("font-weight:bold");

  this->label_requirements->setTextFormat(Qt::RichText);
  this->label_requirements->setText("<ul><li>Firefox Browser</li></ul>");  // TODO: if browser is present then show check mark

  this->layout->addWidget(this->label_intro);
  this->layout->addWidget(this->label_requirementsHeader);
  this->layout->addWidget(this->label_requirements);

  this->setLayout(this->layout);
}

bool IntroPage::validatePage() {
  // TODO: fix
  //   if (!firefoxHandler->isFirefoxInstalled()) {
  //     showErrorMessage("Install Firefox to continue");
  //     return false;
  //   }

  if (!this->handlePrevInstallation()) {
    return false;
  }

  return true;
}

void IntroPage::showErrorMessage(QString message) {
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.setTextFormat(Qt::RichText);
  msgBox.setText(QString("<b>%1<b>").arg(message));
  msgBox.exec();
}

bool IntroPage::handlePrevInstallation() {
  // TODO: fix
  //   QDir prevDir = artifactsHandler->getPreviousInstallationDir();
  //   if (!prevDir.exists()) {
  //     return true;
  //   }
  //   QMessageBox msgBox;
  //   msgBox.setIcon(QMessageBox::Warning);

  //   msgBox.setTextFormat(Qt::RichText);
  //   msgBox.setText("Detected previous installation");
  //   msgBox.setDetailedText(QString("Installed at %1").arg(prevDir.path()));
  //   msgBox.setInformativeText("<b>Delete previous installation?</b>");

  //   msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  //   msgBox.setDefaultButton(QMessageBox::Yes);

  //   if (msgBox.exec() == QMessageBox::No) {
  //     return true;
  //   }

  //   if (!artifactsHandler->deletePreviousInstallation()) {
  //     showErrorMessage("Couldn't delete previous installation. Close Firefox if open.");
  //     return false;
  //   }

  return true;
}
