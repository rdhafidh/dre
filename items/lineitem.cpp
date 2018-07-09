#include "lineitem.h"
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

LineItem::LineItem(QGraphicsItem *parent) : BaseAllItems(parent) {
  setItemType(ItemConst::Tipe::GARIS);
  m_color = QColor("black");
  m_lineWidth = 3.0;
}

LineItem::~LineItem() {}

void LineItem::drawLine(const QLineF &line) {
  if (m_currentLine == line) {
    return;
  }
  m_currentLine = line;
  update();
}

QLineF LineItem::getLine() const { return m_currentLine; }

void LineItem::setLineWidth(qreal w) {
  if (m_lineWidth == w) {
    return;
  }
  m_lineWidth = w;
  this->lineWidthChanged(m_lineWidth);
  update();
}

qreal LineItem::getLineWidth() const { return m_lineWidth; }

void LineItem::setLineColor(const QColor &color) {
  if (m_color == color) {
    return;
  }
  m_color = color;
  this->lineColorChanged(m_color);
  update();
}

QColor LineItem::getLineColor() const { return m_color; }

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  painter->save();
  auto path = shape();
  setRect(path.controlPointRect());
  painter->setBrush(QBrush(m_color));
  painter->drawPath(path);
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

QPainterPath LineItem::shape() const {
  QPen pen;
  pen.setColor(m_color);
  pen.setWidthF(m_lineWidth);
  QPainterPathStroker stroke(pen);
  QPainterPath path;
  path.moveTo(m_currentLine.p1());
  path.lineTo(m_currentLine.p2());
  return stroke.createStroke(path);
}

void LineItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
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
