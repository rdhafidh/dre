#ifndef RULERITEM_H
#define RULERITEM_H

#include <QGraphicsObject>

class RulerItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF cursorPos READ cursorPos WRITE setCursorPos NOTIFY cursorPosChanged)
public:
    explicit RulerItem( Qt::Orientation ori, QGraphicsItem *parent = nullptr);
    ~RulerItem();
    
    Qt::Orientation orientation() const;
    void setRatioUnit(double mm);
    double ratioUnit() const;
    
    void setRect(const QRectF & rect);
    QRectF rect()const;
    
    QPointF cursorPos()const;
    void setCursorPos(const QPointF &m_pos);
    
signals:
    void cursorPosChanged(const QPointF &m_pos);
public slots:
    
protected:
    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
    QRectF boundingRect ()const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    virtual void	contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    Q_DECL_OVERRIDE;
private:
    QPointF m_cursorpos;
    QPolygonF pArrow;
    Qt::Orientation m_orientation;
    int m_ratiounit;
    QRectF m_rect;
};

#endif // RULERITEM_H