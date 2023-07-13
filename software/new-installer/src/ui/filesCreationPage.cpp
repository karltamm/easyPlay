#include "ui/filesCreationPage.h"

#include <QDebug>  // TODO: use logger
#include <QDir>

#include "clientHandler.h"
#include "ui/setupWizard.h"

FilesCreationPage::FilesCreationPage(QWidget* parent)
    : QWizardPage{parent},
      filesCopied{false},
      copyTimer{new QTimer{this}},
      elapsedTime{0},
      movie_loader{new QMovie{this}},
      label_loader{new QLabel{this}},
      layout{new QVBoxLayout{this}} {
  this->setUpGui();
  this->handleEvents();
  this->registerField(INSTALLATION_FEEDBACK_FIELD, new QLabel{this}, "text");
}

void FilesCreationPage::initializePage() {
  this->setCommitPage(true);
  this->wizard()->setOption(QWizard::NoCancelButton);
  this->setUpCopyTimer();

  ClientHandler::copyClientFile(field(SELECTED_DIR_PATH_FIELD).toString());
  // TODO: create manifest
}

bool FilesCreationPage::isComplete() const {
  // When files are copied, then next page is shown automatically
  // This method prevents user clicking on "Next" button
  return false;
}

void FilesCreationPage::setUpGui() {
  this->setTitle("Installing");

  this->label_loader->setMovie(movie_loader);
  this->label_loader->setTextFormat(Qt::RichText);

  this->movie_loader->setFileName(":/img/installation-loader.gif");  // TODO: add resource
  this->movie_loader->start();

  this->layout->addWidget(label_loader);
  this->layout->setAlignment(label_loader, Qt::AlignCenter | Qt::AlignVCenter);
  this->setLayout(layout);
}

void FilesCreationPage::handleEvents() {
  // TODO: fix; try to use QFuture
  //   connect(artifactsHandler->copyHandler, &CopyHandler::copyResult, this, [this](bool success) {
  //     if (success) {
  //       filesCopied = true;
  //       return;
  //     }
  //     emit copyFinished(false);
  //   });

  // TODO: fix
  //   connect(this, &FilesCreationPage::copyFinished, this, [this](bool success) {
  //     copyTimer->stop();
  //     setField(INSTALLATION_FEEDBACK_FIELD, QVariant(success));
  //     if (success) {
  //       QString destDir = field(SELECTED_DIR_PATH_FIELD).toString();
  //       QString manifestPath = QDir::cleanPath(destDir + QDir::separator() + NATIVE_APP_MANIFEST_FILE_NAME);
  //       firefoxHandler->addNativeAppManifest(manifestPath);
  //     }
  //     wizard()->next();
  //   });
}

void FilesCreationPage::setUpCopyTimer() {
  // TODO: fix
  //   connect(copyTimer, &QTimer::timeout, this, [this]() {
  //     if (!filesCopied || elapsedTime < MIN_LOADER_ANIMATION_DURATION_MS) {
  //       elapsedTime += COPY_TIMER_INTERVAL_MS;
  //       return;
  //     }
  //     emit copyFinished(true);
  //   });
  //   copyTimer->start(COPY_TIMER_INTERVAL_MS);
}
