#ifndef INSTALLATIONDESTPAGE_H
#define INSTALLATIONDESTPAGE_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QWizardPage>

#define PROGRAM_FILES_X86_DIR_PATH "C:/Program Files (x86)/"
#define DEFAULT_DEST_DIR_PATH      PROGRAM_FILES_X86_DIR_PATH "EasyPlay"

class InstallationDestPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit InstallationDestPage(QWidget* parent = nullptr);

 private:
  QGridLayout* layout;
  QLabel* label_dirPickerHeader;
  QLabel* label_selectedDirPath;
  QPushButton* btn_selectDestDir;

  void setUpGui();
  void handleEvents();
  bool validatePage();
  bool useExistingDir();
};

#endif  // INSTALLATIONDESTPAGE_H
