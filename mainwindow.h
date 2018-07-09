#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <manystructuiobjectparam.h>
#include <QList>
#include <QMainWindow>
#include <QPair>
#include <constvalue.h>

namespace Ui {
class MainWindow;
}
class SceneView;
class FormDesign;
class QAction;
struct HelperTabSwitch {
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

  void on_actionTutup_Aplikasi_triggered();

  void on_actionTambah_teks_triggered();

  void on_actionTambah_Gambar_triggered();

  void on_actionTambahLine_triggered();
  
  void on_actionTambahSegitiga_triggered();
  
  void on_actionTambahBulat_triggered();
  
  void on_actionTambahKotak_triggered();
  
private:
  void privAddSampleText();
  void privAddSampleImage();
  void privHapusSemuaItem();
  void privAddShapeLine();
  void privAddShapeTriangle();
  void privAddShapeEllipse();
  void privAddShapeRectangle();
  
  void createItemBase(const ItemConst::Tipe &ty);
  void privExit();

  Ui::MainWindow *ui;
  QAction *act_undo;
  QAction *act_redo;
  QList<HelperTabSwitch *> daftarform;
  FormDesign *m_maybeOldTabwidget;
};

#endif  // MAINWINDOW_H
