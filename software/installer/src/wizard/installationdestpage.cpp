#include "installationdestpage.h"

#include <logger.h>
#include <setupwizard.h>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

InstallationDestPage::InstallationDestPage(QWidget* parent)
    : QWizardPage{parent},
      layout{new QGridLayout(this)},
      label_dirPickerHeader{new QLabel(this)},
      label_selectedDirPath{new QLabel(this)},
      btn_selectDestDir{new QPushButton(this)} {
  setUpGui();
  handleEvents();

  registerField(SELECTED_DIR_PATH_FIELD, label_selectedDirPath, "text");
  setField(SELECTED_DIR_PATH_FIELD, QVariant(DEFAULT_DEST_DIR_PATH));

  setCommitPage(true);
}

void InstallationDestPage::setUpGui() {
  setTitle("Installation destination");

  label_dirPickerHeader->setText("Selected folder");
  label_dirPickerHeader->setStyleSheet("font-weight:bold");

  label_selectedDirPath->setText(DEFAULT_DEST_DIR_PATH);
  label_selectedDirPath->setWordWrap(true);

  btn_selectDestDir->setText("Select Folder");

  layout->addWidget(label_dirPickerHeader, 0, 0);
  layout->addWidget(label_selectedDirPath, 1, 0);
  layout->addWidget(btn_selectDestDir, 1, 1);
  setLayout(layout);
}

void InstallationDestPage::handleEvents() {
  connect(btn_selectDestDir, &QPushButton::clicked, this, [this]() {
    QString destDir = QFileDialog::getExistingDirectory(this,
                                                        "Select folder",
                                                        PROGRAM_FILES_X86_DIR_PATH,
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!QDir().exists(destDir)) {
      return;
    }
    label_selectedDirPath->setText(destDir);
    setField(SELECTED_DIR_PATH_FIELD, QVariant(destDir));
  });
}

bool InstallationDestPage::validatePage() {
  QDir destDir(label_selectedDirPath->text());
  if (!destDir.exists()) {
    if (!destDir.mkpath(label_selectedDirPath->text())) {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.setText("Couldn't create installation folder");
      msgBox.exec();
      return false;
    }
    return true;
  }
  if (!destDir.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Selected folder is not empty");
    msgBox.setInformativeText("Select empty folder");
    msgBox.exec();
    return false;
  }
  return true;
}

// TODO: add uninstall option
