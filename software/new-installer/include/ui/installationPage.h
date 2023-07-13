#ifndef INSTALLATION_PAGE
#define INSTALLATION_PAGE

#include <QGridLayout>
#include <QLabel>
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
};

#endif  // INSTALLATION_PAGE
