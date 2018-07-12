#include "sceneview.h"
#include <baseallitems.h>
#include <baseview.h>
#include <formdesign.h>
#include <items/imageitem.h>
#include <items/lineitem.h>
#include <items/textitem.h>
#include <items/triangleitem.h>
#include <pageitem.h>
#include <ruleritem.h>
#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <mainwindow.h>
#include <undocommand.h>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QAction>

SceneView::SceneView(QObject *parent)
    : QGraphicsScene(parent),
      pageitemdsgn(nullptr),
      m_pagedesign(nullptr),
      m_mainwin(nullptr),
      ruler_atas(nullptr),
      ruler_kiri(nullptr) {
  connect(this, SIGNAL(selectionChanged()), SLOT(onItemSelected()));
  m_undostack.clear();
  if_page_is_not_build = true;

}

void SceneView::setMainPageDesign(FormDesign *from) {
  if (from == nullptr) return;
  m_pagedesign = from;
  connect(m_pagedesign->getScene()->pageItemDesign(),
          &PageItem::emitStartInsertFromTopLeftPoin, this,
          &SceneView::doInsertItemFromTopLeft);
}

FormDesign *SceneView::mainPageDesign() { return m_pagedesign; }

void SceneView::setMainWindow(MainWindow *mainWin) { m_mainwin = mainWin; }

MainWindow *SceneView::mainWindow() { return m_mainwin; }

SceneView::~SceneView() {
  ClearAllItems();
  clear();
}

void SceneView::setPageItemDesign(PageItem *page) { pageitemdsgn = page; }

PageItem *SceneView::pageItemDesign() { return pageitemdsgn; }

BaseAllItems *SceneView::createTextitem(const QPointF &topleft,
                                        const QSizeF &size) {
  TextItem *text = new TextItem;
  text->setParent(pageitemdsgn);
  text->setParentItem(pageitemdsgn);
  text->setRect(QRectF(topleft, size));
  connect(text, &TextItem::emitRefreshItemProperty, m_pagedesign,
          &FormDesign::handleItemPropertyUpdate);
  connect(text, &TextItem::forceThisItemSelected, this,
          &SceneView::updateForceThatItemSelected);
  m_items << text;
  return (BaseAllItems *)text;
}

BaseAllItems *SceneView::createImageitem(const QPointF &topleft,
                                         const QSizeF &size) {
  ImageItem *img = new ImageItem;
  img->setParent(pageitemdsgn);
  img->setParentItem(pageitemdsgn);
  img->setRect(QRectF(topleft, size));
  connect(img, &ImageItem::emitRefreshItemProperty, m_pagedesign,
          &FormDesign::handleItemPropertyUpdate);
  connect(img, &ImageItem::forceThisItemSelected, this,
          &SceneView::updateForceThatItemSelected);
  m_items << img;
  return (BaseAllItems *)img;
}

BaseAllItems *SceneView::createLineItem(const QPointF &topleft,
                                        const QSizeF &size) {
  LineItem *ln = new LineItem;
  ln->setParent(pageitemdsgn);
  ln->setParentItem(pageitemdsgn);
  ln->drawLine(QLineF(topleft, QPointF(size.width(), size.height())));
  connect(ln, &LineItem::emitRefreshItemProperty, m_pagedesign,
          &FormDesign::handleItemPropertyUpdate);
  connect(ln, &LineItem::forceThisItemSelected, this,
          &SceneView::updateForceThatItemSelected);
  m_items << ln;
  return (BaseAllItems *)ln;
}

BaseAllItems *SceneView::createTriangleItem(const QPointF &topleft,
                                            const QSizeF &size) {
  TriangleItem *m_tr = new TriangleItem;
  m_tr->setParent(pageitemdsgn);
  m_tr->setParentItem(pageitemdsgn);
  m_tr->setRect(QRectF(topleft, size));
  connect(m_tr, &LineItem::emitRefreshItemProperty, m_pagedesign,
          &FormDesign::handleItemPropertyUpdate);
  connect(m_tr, &LineItem::forceThisItemSelected, this,
          &SceneView::updateForceThatItemSelected);
  m_items << m_tr;
  return (BaseAllItems *)m_tr;
}

BaseAllItems *SceneView::createShapeRectangleitem(const QPointF &topleft,
                                                  const QSizeF &size) {
  Q_UNUSED(topleft)
  Q_UNUSED(size)
  return nullptr;
}

