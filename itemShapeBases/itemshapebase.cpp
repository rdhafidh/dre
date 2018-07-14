#include "itemshapebase.h"
#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <QPainterPath>

ItemShapeBase::ItemShapeBase(QObject *parent) : QObject(parent) {
  m_borderflag = BORDER_SEMUA;
  m_borderwidth = 1;
  localrect = QRectF(0, 0, 0, 0);
  m_bordercolor = QColor(Qt::black);
  m_visible = true;
  m_tipeitem = ItemConst::Tipe::KOTAK; 
}

ItemShapeBase::~ItemShapeBase() {}

ItemShapeBase::BorderLineFlags ItemShapeBase::borderLineFlags() const {
  return m_borderflag;
}

void ItemShapeBase::setBorderLineFlags(
    const ItemShapeBase::BorderLineFlags &b) {
  if (m_borderflag == b) return;

  m_borderflag = b;
  this->askUpdate();
}

qreal ItemShapeBase::borderLineWidth() const { return m_borderwidth; }

void ItemShapeBase::setBorderLineWidth(qreal n) {
  if (m_borderwidth == n) return;

  m_borderwidth = n;
  this->askUpdate();
}

QColor ItemShapeBase::borderColor() const { return m_bordercolor; }

void ItemShapeBase::setBorderColor(const QColor &col) {
  if (m_bordercolor == col) return;

  m_bordercolor = col;
  this->askUpdate();
}

bool ItemShapeBase::visibleItem() const { return m_visible; }

void ItemShapeBase::setVisibleItem(bool n) {
  if (m_visible == n) return;

  m_visible = n;
  this->askUpdate();
}

void ItemShapeBase::setRect(const QRectF &r) {
  if (localrect == r) return;

  localrect = r;
  this->rectChanged(localrect);
  this->askUpdate();
}

QRectF ItemShapeBase::rect() const { return localrect; }
 
void ItemShapeBase::setItemType(const ItemConst::Tipe &tipe) {
  if (m_tipeitem == tipe) return;

  m_tipeitem = tipe;
}

ItemConst::Tipe ItemShapeBase::getItemType() const { return m_tipeitem; }

bool ItemShapeBase::isInUndoStack() const { return m_isindostack; }

void ItemShapeBase::setInUndoStack(bool e) { m_isindostack = e; }

void ItemShapeBase::setLineWidth(qreal w)
{
    if(this->m_lineWidth==w){
        return;
    }
    this->m_lineWidth=w;
    this->askUpdate ();
}

qreal ItemShapeBase::getLineWidth() const
{
    return m_lineWidth;
}

void ItemShapeBase::setLineColor(const QColor &color)
{
    if(this->m_lineColor==color){
        return;
    }
    m_lineColor=color;
    this->askUpdate ();
}

QColor ItemShapeBase::getLineColor() const
{
    return m_lineColor;
}

void ItemShapeBase::setFillColorShape(const QColor &color)
{
    if(this->m_fillColor==color){
        return;
    }
    m_fillColor=color;
    this->askUpdate ();
}

QColor ItemShapeBase::getFillColorShape() const
{
    return m_fillColor;
}

void ItemShapeBase::paintShape(QPainter *painter) {
  if (painter != nullptr && m_visible) {
    drawSingleItemBorder(painter);
  }
}

void ItemShapeBase::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
  Q_UNUSED(event)
}

void ItemShapeBase::drawSingleItemBorder(QPainter *painter) {
  if (this->m_borderflag & BORDER_ATAS)
    drawSingleItemTopLine(painter, this->rect());
  if (this->m_borderflag & BORDER_KANAN)
    drawSingleItemRightLine(painter, this->rect());
  if (this->m_borderflag & BORDER_KIRI)
    drawSingleItemLeftLine(painter, this->rect());
  if (this->m_borderflag & BORDER_BAWAH)
    drawSingleItemBotomLine(painter, this->rect());
}

void ItemShapeBase::drawSingleItemTopLine(QPainter *painter, QRectF rect) {
  QPainterPath path;
  path.moveTo(rect.topLeft());
  path.lineTo(rect.topRight());
  painter->setPen(borderPen());
  painter->drawPath(path);
}

void ItemShapeBase::drawSingleItemBotomLine(QPainter *painter, QRectF rect) {
  QPainterPath path;
  path.moveTo(rect.bottomLeft());
  path.lineTo(rect.bottomRight());
  painter->setPen(borderPen());
  painter->drawPath(path);
}

void ItemShapeBase::drawSingleItemRightLine(QPainter *painter, QRectF rect) {
  QPainterPath path;
  path.moveTo(rect.topRight());
  path.lineTo(rect.bottomRight());
  painter->setPen(borderPen());
  painter->drawPath(path);
}

void ItemShapeBase::drawSingleItemLeftLine(QPainter *painter, QRectF rect) {
  QPainterPath path;
  path.moveTo(rect.topLeft());
  path.lineTo(rect.bottomLeft());
  painter->setPen(borderPen());
  painter->drawPath(path);
}

QPen ItemShapeBase::borderPen() const {
  QPen pen;
  pen.setBrush(QBrush(m_bordercolor));
  pen.setWidth(m_borderwidth);
  pen.setStyle(Qt::SolidLine);
  return pen;
} 
