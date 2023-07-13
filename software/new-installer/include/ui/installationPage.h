#ifndef INSTALLATION_PAGE
#define INSTALLATION_PAGE

#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QWizardPage>

class InstallationPage : public QWizardPage {
  Q_OBJECT
 public:
  explicit InstallationPage(QWidget* parent = nullptr);

 private:
  QGridLayout* layout;
  QLabel* label_dirPickerHeader;
  QLabel* label_selectedDirPath;
  QPushButton* btn_selectDestDir;

  void initializePage();  // TODO: override
  void setUpGui();
  void handleEvents();
  bool validatePage();  // TODO: override
  void showPopup(const QString& text, QMessageBox::Icon icon, const QString& informativeText = "");
};

#endif  // INSTALLATION_PAGE
