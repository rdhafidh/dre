#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsObject>

class LineItem : public QGraphicsObject
{
    Q_OBJECT
public:
    LineItem(QGraphicsItem *parent);
    ~LineItem();
    
    void setStartPoint(const QPointF &p);
    QPointF startPoint()const;
    
    void setEndPoint(const QPointF & p);
    QPointF endPoint()const;
    
    void setColor(const QColor &c);
    QColor color()const;
    
    void setWidth(qreal w);
    qreal width()const;  
     
    QRectF internalRect()const;
    
protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
     
private:
    QPointF start;
    QPointF end;
    QColor warna;
    QRectF m_rect;
    qreal m_width=0;
};

#endif // LINEITEM_H