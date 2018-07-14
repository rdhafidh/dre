#ifndef LINEITEM_H
#define LINEITEM_H

#include <baseallitems.h>
#include <QGraphicsRectItem>
#include <QLineF>
#include <QPainterPath> 

class LineItem : public BaseAllItems  {
  Q_OBJECT
  Q_PROPERTY(QLineF line READ getLine WRITE drawLine NOTIFY lineChanged)
  
 public:
  explicit LineItem(QGraphicsItem *parent = nullptr);
  ~LineItem();

  void drawLine(const QLineF &line);
  QLineF getLine() const; 

 Q_SIGNALS:
  void lineChanged(const QLineF &line); 
  
 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const;

  void createContextMenu(QGraphicsSceneContextMenuEvent *event) override;
  
 private Q_SLOTS:
  void updateRightSideLineToMove(const QPointF &to, const QPointF &lastpos);
  void updateLeftSideLineToMove(const QPointF &to, const QPointF &lastpos);

 private:
  void saveCurrentLinePosStack(const QLineF &newLine);

  QLineF m_currentLine;
};

#endif  // LINEITEM_H