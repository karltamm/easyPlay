#include "copypage.h"

#include <logger.h>
#include <setupwizard.h>
#include <QDir>

CopyPage::CopyPage(ArtifactsHandler* artifactsHandler, FirefoxHandler* firefoxHandler, QWidget* parent)
    : QWizardPage{parent},
      artifactsHandler{artifactsHandler},
      firefoxHandler{firefoxHandler},
      filesCopied{false},
      copyTimer{new QTimer(this)},
      elapsedTime{0},
      movie_loader{new QMovie(this)},
      label_loader{new QLabel(this)},
      layout{new QVBoxLayout(this)} {
  setUpGui();
  handleEvents();
  registerField(INSTALLATION_FEEDBACK_FIELD, new QLabel(this), "text");
}

void CopyPage::initializePage() {
  emit artifactsHandler->copyArtifacts(field(SELECTED_DIR_PATH_FIELD).toString());
  setUpCopyTimer();
}

bool CopyPage::isComplete() const {
  // When files are copied, then next page is shown automatically
  // This method prevents user clicking on "Next" button
  return false;
}

void CopyPage::setUpGui() {
  setTitle("Installing");

  label_loader->setMovie(movie_loader);
  label_loader->setTextFormat(Qt::RichText);

  movie_loader->setFileName(":/img/installation-loader.gif");
  movie_loader->start();

  layout->addWidget(label_loader);
  layout->setAlignment(label_loader, Qt::AlignCenter);
  setLayout(layout);
}

void CopyPage::handleEvents() {
  connect(artifactsHandler->copyHandler, &CopyHandler::copyResult, this, [this](bool success) {
    if (success) {
      filesCopied = true;
      return;
    }
    emit copyFinished(false);
  });

  connect(this, &CopyPage::copyFinished, this, [this](bool success) {
    copyTimer->stop();
    setField(INSTALLATION_FEEDBACK_FIELD, QVariant(success));
    if (success) {
      QString destDir = field(SELECTED_DIR_PATH_FIELD).toString();
      QString manifestPath = QDir::cleanPath(destDir + QDir::separator() + NATIVE_APP_MANIFEST_FILE_NAME);
      firefoxHandler->addNativeAppManifest(manifestPath);
    }
    wizard()->next();
  });
}

void CopyPage::setUpCopyTimer() {
  connect(copyTimer, &QTimer::timeout, this, [this]() {
    if (!filesCopied || elapsedTime < MIN_LOADER_ANIMATION_DURATION_MS) {
      elapsedTime += COPY_TIMER_INTERVAL_MS;
      return;
    }
    emit copyFinished(true);
  });
  copyTimer->start(COPY_TIMER_INTERVAL_MS);
}
