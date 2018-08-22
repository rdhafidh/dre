#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <baseallitems.h>
#include <QColor> 

class TriangleItem : public BaseAllItems  {
  Q_OBJECT  
 public:
  explicit TriangleItem(QGraphicsItem *parent = nullptr);
  ~TriangleItem(); 

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const;

  void createContextMenu(QGraphicsSceneContextMenuEvent *event) override;

 private: 
};

#endif  // TRIANGLEITEM_H