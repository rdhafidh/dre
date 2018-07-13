#ifndef LINEITEM_H
#define LINEITEM_H

#include <baseallitems.h>
#include <QGraphicsRectItem>
#include <QLineF>
#include <QPainterPath>

class LineItem : public BaseAllItems {
  Q_OBJECT
  Q_PROPERTY(QLineF line READ getLine WRITE drawLine NOTIFY lineChanged)
  Q_PROPERTY(qreal lineWidth READ getLineWidth WRITE setLineWidth NOTIFY
                 lineWidthChanged)
  Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY
                 lineColorChanged)
 public:
  explicit LineItem(QGraphicsItem *parent = nullptr);
  ~LineItem();

  void drawLine(const QLineF &line);
  QLineF getLine() const;

  void setLineWidth(qreal w);
  qreal getLineWidth() const;

  void setLineColor(const QColor &color);
  QColor getLineColor() const;

 Q_SIGNALS:
  void lineChanged(const QLineF &line);
  void lineWidthChanged(qreal w);
  void lineColorChanged(const QColor &warna);

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const;

  void createContextMenu(QGraphicsSceneContextMenuEvent *event) override;

 public Q_SLOTS:

 private Q_SLOTS:
  void updateRightSideLineToMove(const QPointF &to, const QPointF &lastpos);
  void updateLeftSideLineToMove(const QPointF &to, const QPointF &lastpos);

 private:
  void saveCurrentLinePosStack(const QLineF &newLine);

  QColor m_color;
  qreal m_lineWidth;
  QLineF m_currentLine;
};

#endif  // LINEITEM_H