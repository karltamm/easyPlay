#include "ui/installationPage.h"

#include <QDebug>  // TODO: change to logger
#include <QDir>
#include <QFileDialog>

#include "clientHandler.h"
#include "firefoxHandler.h"
#include "ui/setupWizard.h"

#define DEFAULT_DEST_DIR_PATH      \
  QString {                        \
    QDir::homePath() + "/EasyPlay" \
  }

InstallationPage::InstallationPage(QWidget* parent)
    : QWizardPage{parent},
      layout{new QGridLayout{this}},
      label_dirPickerHeader{new QLabel{this}},
      label_selectedDirPath{new QLabel{this}},
      btn_selectDestDir{new QPushButton{this}} {
  this->setUpGui();
  this->handleEvents();

  this->registerField(SELECTED_DIR_PATH_FIELD, label_selectedDirPath, "text");
  this->setField(SELECTED_DIR_PATH_FIELD, QVariant(DEFAULT_DEST_DIR_PATH));

  this->setCommitPage(true);
}

void InstallationPage::initializePage() {
  this->wizard()->setButtonText(QWizard::CommitButton, "Install");
}

void InstallationPage::setUpGui() {
  this->setTitle("Installation destination");

  this->label_dirPickerHeader->setText("Selected folder");
  this->label_dirPickerHeader->setStyleSheet("font-weight:bold");

  this->label_selectedDirPath->setText(DEFAULT_DEST_DIR_PATH);
  this->label_selectedDirPath->setWordWrap(true);

  this->btn_selectDestDir->setText("Select Folder");

  this->layout->addWidget(label_dirPickerHeader, 0, 0);
  this->layout->addWidget(label_selectedDirPath, 1, 0);
  this->layout->addWidget(btn_selectDestDir, 1, 1);
  this->setLayout(layout);
}

void InstallationPage::handleEvents() {
  QObject::connect(this->btn_selectDestDir, &QPushButton::clicked, this, [this]() {
    QString destDir = QFileDialog::getExistingDirectory(this,
                                                        "Select folder",
                                                        QDir::homePath(),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!QDir{}.exists(destDir)) {
      return;
    }

    this->label_selectedDirPath->setText(destDir);
    this->setField(SELECTED_DIR_PATH_FIELD, QVariant{destDir});
  });
}

bool InstallationPage::validatePage() {
  QString destDirPath = this->field(SELECTED_DIR_PATH_FIELD).toString();  // TODO: no need for field

  QDir destDir{destDirPath};

  if (destDir.exists() and !destDir.isEmpty()) {
    this->showPopup("Selected folder is not empty", QMessageBox::Critical, "<b>Select empty folder</b>");
    return false;
  }

  if (!destDir.mkpath(destDirPath)) {
    this->showPopup("Couldn't create installation folder", QMessageBox::Critical);
    return false;
  }

  QFuture<QPair<bool, QString>> copyResult = ClientHandler::copyClientFile(destDirPath);
  copyResult.waitForFinished();

  if (!copyResult.result().first) {
    this->showPopup("Couldn't create device client", QMessageBox::Critical);
    return false;
  }

  if (!FirefoxHandler::createNativeManifest(FirefoxHandler::getNativeAppManifestDir().path(), copyResult.result().second)) {
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