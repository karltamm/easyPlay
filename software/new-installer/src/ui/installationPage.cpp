#include "ui/installationPage.h"

#include <QDebug>  // TODO: change to logger
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

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
  this->setButtonText(QWizard::CommitButton, "Install");
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
  QString destDirPath = this->field(SELECTED_DIR_PATH_FIELD).toString();
  QDir destDir{destDirPath};

  if (!destDir.exists()) {
    if (!destDir.mkpath(label_selectedDirPath->text())) {
      QMessageBox msgBox;
      msgBox.setTextFormat(Qt::RichText);
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.setText("<b>Couldn't create installation folder</b>");
      msgBox.exec();

      return false;
    }

    return true;
  }

  if (!destDir.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Selected folder is not empty");
    msgBox.setInformativeText("<b>Select empty folder</b>");
    msgBox.exec();

    return false;
  }

  return true;
}
