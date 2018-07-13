#ifndef FORMDESIGN_H
#define FORMDESIGN_H

#include <manystructuiobjectparam.h>
#include <QWidget>

namespace Ui {
class FormDesign;
}
class SceneView;
class QGraphicsItem;
class BaseAllItems;
class QStandardItemModel;
class QStandardItem;
class PageItem;
class PropertyEditItemDelegate;

class MainWindow;

class FormDesign : public QWidget {
  Q_OBJECT

 public:
  explicit FormDesign(MainWindow *fromMainWind, QWidget *parent = 0);
  ~FormDesign();
  SceneView *getScene();

  MainWindow *mainWindow();

 public Q_SLOTS:
  void resetPropertyItemObj();

  void handleItemPropertyUpdate();

  void handleItemSelection(BaseAllItems *item);

 private:
  // klik getobj to prop
  void buildItemPropertySelectionTeks(BaseAllItems *item);
  void buildItemPropertySelectionGambar(BaseAllItems *item);
  void buildItemPropertySelectionLine(BaseAllItems *item);
  void buildItemPropertySelectionTriangle(BaseAllItems *item);

  // on edit change user interact to direct item
  // from prop edit to  setting of obj
  void updateItemPropertySeletionTeks(const BaseAllItems *item);
  void updateItemPropertySeletionGambar(const BaseAllItems *item);
  void updateItemPropertySeletionLine(const BaseAllItems *item);
  void updateItemPropertySeletionTriangle(const BaseAllItems *item);

  QStandardItem *insertNewPropertyItemFromParent(
      QStandardItem *parent,
      const ManyStructUiObjectParam::SingleRowPropertyParamItemEdit &in);

  QStandardItem *lookUpSecondColumnPropItemFromKeyStringCol1(
      const QString &key);
  Ui::FormDesign *ui;

  SceneView *scnview;
  QList<QGraphicsItem *> contents;
  BaseAllItems *currentitem;
  QStandardItemModel *model_obj_tree;
  QStandardItemModel *model_item_prop;
  PropertyEditItemDelegate *delegate_obj_editor;
  QList<ManyStructUiObjectParam::RecordedSingleRowItem> recorded_item_prop;
  MainWindow *m_mainWindow;
};

#endif  // FORMDESIGN_H
