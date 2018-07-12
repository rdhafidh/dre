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
             QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
  QRectF boundingRect() const Q_DECL_OVERRIDE;
  QPainterPath shape() const Q_DECL_OVERRIDE;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
  void hoverEnterEvent (QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
  void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;


 public slots:
 private:
  
  int m_gridsize;
  QRectF rect;
  bool m_drawgrid;
  RulerBase *ruler_atas;
  RulerBase *ruler_kiri;
  bool m_isInsertItemMode=false;
};

#endif  // PAGEITEM_H