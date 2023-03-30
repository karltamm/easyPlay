#include "endpage.h"

#include <setupwizard.h>

EndPage::EndPage(QWidget* parent)
    : QWizardPage{parent},
      label_feedback{new QLabel(this)},
      layout{new QVBoxLayout(this)} {
  setUpGui();
}

void EndPage::initializePage() {
  if (field(INSTALLATION_FEEDBACK_FIELD).toBool()) {
    label_feedback->setText("✅ Installation was successful");
  } else {
    label_feedback->setText("❌ Installation failed");
  }
}

void EndPage::setUpGui() {
  setTitle("Done");
  label_feedback->setTextFormat(Qt::RichText);
  layout->addWidget(label_feedback);
  setLayout(layout);
}
