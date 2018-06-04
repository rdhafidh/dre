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
    : QMainWindow(parent), ui(new Ui::MainWindow),m_maybeOldTabwidget(nullptr) {
  ui->setupUi(this);
  act_redo=new QAction(tr("Redo"),this);
  act_undo=new QAction(tr("Undo"),this); 
  act_redo->setShortcut (QKeySequence(tr("Ctrl+Y")));
  act_undo->setShortcut (QKeySequence(tr("Ctrl+Z")));
  connect(ui->tabWidget,&TabWidgetUtama::currentChanged,[this](int idx){
      if(idx<0) return;
      
      auto widget = ui->tabWidget->currentWidget();
      if (widget == nullptr) return;
      
      FormDesign *page = qobject_cast<FormDesign *>(widget);
      if (page == nullptr) return;
      
      if(m_maybeOldTabwidget !=nullptr && m_maybeOldTabwidget !=page){
          this->UnregisterHandlerUndoRedoConnection (m_maybeOldTabwidget);
          this->UnregisterHandlerUndoRedoConnection(page);
          this->RegisterHandlerUndoRedoConnection (page);
      } 
             
  });
  connect(act_undo,&QAction::triggered,[this](){
      auto widget = ui->tabWidget->currentWidget();
      if (widget == nullptr) return;
    
      FormDesign *page = qobject_cast<FormDesign *>(widget);
      if (page == nullptr) return;
      
      if(page->getScene ()->undostack ()->canUndo ()){
          page->getScene ()->undostack ()->undo ();
      }
      this->act_undo->setEnabled (page->getScene ()->undostack ()->canUndo ());
      this->act_redo->setEnabled (page->getScene ()->undostack ()->canRedo ());
  });
  connect(act_redo,&QAction::triggered,[this](){
      auto widget = ui->tabWidget->currentWidget();
      if (widget == nullptr) return;
    
      FormDesign *page = qobject_cast<FormDesign *>(widget);
      if (page == nullptr) return;
      
      if(page->getScene ()->undostack ()->canRedo ()){
          page->getScene ()->undostack ()->redo ();
      }
      this->act_undo->setEnabled (page->getScene ()->undostack ()->canUndo ());
      this->act_redo->setEnabled (page->getScene ()->undostack ()->canRedo ());
  });
  
  act_undo->setEnabled (false);
  act_redo->setEnabled (false);
  ui->menuEdit->addAction(act_undo);
  ui->menuEdit->addAction(act_redo);
  
  createNewTabEditor();
}

MainWindow::~MainWindow() {
  foreach (auto item, daftarform) {
      if(item !=nullptr){
          delete item;
          item = nullptr;
      }
  }
  daftarform.clear();
  delete ui;
}

void MainWindow::on_actionAdd_teks_triggered() {
  auto widget = ui->tabWidget->currentWidget();
  if (widget == nullptr) return;

  FormDesign *page = qobject_cast<FormDesign *>(widget);
  if (page == nullptr) return;

  page->getScene()->undostack()->push(new XCommands::InsertItemCommand(
      page->getScene(), ItemConst::Tipe::TEKS));
  act_redo->setEnabled (page->getScene ()->undostack ()->canRedo ());
  act_undo->setEnabled (page->getScene ()->undostack ()->canUndo ());
}

void MainWindow::on_actionHapus_Semua_triggered() {
  auto widget = ui->tabWidget->currentWidget();
  if (widget == nullptr) return;

  FormDesign *page = qobject_cast<FormDesign *>(widget);
  if (page == nullptr) return;

  page->getScene()->ClearAllItems();
}

void MainWindow::on_actionAdd_qt_teks_triggered() {
  //  QGraphicsTextItem *teks = new QGraphicsTextItem;
  //  teks->setHtml("WOIII");
  //  scnview->addItem(teks);
  //  contents.append(teks);
  //  qDebug() << "add item teks";
}

void MainWindow::on_actionAdd_pure_obyek_teks_triggered() {
  //  CustomObyek *cb = new CustomObyek;
  //  cb->setRect(QRectF(0, 0, 30, 60));
  //  cb->setTeks("teks panjannnnnnnnnnnnnnnnnnnnnnng");
  //  scnview->addItem(cb);
  //  contents.append(cb);
}
void MainWindow::on_actionAdd_custom_image_item_triggered() {
  auto widget = ui->tabWidget->currentWidget();
  if (widget == nullptr) return;

  FormDesign *page = qobject_cast<FormDesign *>(widget);
  if (page == nullptr) return;

  page->getScene()->undostack()->push(new XCommands::InsertItemCommand(
      page->getScene(), ItemConst::Tipe::GAMBAR));
  act_redo->setEnabled (page->getScene ()->undostack ()->canRedo ());
  act_undo->setEnabled (page->getScene ()->undostack ()->canUndo ());
}

void MainWindow::RegisterHandlerUndoRedoConnection(FormDesign *from)
{
    connect(from->getScene ()->undostack (),&QUndoStack::canRedoChanged,
            [this](bool e){
        this->act_redo->setEnabled (e);
    });
    connect(from->getScene ()->undostack (),&QUndoStack::canUndoChanged,
            [this](bool e){
        this->act_undo->setEnabled (e);
    });
    connect(from->getScene ()->undostack (),&QUndoStack::redoTextChanged,
            [this](const QString & e){
        if(e.isEmpty ()){
            this->act_redo->setText (tr("Redo"));
            return;
        }
        this->act_redo->setText ("Redo "+e);
    });
    connect(from->getScene ()->undostack (),&QUndoStack::undoTextChanged,
            [this](const QString & e){
        if(e.isEmpty ()){
            this->act_undo->setText (tr("Undo"));
            return;
        }
        this->act_undo->setText ("Undo "+e);
    });
}

void MainWindow::UnregisterHandlerUndoRedoConnection(FormDesign *from)
{
//    disconnect(from->getScene ()->undostack (),&QUndoStack::canRedoChanged,
//            [this](bool e){
//        this->act_redo->setEnabled (e);
//    });
//    disconnect(from->getScene ()->undostack (),&QUndoStack::canUndoChanged,
//            [this](bool e){
//        this->act_undo->setEnabled (e);
//    });
//    disconnect(from->getScene ()->undostack (),&QUndoStack::redoTextChanged,
//            [this](const QString & e){
//        this->act_redo->setText (e);
//    });
//    disconnect(from->getScene ()->undostack (),&QUndoStack::undoTextChanged,
//            [this](const QString & e){
//        this->act_undo->setText (e);
//    });
	Q_UNUSED(from)
}

void MainWindow::createNewTabEditor() {
  HelperTabSwitch *tab = new HelperTabSwitch;
  tab->design = new FormDesign(this);
  tab->tabidx = ui->tabWidget->addTab(
      tab->design, tr("Editor Tab %1").arg(ui->tabWidget->count() + 1));
  daftarform << tab;
 m_maybeOldTabwidget=tab->design;
 RegisterHandlerUndoRedoConnection (tab->design);
}
