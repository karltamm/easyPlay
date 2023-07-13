#include "ui/filesCreationPage.h"

#include <QDebug>  // TODO: use logger
#include <QDir>

#include "clientHandler.h"
#include "firefoxHandler.h"
#include "ui/setupWizard.h"

#define MIN_COPY_ANIMATION_DURATION_MS 3000
#define COPY_TIMER_INTERVAL_MS         100

FilesCreationPage::FilesCreationPage(QWidget* parent)
    : QWizardPage{parent},
      filesCopied{false},
      copyTimer{new QTimer{this}},
      copyAnimationDurationMs{0},
      movie_loader{new QMovie{this}},
      label_loader{new QLabel{this}},
      layout{new QVBoxLayout{this}} {
  this->setUpGui();
  this->registerField(INSTALLATION_FEEDBACK_FIELD, new QLabel{this}, "text");
}

void FilesCreationPage::initializePage() {
  this->setCommitPage(true);
  this->wizard()->setOption(QWizard::NoCancelButton);

  this->createFiles();
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

  this->movie_loader->setFileName(":/installation-loader.gif");  // TODO: add resource
  this->movie_loader->start();

  this->layout->addWidget(label_loader);
  this->layout->setAlignment(label_loader, Qt::AlignCenter | Qt::AlignVCenter);
  this->setLayout(layout);
}

void FilesCreationPage::createFiles() {
  const auto destDirPath = this->field(SELECTED_DIR_PATH_FIELD).toString();

  QObject::connect(this->copyTimer, &QTimer::timeout, this, [this, &destDirPath]() {
    this->copyAnimationDurationMs += COPY_TIMER_INTERVAL_MS;

    if (this->copyWatcher.isRunning() or this->copyAnimationDurationMs < MIN_COPY_ANIMATION_DURATION_MS) {
      qDebug() << "Increase copy timer";  // TODO: rm
      return;
    }

    this->copyTimer->stop();

    if (!this->copyWatcher.result().first) {
      this->setField(INSTALLATION_FEEDBACK_FIELD, QVariant{false});
      this->wizard()->next();
      return;
    }

    qDebug() << "Now create native manifest";  // TODO: rm

    qDebug() << "destDirPath" << destDirPath;  // TODO: rm

    if (!FirefoxHandler::createNativeManifest("", this->copyWatcher.result().second)) {  // TODO: rename nativeAppManifest
      this->setField(INSTALLATION_FEEDBACK_FIELD, QVariant{false});
    }

    this->wizard()->next();
  });

  this->copyWatcher.setFuture(ClientHandler::copyClientFile(destDirPath));
  this->copyTimer->start(COPY_TIMER_INTERVAL_MS);
}