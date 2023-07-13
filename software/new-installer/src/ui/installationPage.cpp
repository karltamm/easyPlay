#include "ui/installationPage.h"

#include <QDebug>  // TODO: change to logger
#include <QDir>
#include <QFileDialog>

#include "clientHandler.h"
#include "firefoxHandler.h"
#include "ui/setupWizard.h"

InstallationPage::InstallationPage(QWidget* parent)
    : QWizardPage{parent},
      layout{new QGridLayout{this}},
      label_dirPickerHeader{new QLabel{this}},
      label_selectedDirPath{new QLabel{this}},
      btn_selectDestDir{new QPushButton{this}} {
  this->clientDestDir = QDir::homePath() + "/EasyPlay";
  this->setUpGui();
  this->handleEvents();
}

void InstallationPage::initializePage() {
  this->wizard()->setButtonText(QWizard::FinishButton, "Install");
}

void InstallationPage::setUpGui() {
  this->setTitle("Installation destination");

  this->label_dirPickerHeader->setText("Selected folder");
  this->label_dirPickerHeader->setStyleSheet("font-weight:bold");

  this->label_selectedDirPath->setText(this->clientDestDir);
  this->label_selectedDirPath->setWordWrap(true);

  this->btn_selectDestDir->setText("Select Folder");

  this->layout->addWidget(label_dirPickerHeader, 0, 0);
  this->layout->addWidget(label_selectedDirPath, 1, 0);
  this->layout->addWidget(btn_selectDestDir, 1, 1);
  this->setLayout(layout);
}

void InstallationPage::handleEvents() {
  QObject::connect(this->btn_selectDestDir, &QPushButton::clicked, this, [this]() {
    QString dirPath = QFileDialog::getExistingDirectory(this,
                                                        "Select folder",
                                                        QDir::homePath(),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!QDir{}.exists(dirPath)) {
      return;
    }

    this->clientDestDir = dirPath;
    this->label_selectedDirPath->setText(this->clientDestDir);
  });
}

bool InstallationPage::validatePage() {
  QDir destDir{this->clientDestDir};

  if (destDir.exists() and !destDir.isEmpty()) {
    this->showPopup("Selected folder is not empty", QMessageBox::Critical, "<b>Select empty folder</b>");
    return false;
  }

  if (!destDir.mkpath(this->clientDestDir)) {
    this->showPopup("Couldn't create installation folder", QMessageBox::Critical);
    return false;
  }

  QFuture<QPair<bool, QString>> copyResult = ClientHandler::copyClientFile(this->clientDestDir);
  copyResult.waitForFinished();

  if (!copyResult.result().first) {
    this->showPopup("Couldn't create device client", QMessageBox::Critical);
    return false;
  }

  if (!FirefoxHandler::createNativeAppManifest(FirefoxHandler::getNativeAppManifestDir().path(), copyResult.result().second)) {
    this->showPopup("Couldn't create Firefox native app manifest", QMessageBox::Critical);
    ClientHandler::deleteExistingClientDir();
    return false;
  }

  this->showPopup("✅ Success", QMessageBox::Information);

  return true;
}

void InstallationPage::showPopup(const QString& text, QMessageBox::Icon icon, const QString& informativeText) {
  QMessageBox msgBox;

  msgBox.setTextFormat(Qt::RichText);
  msgBox.setIcon(icon);
  msgBox.setText(text);
  msgBox.setInformativeText(informativeText);

  msgBox.exec();
}