#include "rectangleitem.h"
#include <QBrush>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPolygonF>

RectangleItem::RectangleItem(QGraphicsItem *parent) : BaseAllItems(parent) {
  setItemType(ItemConst::Tipe::KOTAK);
  setProperty("borderLine", BORDER_KOSONG);
  setProperty("lineColor", QColor("black"));
  setProperty("lineWidth", 1.5f);
  setProperty("fillColorShape", QColor("red"));
}

RectangleItem::~RectangleItem() {}

void RectangleItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
  painter->save();
  auto path = shape();  
  painter->setBrush (this->getFillColorShape ());
  painter->drawPath(path);
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

QPainterPath RectangleItem::shape() const {
  QPen pen;
  pen.setBrush(QBrush(this->getLineColor()));
  pen.setWidthF(this->getLineWidth());
  QPainterPathStroker stroke(pen);
  QPainterPath path; 
  path.addRect(this->rect());
  return stroke.createStroke(path);
}

void RectangleItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  QAction *cpAction = menu.addAction("Copy");
  QAction *pasteAction = menu.addAction("Paste");
  QAction *delAction = menu.addAction("Delete");
  QAction *dumpPropertiAction = menu.addAction("Dump Properti");
  QAction *selectedAction = menu.exec(event->screenPos());
  if (selectedAction == cpAction) {
  } else if (selectedAction == pasteAction) {
  } else if (selectedAction == delAction) {
  } else if (selectedAction == dumpPropertiAction) {
    this->dumpPropertiInfo();
  }
}