QUndoStack *SceneView::undostack() { return &m_undostack; }

RulerItem *SceneView::rulerAtas() { return ruler_atas; }

RulerItem *SceneView::rulerKiri() { return ruler_kiri; }

void SceneView::setupMouseRulerPointers() {
  if (views().size() < 1 || !ruler_kiri || !ruler_atas) return;

  connect(qobject_cast<Baseview *>(views()[0]), &Baseview::cursorPosition,
          [this](const QPointF &point) {
            ruler_atas->setProperty("cursorPos", point);
            ruler_kiri->setProperty("cursorPos", point);
          });
}

void SceneView::ClearAllItems() {
  for (auto item : m_items) {
    if (item) {
      removeItem(item);
      item->disconnect();
      delete item;
      item = nullptr;
    }
  }
  m_items.clear();
  m_undostack.clear();
}

void SceneView::onItemSelected() {
  auto items = selectedItems();
  if (items.size() == 1) {
    auto baseitem = (BaseAllItems *)items.at(0);
    if (!baseitem) {
      return;
    }
    this->itemSelected(baseitem);
  }
}

void SceneView::removeKindsItem(BaseAllItems *item) {
  if (item == nullptr) return;

  item->setItemIsRemoved(true);
  item->setSelected(false);
  removeItem(item);
  this->itemRemovedFromScene(item);
  // do not really delete the item, because
  // it might be still saved in qundostack
}

void SceneView::addKindsItem(BaseAllItems *item) {
  if (item == nullptr) return;
  item->setParent(pageitemdsgn);
  item->setParentItem(pageitemdsgn);
  item->setItemIsRemoved(false);
  item->setSelected(true);
  this->itemAddedAgainToScene(item);
}

void SceneView::buildNewItemPage() {
  if (!if_page_is_not_build) return;

  PageItem *page = new PageItem;
  page->setRect(QRectF(0, 0, 850, 1200));
  page->setPos(0, 0);
  if_page_is_not_build = false;
  addItem(page);
  setPageItemDesign(page);
}

void SceneView::buildNewRuler(Qt::Orientation ori, const QSizeF &size) {
  if (!pageItemDesign()) {
    return;
  }
  RulerItem *ruler = nullptr;
  switch (ori) {
    case Qt::Horizontal:
      ruler = new RulerItem(Qt::Horizontal);
      ruler_atas = ruler;
      ruler->setRect(QRectF(QPointF(0, 0), size));
      //        ruler->setPos (0.101056,-30.2836);
      ruler->setPos(0, -ruler_atas->rect().height());
      break;
    default:
      ruler = new RulerItem(Qt::Vertical);
      ruler_kiri = ruler;
      ruler->setRect(QRectF(QPointF(0, 0), size));
      //        ruler->setPos(-30.3245,0.502513);
      ruler->setPos(-ruler_kiri->rect().width(), 0);
      break;
  }
  addItem(ruler);
}

void SceneView::adjustSceneRulerPageRect() {
  if (!ruler_atas || !ruler_kiri) return;

  QRectF r(
      QPointF(rulerKiri()->rect().x() - 7,
              rulerKiri()->rect().y() - rulerAtas()->rect().height() - 14),
      QSizeF(
          ruler_kiri->rect().width() + pageitemdsgn->getRect().width() + 7,
          ruler_atas->rect().height() + pageitemdsgn->getRect().height() + 7));
  setSceneRect(r);
}

void SceneView::updateForceThatItemSelected(BaseAllItems *item) {
  for (auto x : pageItemDesign()->childItems()) {
    if (x == item) {
      x->setSelected(true);
    } else {
      x->setSelected(false);
    }
  }
}

void SceneView::doInsertItemFromTopLeft(const QPointF &p) {
  if (m_mainwin && pageitemdsgn &&
      m_mainwin->currentInsertItemType() != ItemConst::Tipe::UNDEFINED &&
      pageitemdsgn->isInsertItemMode()) {
    undostack()->push(new XCommands::InsertItemCommand(
        this, p, m_mainwin->currentInsertItemType()));
    m_mainwin->actRedoObject()->setEnabled(undostack()->canRedo());
    m_mainwin->actUndoObject()->setEnabled(undostack()->canUndo());
   pageitemdsgn->setInsertItemMode(false); 
  }
}

void SceneView::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}
