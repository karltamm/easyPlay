#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <artifactshandler.h>
#include <firefoxhandler.h>
#include <QWizard>

class SetupWizard : public QWizard {
  Q_OBJECT
 public:
  explicit SetupWizard(QWidget* parent = nullptr);

 private:
  FirefoxHandler* firefoxHandler;
  ArtifactsHandler* artifactsHandler;
};

#endif  // SETUPWIZARD_H
