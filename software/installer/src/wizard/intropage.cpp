#include "intropage.h"

#include <logger.h>
#include <QPushButton>

IntroPage::IntroPage(ArtifactsHandler* artifactsHandler, FirefoxHandler* firefoxHandler, QWidget* parent)
    : QWizardPage{parent},
      artifactsHandler{artifactsHandler},
      firefoxHandler{firefoxHandler},
      layout{new QVBoxLayout(this)},
      label_intro{new QLabel(this)},
      label_requirementsHeader{new QLabel(this)},
      label_requirements{new QLabel(this)} {
  setUpGui();
}

void IntroPage::setUpGui() {
  setTitle("Introduction");

  label_intro->setText(
      "This installation wizard sets up EasyPlay driver.\n"
      "Driver allows the Firefox extension to communicate with the device.\n");
  label_intro->setWordWrap(true);

  label_requirementsHeader->setText("Requirements");
  label_requirementsHeader->setStyleSheet("font-weight:bold");

  label_requirements->setTextFormat(Qt::RichText);
  label_requirements->setText(
      "<ul>"
      "<li>Firefox Browser</li>"
      "<li>Java Runtime Environment</li>"  // TODO: check which JRE version is correct
      "</ul>");

  layout->addWidget(label_intro);
  layout->addWidget(label_requirementsHeader);
  layout->addWidget(label_requirements);
  setLayout(layout);
}

bool IntroPage::validatePage() {
  if (!firefoxHandler->isFirefoxInstalled()) {
    showErrorMessage("Install Firefox to continue");
    return false;
  }
  if (!handlePrevInstallation()) {
    return false;
  }
  // TODO: check if Java is installed
  return true;
}

void IntroPage::showErrorMessage(QString message) {
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.setTextFormat(Qt::RichText);
  msgBox.setText(QString("<b>%1<b>").arg(message));  // TODO: set bold every message box
  msgBox.exec();
}

bool IntroPage::handlePrevInstallation() {
  QDir prevDir = artifactsHandler->getPreviousInstallationDir();
  if (!prevDir.exists()) {
    return true;
  }
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Warning);

  msgBox.setTextFormat(Qt::RichText);
  msgBox.setText("Detected previous installation");
  msgBox.setDetailedText(QString("Installed at %1").arg(prevDir.path()));
  msgBox.setInformativeText("<b>Delete previous installation?</b>");

  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::Yes);

  if (msgBox.exec() == QMessageBox::No) {
    return false;
  }
  if (!artifactsHandler->deletePreviousInstallation()) {
    showErrorMessage("Couldn't delete previous installation");
    return false;
  }
  return true;
}
