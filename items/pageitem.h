#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QGraphicsObject>
#include <QPainterPath>

class RulerBase;

class PageItem : public QGraphicsObject {
  Q_OBJECT
    Q_PROPERTY(int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged) 
    Q_PROPERTY(bool drawGrid READ drawGrid  WRITE setDrawGrid  )
 public:
  explicit PageItem(QGraphicsItem *parent = nullptr);
  ~PageItem();
    void setRect(const QRectF &f);
    QRectF getRect()const;
    
    int gridSize()const;
    void setGridSize(int n);
    
    void setDrawGrid(bool a);
    bool drawGrid()const;
    
protected:
    void	paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
    QRectF boundingRect ()const Q_DECL_OVERRIDE;
    QPainterPath shape ()const Q_DECL_OVERRIDE;
 Q_SIGNALS:
    void gridSizeChanged(int g);

 public slots:
 private:
    int m_gridsize;
    QRectF rect;
    bool m_drawgrid;
      RulerBase *ruler_atas;
      RulerBase *ruler_kiri;
};

#endif  // PAGEITEM_H