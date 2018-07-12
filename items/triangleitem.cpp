#include "triangleitem.h"
#include <QBrush>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPolygonF>

TriangleItem::TriangleItem(QGraphicsItem *parent)
    : BaseAllItems(parent), m_lineColor(QColor("black")), m_lineWidth(1.5) {
  setItemType(ItemConst::Tipe::SEGITIGA);
  setProperty("borderLine", BORDER_KOSONG);
}

TriangleItem::~TriangleItem() {}

void TriangleItem::setLineWidth(qreal w) {
  if (m_lineWidth == w) {
    return;
  }
  m_lineWidth = w;
  update();
}

qreal TriangleItem::getLineWidth() const { return m_lineWidth; }

void TriangleItem::setLineColor(const QColor &color) {
  if (m_lineColor == color) {
    return;
  }
  m_lineColor = color;
  update();
}

QColor TriangleItem::getLineColor() const { return m_lineColor; }

void TriangleItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->save();
  auto path = shape();
  painter->drawPath(path);
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

QPainterPath TriangleItem::shape() const {
  QPen pen;
  pen.setBrush(QBrush(m_lineColor));
  pen.setWidthF(m_lineWidth);
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
