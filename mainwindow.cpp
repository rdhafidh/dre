#include "mainwindow.h"

#include <customobyek.h>
#include <formdesign.h>
#include <imageitem.h>
#include <sceneview.h>
#include <tabwidgetutama.h>
#include <textitem.h>
#include <undocommand.h>
#include <QDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_maybeOldTabwidget(nullptr) {
  ui->setupUi(this);
  act_redo = new QAction(tr("Redo"), this);
  act_undo = new QAction(tr("Undo"), this);
  act_redo->setShortcut(QKeySequence(tr("Ctrl+Y")));
  act_undo->setShortcut(QKeySequence(tr("Ctrl+Z")));
  connect(ui->tabWidget, &TabWidgetUtama::currentChanged, [this](int idx) {
    if (idx < 0) return;

    auto widget = ui->tabWidget->currentWidget();
    if (widget == nullptr) return;

    FormDesign *page = qobject_cast<FormDesign *>(widget);
    if (page == nullptr) return;

  });
  connect(act_undo, &QAction::triggered, [this]() {
    auto widget = ui->tabWidget->currentWidget();
    if (widget == nullptr) return;

    FormDesign *page = qobject_cast<FormDesign *>(widget);
    if (page == nullptr) return;

    if (page->getScene()->undostack()->canUndo()) {
      page->getScene()->undostack()->undo();
    }
    this->act_undo->setEnabled(page->getScene()->undostack()->canUndo());
    this->act_redo->setEnabled(page->getScene()->undostack()->canRedo());
  });
  connect(act_redo, &QAction::triggered, [this]() {
    auto widget = ui->tabWidget->currentWidget();
    if (widget == nullptr) return;

    FormDesign *page = qobject_cast<FormDesign *>(widget);
    if (page == nullptr) return;

    if (page->getScene()->undostack()->canRedo()) {
      page->getScene()->undostack()->redo();
    }
    this->act_undo->setEnabled(page->getScene()->undostack()->canUndo());
    this->act_redo->setEnabled(page->getScene()->undostack()->canRedo());
  });

  act_undo->setEnabled(false);
  act_redo->setEnabled(false);
  ui->menuEdit->addAction(act_undo);
  ui->menuEdit->addAction(act_redo);

  createNewTabEditor();
}

MainWindow::~MainWindow() {
  foreach (auto item, daftarform) {
    if (item != nullptr) {
      delete item;
      item = nullptr;
    }
  }
  daftarform.clear();
  delete ui;
}

void MainWindow::privAddSampleText() {
  auto widget = ui->tabWidget->currentWidget();
  if (widget == nullptr) return;

  FormDesign *page = qobject_cast<FormDesign *>(widget);
  if (page == nullptr) return;

  page->getScene()->undostack()->push(new XCommands::InsertItemCommand(
      page->getScene(), ItemConst::Tipe::TEKS));
  act_redo->setEnabled(page->getScene()->undostack()->canRedo());
  act_undo->setEnabled(page->getScene()->undostack()->canUndo());
}

void MainWindow::privAddSampleImage() {
  auto widget = ui->tabWidget->currentWidget();
  if (widget == nullptr) return;

  FormDesign *page = qobject_cast<FormDesign *>(widget);
  if (page == nullptr) return;

  page->getScene()->undostack()->push(new XCommands::InsertItemCommand(
      page->getScene(), ItemConst::Tipe::GAMBAR));
  act_redo->setEnabled(page->getScene()->undostack()->canRedo());
  act_undo->setEnabled(page->getScene()->undostack()->canUndo());
}

void MainWindow::privHapusSemuaItem() {
  auto widget = ui->tabWidget->currentWidget();
  if (widget == nullptr) return;

  FormDesign *page = qobject_cast<FormDesign *>(widget);
  if (page == nullptr) return;

  page->getScene()->ClearAllItems();
}

void MainWindow::privExit() { close(); }

void MainWindow::createNewTabEditor() {
  HelperTabSwitch *tab = new HelperTabSwitch;
  tab->design = new FormDesign(this);
  tab->tabidx = ui->tabWidget->addTab(
      tab->design, tr("Editor Tab %1").arg(ui->tabWidget->count() + 1));
  daftarform << tab;
  m_maybeOldTabwidget = tab->design;
}

void MainWindow::on_actionTutup_Aplikasi_triggered() { this->privExit(); }

void MainWindow::on_actionTambah_teks_triggered() { privAddSampleText(); }

void MainWindow::on_actionTambah_Gambar_triggered() { privAddSampleImage(); }
