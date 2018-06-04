#include "customobyek.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QAbstractTextDocumentLayout>

CustomObyek::CustomObyek(QGraphicsItem *parent) : QGraphicsObject(parent) {
    setFlags (QGraphicsObject::ItemIsMovable);
}

CustomObyek::~CustomObyek() {}

void CustomObyek::setRect(const QRectF &r) {
  if (m_rect == r) return;

  m_rect = r;
  doc.setTextWidth(m_rect.width());
  update();
}

QRectF CustomObyek::rect() const { return m_rect; }

void CustomObyek::setTeks(const QString &t)
{
    doc.setHtml (t);
    update();
}

QString CustomObyek::teks() const
{
    return doc.toHtml ();
}

void CustomObyek::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QAbstractTextDocumentLayout::PaintContext ctx;
  doc.documentLayout()->draw(painter, ctx);
}

void CustomObyek::mousePressEvent(QGraphicsSceneMouseEvent *e) {
  qDebug() << "mousePressEvent CustomObyek  ";
  QGraphicsObject::mousePressEvent (e);
}

QPainterPath CustomObyek::shape() const {
  QPainterPath path;
  path.addRect(m_rect);
  return path;
}

QRectF CustomObyek::boundingRect() const { return m_rect; }
