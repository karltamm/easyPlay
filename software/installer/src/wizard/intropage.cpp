#include "intropage.h"

#include <logger.h>

IntroPage::IntroPage(FirefoxHandler* firefoxHandler, QWidget* parent)
    : QWizardPage{parent},
      firefoxHandler{firefoxHandler},
      layout{new QVBoxLayout(this)},
      label_intro{new QLabel(this)},
      label_requirementsHeader{new QLabel(this)},
      label_requirements{new QLabel(this)},
      messageBox{new QMessageBox(this)} {
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
  // TODO: use local scoped Messagebox
  messageBox->setIcon(QMessageBox::Critical);
  messageBox->setText(message);
  messageBox->exec();
}

bool IntroPage::handlePrevInstallation() {
  QString prevDir = artifactsHandler->getPreviousInstallationDir();
  if (prevDir.isEmpty()) {
    return true;
  }
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Warning);

  msgBox.setTextFormat(Qt::RichText);
  msgBox.setText("<b>Detected previous installation</b>");
  msgBox.setDetailedText()  //   TODO: use detailedText
      msgBox.setInformativeText("Delete previous installation?");

  QPushButton* btn_keep = msgBox.addButton("Keep", QMessageBox::RejectRole);  // TODO: update
  QPushButton* btn_delete = msgBox.addButton("Delete", QMessageBox::AcceptRole);
  msgBox.setDefaultButton(btn_keep);

  msgBox.exec();
  return msgBox.clickedButton() == btn_delete;
}
