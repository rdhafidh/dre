#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QPair>
#include <manystructuiobjectparam.h>

namespace Ui {
class MainWindow;
}
class SceneView;
class FormDesign;
class QAction;
struct HelperTabSwitch{
    FormDesign *design;
    int tabidx;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public Q_SLOTS:  
    void createNewTabEditor();
    
 private Q_SLOTS:
  void on_actionAdd_teks_triggered();

  void on_actionHapus_Semua_triggered();

  void on_actionAdd_qt_teks_triggered();

  void on_actionAdd_pure_obyek_teks_triggered();
 
  void on_actionAdd_custom_image_item_triggered();
   
private:   
  void RegisterHandlerUndoRedoConnection(FormDesign *from);
  void UnregisterHandlerUndoRedoConnection(FormDesign *from);
  
  Ui::MainWindow *ui; 
  QAction *act_undo;
  QAction *act_redo;
  QList<HelperTabSwitch *> daftarform; 
  FormDesign *m_maybeOldTabwidget;
};

#endif  // MAINWINDOW_H
