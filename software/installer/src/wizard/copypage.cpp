#include "copypage.h"

#include <logger.h>
#include <setupwizard.h>

CopyPage::CopyPage(ArtifactsHandler* artifactsHandler, QWidget* parent)
    : QWizardPage{parent},
      artifactsHandler{artifactsHandler} {
  handleEvents();
}

void CopyPage::initializePage() {  // TODO:rm
  QStringList files = {DRIVER_EXE_FILE_NAME, NATIVE_APP_MANIFEST_FILE_NAME};
  emit artifactsHandler->copyHandler->requestCopy(files, field(SELECTED_DIR_PATH_FIELD).toString());
}

void CopyPage::handleEvents() {
  connect(artifactsHandler->copyHandler, &CopyHandler::copyResult, this, [](bool success) {
    qDebug() << "copy result:" << success;  // TODO: rm
    // TODO: implement
  });
}
