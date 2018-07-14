#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <baseallitems.h>

class RectangleItem : public BaseAllItems
{
    Q_OBJECT
public:
    explicit RectangleItem(QGraphicsItem *parent = nullptr);
    ~RectangleItem();
    
protected:
 void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget) override;
 QPainterPath shape() const;

 void createContextMenu(QGraphicsSceneContextMenuEvent *event) override;
    
private:
     
};

#endif // RECTANGLEITEM_H