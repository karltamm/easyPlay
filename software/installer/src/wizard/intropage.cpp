#include "intropage.h"

#include <QPushButton>  // TODO: rm

IntroPage::IntroPage(QWidget* parent)
    : QWizardPage{parent},                         //
      layout{new QVBoxLayout(this)},               //
      label_intro{new QLabel(this)},               //
      label_requirementsHeader{new QLabel(this)},  //
      label_requirements{new QLabel(this)} {
  setUpGui();
}

void IntroPage::setUpGui() {
  setTitle("Introduction");

  label_intro->setText(
      "This installation wizard sets up EasyPlay driver.\n"
      "Driver allows the Firefox extension to communicate with the device.\n");
  label_intro->setWordWrap(true);

  label_requirementsHeader->setText("Requirements");
  label_requirementsHeader->setStyleSheet("font-weight:bold");

  label_requirements->setTextFormat(Qt::RichText);
  label_requirements->setText(
      "<ul>"
      "<li>Firefox Browser</li>"
      "<li>Java Runtime Environment</li>"  // TODO: check which JRE version is correct
      "</ul>");

  layout->addWidget(label_intro);
  layout->addWidget(label_requirementsHeader);
  layout->addWidget(label_requirements);
  setLayout(layout);
}
