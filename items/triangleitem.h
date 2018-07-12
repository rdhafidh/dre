#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <baseallitems.h>
#include <QColor>

class TriangleItem : public BaseAllItems {
  Q_OBJECT
  Q_PROPERTY(qreal lineWidth READ getLineWidth WRITE setLineWidth NOTIFY
                 lineWidthChanged)
  Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY
                 lineColorChanged)

 public:
  explicit TriangleItem(QGraphicsItem *parent = nullptr);
  ~TriangleItem();

  void setLineWidth(qreal w);
  qreal getLineWidth() const;

  void setLineColor(const QColor &color);
  QColor getLineColor() const;

 Q_SIGNALS:
  void lineWidthChanged(qreal n);
  void lineColorChanged(const QColor &color);

 public Q_SLOTS:

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) Q_DECL_OVERRIDE;
  QPainterPath shape() const;

  void createContextMenu(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;

 private:
  QColor m_lineColor;
  qreal m_lineWidth;
};

#endif  // TRIANGLEITEM_H