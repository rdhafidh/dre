#ifndef CUSTOMITEMKOTAK_H
#define CUSTOMITEMKOTAK_H

#include <QGraphicsItem>
#include <QPen>  
#include "constvalue.h"
#include <QTextDocument>

class SelectionMarkerHandleBase;
class CustomItemKotak:public QGraphicsItem
{
public:
    friend class SelectionMarkerHandleBase; 
    CustomItemKotak(QGraphicsItem *parent=0);
    ~CustomItemKotak();
    void setRect(const QRectF &r);
    void setPen(const QPen &p);
    void setHeight(qreal p);
    void setWidth(qreal w); 
    void setItemType(const ItemConst::Tipe &tipe);
    ItemConst::Tipe getItemType()const;
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QVariant  itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
     void	contextMenuEvent(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;
     void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
     int type() const;
private:
    void setModeOnOffSelection(bool b);
    void handleCustomCmdResize();
    void updateHandlePos();
    
    bool modeselect;
    //atas
    SelectionMarkerHandleBase *smpat;
    //samping kiri
    SelectionMarkerHandleBase* smpsk; 
    SelectionMarkerHandleBase *smpsb;
    SelectionMarkerHandleBase *smpsknn;
    SelectionMarkerHandleBase *smh_a_k;
    SelectionMarkerHandleBase *smh_a_knn;
    SelectionMarkerHandleBase *smh_b_knn;
    SelectionMarkerHandleBase *smh_b_kr;
    QRectF m_rect;
    QPen mypen; 
    int markerSize=3;
    QPointF currentpoint;
    ItemConst::Tipe typeitem;
    QTextDocument doc_txt;
};

#endif // CUSTOMITEMKOTAK_H