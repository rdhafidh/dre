#include "selectionmarkerhandlebase.h" 
#include <QPainter> 
#include <QCursor>
#include <baseallitems.h>

SelectionMarkerHandleBase::SelectionMarkerHandleBase(QGraphicsItem *parent)
    : QGraphicsItem(parent) {
    setAcceptHoverEvents (true);  
    moderesize=false;
    setOpacity (0.5);
}

SelectionMarkerHandleBase::~SelectionMarkerHandleBase() {}

void SelectionMarkerHandleBase::setItemHandlePosType(HandlePosType type)
{
    posisi_handle=type;
}

void SelectionMarkerHandleBase::setCursorType(Qt::CursorShape shape)
{
    m_cursorshape=shape;
}

void SelectionMarkerHandleBase::setForParentItemType(const ItemConst::Tipe &tipeItem)
{
    itemType=tipeItem;
}

void SelectionMarkerHandleBase::setSelectionMarkerSize(int n)
{
    markerSize=n;
    update ();
}

void SelectionMarkerHandleBase::setBrushMarker(const QBrush &b)
{
    brush=b;
    update ();
}

bool SelectionMarkerHandleBase::isModeResize() const
{
    return moderesize;
}

void SelectionMarkerHandleBase::setRect(const QRectF &r)
{
    if(m_rect==r ) return;
    prepareGeometryChange ();
    m_rect=r; 
    qreal m_from_marker=markerSize/2;
    m_rect.adjust (-m_from_marker,-m_from_marker,m_from_marker,m_from_marker);
}

QRectF SelectionMarkerHandleBase::rect() const
{
    return m_rect;
}

void SelectionMarkerHandleBase::paint(QPainter *painter,
                                      const QStyleOptionGraphicsItem *option,
                                      QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
 if(parentItem ()){
        painter->setOpacity(opacity ());
        painter->setBrush(brush); 
        painter->drawRect (m_rect);
 }
}

void SelectionMarkerHandleBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (parentItem()) {
        BaseAllItems *cik =qgraphicsitem_cast<BaseAllItems*>(parentItem());
        if(cik){
            cik->mouseMoveEvent (event);
        }
    }
      QGraphicsItem::mouseMoveEvent(event);
}

void SelectionMarkerHandleBase::mousePressEvent(
    QGraphicsSceneMouseEvent *event) {
  if (parentItem()) {
      BaseAllItems *cik =qgraphicsitem_cast<BaseAllItems*>(parentItem());
      if(cik){
          cik->mousePressEvent (event);
      }
  }
  QGraphicsItem::mousePressEvent(event);
}

void SelectionMarkerHandleBase::mouseReleaseEvent(
    QGraphicsSceneMouseEvent *event) {
  if (parentItem()) {
      BaseAllItems *cik =qgraphicsitem_cast<BaseAllItems*>(parentItem());
      if(cik){
          cik->mouseReleaseEvent (event);
      }
  }
  QGraphicsItem::mouseReleaseEvent(event);
}

void SelectionMarkerHandleBase::hoverEnterEvent(
    QGraphicsSceneHoverEvent *event) {
  if (parentItem()) {
      BaseAllItems *cik =qgraphicsitem_cast<BaseAllItems*>(parentItem());
      if(cik){
          setCursor(QCursor(m_cursorshape));
          cik->setFocus (Qt::MouseFocusReason);
          moderesize = true;
          cik->hoverEnterEvent (event);
      }
  }
  QGraphicsItem::hoverEnterEvent(event);
}

void SelectionMarkerHandleBase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (parentItem()) { 
        BaseAllItems *cik =qgraphicsitem_cast<BaseAllItems*>(parentItem());
        if(cik){
            setCursor(QCursor(Qt::ArrowCursor));
            moderesize = false;
            cik->hoverLeaveEvent (event);
        }
    }
    QGraphicsItem::hoverLeaveEvent(event);
}

void SelectionMarkerHandleBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (parentItem()) { 
        BaseAllItems *cik =qgraphicsitem_cast<BaseAllItems*>(parentItem());
        if(cik){
            cik->mouseDoubleClickEvent (event);
        }
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}

QRectF SelectionMarkerHandleBase::boundingRect() const
{
    return m_rect;
}

QPainterPath SelectionMarkerHandleBase::shape() const
{
    QPainterPath path;
    path.addRect (m_rect);
    return path;
}
