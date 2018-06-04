#ifndef SELECTIONMARKERHANDLEBASE_H
#define SELECTIONMARKERHANDLEBASE_H

#include <QGraphicsObject>
#include <QBrush>
#include <constvalue.h>

enum class HandlePosType{
    UNDEFINED=0x0,
    TOP=1,LEFT,BOTTOM,RIGHT
};

class SelectionMarkerHandleBase : public QGraphicsItem
{
public:
    explicit SelectionMarkerHandleBase(QGraphicsItem *parent=nullptr);
    ~SelectionMarkerHandleBase();
    
    void setItemHandlePosType(HandlePosType type);
    void setCursorType(Qt::CursorShape shape);
    void setForParentItemType(const ItemConst::Tipe &tipeItem);
    void setSelectionMarkerSize(int n);
    void setBrushMarker(const QBrush & b);
    bool isModeResize() const;
    void setRect(const QRectF & r);
    QRectF rect()const; 
    
protected:  
    //sistem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE; 
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE; 
    void  mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
   QPainterPath shape() const Q_DECL_OVERRIDE;
    
private:
    int markerSize;
    bool moderesize;
    QBrush brush;
    QRectF m_rect;
    ItemConst::Tipe itemType;
    Qt::CursorShape m_cursorshape;
    HandlePosType posisi_handle=HandlePosType::UNDEFINED;
};

#endif // SELECTIONMARKERHANDLEBASE_H