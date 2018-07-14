#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QGraphicsScene>
#include <QUndoStack>

class BaseAllItems;
class PageItem;
class FormDesign;
class RulerItem;

class MainWindow;

class SceneView : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit SceneView(QObject *parent = 0);
  void setMainPageDesign(FormDesign *from);
  FormDesign *mainPageDesign();

  void setMainWindow(MainWindow *mainWin);
  MainWindow *mainWindow();

  ~SceneView();

  PageItem *pageItemDesign();

  BaseAllItems *createTextitem(const QPointF &topleft, const QSizeF &size);
  BaseAllItems *createImageitem(const QPointF &topleft, const QSizeF &size);
  BaseAllItems *createLineItem(const QPointF &topleft, const QSizeF &size);
  BaseAllItems *createTriangleItem(const QPointF &topleft, const QSizeF &size);
  BaseAllItems *createShapeRectangleitem(const QPointF &topleft,
                                         const QSizeF &size);
  BaseAllItems *createEllipseItem(const QPointF &topleft,const QSizeF &size);

  QUndoStack *undostack();
  RulerItem *rulerAtas();
  RulerItem *rulerKiri();

  void setupMouseRulerPointers();

 Q_SIGNALS:
  void itemSelected(BaseAllItems *item);
  /*
   * biasanya ketika redo delete item, trigger ini
   * */
  void itemRemovedFromScene(BaseAllItems *items);
  /*
   * biasanya ketika undo delete item, trigger ini
   * */
  void itemAddedAgainToScene(BaseAllItems *items);

 public Q_SLOTS:
  void ClearAllItems();

  void onItemSelected();
  void removeKindsItem(BaseAllItems *item);
  void addKindsItem(BaseAllItems *item);

  void buildNewItemPage();
  void buildNewRuler(Qt::Orientation ori, const QSizeF &size);
  void adjustSceneRulerPageRect();

 private Q_SLOTS:
  void updateForceThatItemSelected(BaseAllItems *item);
  void doInsertItemFromTopLeft(const QPointF &p);

 protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

 private:
  bool if_page_is_not_build;
  void setPageItemDesign(PageItem *page);
  QList<BaseAllItems *> m_items;
  PageItem *pageitemdsgn;
  RulerItem *ruler_atas;
  RulerItem *ruler_kiri;
  QUndoStack m_undostack;
  FormDesign *m_pagedesign;
  MainWindow *m_mainwin;
};

#endif  // SCENEVIEW_H