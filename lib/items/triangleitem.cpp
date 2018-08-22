#include "triangleitem.h"
#include <QBrush>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPolygonF>

TriangleItem::TriangleItem(QGraphicsItem *parent)
    : BaseAllItems(parent)  {
  setItemType(ItemConst::Tipe::SEGITIGA);
  setProperty("borderLine", BORDER_KOSONG); 
  setProperty ("lineColor",QColor("black"));
  setProperty ("lineWidth",1.5f);
  setProperty ("fillColorShape",QColor("white"));
}

TriangleItem::~TriangleItem() {}
 
void TriangleItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->save();
  auto path = shape();
  painter->setBrush (QBrush(this->getFillColorShape ()));
  painter->drawPath(path);
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

QPainterPath TriangleItem::shape() const {
  QPen pen;
  pen.setBrush(QBrush(this->getLineColor ()));
  pen.setWidthF(this->getLineWidth ());
  QPainterPathStroker stroke(pen);
  QPainterPath path;
  QPolygonF lines;
  lines << this->rect().bottomLeft() << this->rect().bottomRight()
        << this->rect().bottomLeft()
        << QPointF(this->rect().topRight().x() - (this->rect().width() / 2),
                   this->rect().top())
        << this->rect().bottomRight();
  path.addPolygon(lines);
  return stroke.createStroke(path);
}

void TriangleItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
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
