#include "lineitem.h"
#include <QPainterPath>
#include <QPainter>

LineItem::LineItem(QGraphicsItem *parent) : QGraphicsObject(parent) {
    m_width=1.5;
    warna=QColor("blue");
}

LineItem::~LineItem() { 
}

void LineItem::setStartPoint(const QPointF &p)
{
    if(start==p){
        return;
    }   
    start=p;
    QPointF topleft((qreal)p.x ()-(m_width/2),p.y ());
    m_rect.setTopLeft (topleft);
    update();
}

QPointF LineItem::startPoint() const
{
    return start;
}

void LineItem::setEndPoint(const QPointF &p)
{
    if(end==p){
        return;
    }   
    QPointF bottomright((qreal)p.x ()+(m_width/2),p.y ());
    m_rect.setBottomRight (bottomright);
    end=p;
    update();
}

QPointF LineItem::endPoint() const
{
    return end;
}

void LineItem::setColor(const QColor &c)
{
    if(warna==c){
        return;
    }
    warna=c;
    update();
}

QColor LineItem::color() const
{
    return warna;
}

void LineItem::setWidth(qreal w)
{
    if(m_width==w){
        return;
    }
    m_width=w;
    update();
}

qreal LineItem::width() const
{
    return m_width;
}
   
QRectF LineItem::internalRect() const
{
    return m_rect;
}

QRectF LineItem::boundingRect() const
{
    return m_rect;
}

QPainterPath LineItem::shape() const
{
    QPainterPath path;
    path.addRect (m_rect);
    return path;
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPen pen(warna,width());
    painter->setPen (pen);
    painter->drawLine (QLineF(start,end));
}
