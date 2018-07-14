#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include <baseallitems.h> 

class EllipseItem : public BaseAllItems  
{
    Q_OBJECT  
public:
    explicit EllipseItem(QGraphicsItem *parent = nullptr);
    ~EllipseItem();
     
protected:
 void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget) override;
 QPainterPath shape() const;

 void createContextMenu(QGraphicsSceneContextMenuEvent *event) override;
    
private:
    
};

#endif // ELLIPSEITEM_H