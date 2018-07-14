#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QGraphicsObject>
#include <QPainterPath>

class RulerBase;

class PageItem : public QGraphicsObject {
  Q_OBJECT
  Q_PROPERTY(
      int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
  Q_PROPERTY(bool drawGrid READ drawGrid WRITE setDrawGrid)

 public:
  explicit PageItem(QGraphicsItem *parent = nullptr);
  ~PageItem();
  void setRect(const QRectF &f);
  QRectF getRect() const;

  int gridSize() const;
  void setGridSize(int n);

  void setDrawGrid(bool a);
  bool drawGrid() const;

  void setInsertItemMode(bool e);
  bool isInsertItemMode() const;

 Q_SIGNALS:
  void gridSizeChanged(int g);

  void emitStartInsertFromTopLeftPoin(const QPointF &p);

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

 public slots:
 private:
  int m_gridsize;
  QRectF rect;
  bool m_drawgrid;
  RulerBase *ruler_atas;
  RulerBase *ruler_kiri;
  bool m_isInsertItemMode = false;
};

#endif  // PAGEITEM_H