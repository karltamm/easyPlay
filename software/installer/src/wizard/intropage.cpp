#include "intropage.h"

#include <logger.h>
#include <QPushButton>

IntroPage::IntroPage(ArtifactsHandler* artifactsHandler, FirefoxHandler* firefoxHandler, QWidget* parent)
    : QWizardPage{parent},
      artifactsHandler{artifactsHandler},
      firefoxHandler{firefoxHandler},
      javaHandler{new JavaHandler(this)},
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
  label_requirements->setText(QString("<ul>"
                                      "<li>Firefox Browser</li>"
                                      "<li>Java Runtime Environment %1</li>"
                                      "</ul>")
                                  .arg(JRE_MIN_VERSION));

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
  if (!javaHandler->isSuitableJreInstalled(JRE_MIN_VERSION)) {
    showErrorMessage(QString("Install Java Runtime Environment %1 or later").arg(JRE_MIN_VERSION));
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
    showErrorMessage("Couldn't delete previous installation. Close Firefox if open.");
    return false;
  }
  return true;
}
