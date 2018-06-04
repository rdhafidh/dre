#include "pageitem.h" 
#include <QGraphicsDropShadowEffect>
#include <QGraphicsProxyWidget>
#include <QPainter>

PageItem::PageItem(QGraphicsItem *parent) : QGraphicsObject(parent) {
  setAcceptHoverEvents(true);
  grabGesture(Qt::PinchGesture);
  grabGesture(Qt::SwipeGesture);
  QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
  setGraphicsEffect(shadow);
  setFlag(QGraphicsItem::ItemClipsChildrenToShape);
  m_drawgrid = true;
  m_gridsize = 5; 
}

PageItem::~PageItem() {}

void PageItem::setRect(const QRectF &f) {
  if(rect==f) return;
  
  rect = f;
  update();
}

QRectF PageItem::getRect() const { return rect; }

int PageItem::gridSize() const { return m_gridsize; }

void PageItem::setGridSize(int n) {
  if (m_gridsize == n) return;

  m_gridsize = n;
  this->gridSizeChanged(n);
  update();
}

void PageItem::setDrawGrid(bool a) {
  if (m_drawgrid == a) return;

  m_drawgrid = a;
  update();
}

bool PageItem::drawGrid() const { return m_drawgrid; }

void PageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->fillRect(rect, Qt::white);
  painter->drawRect(rect);

  if (!m_drawgrid) return;

  qreal left = int(rect.left()) - (int(rect.left()) % m_gridsize);
  qreal top = int(rect.top()) - (int(rect.top()) % m_gridsize);
  QVector<QPointF> m_points;

  for (qreal x = left; x < rect.right(); x += m_gridsize) {
    for (qreal y = top; y < rect.bottom(); y += m_gridsize) {
      m_points << QPointF(x, y);
    }
  }
  QPen pen;
  pen.setColor(QColor(Qt::gray));
  pen.setCosmetic(true);
  painter->save();
  painter->setPen(pen);
  painter->drawPoints(m_points.data(), m_points.size());
  painter->restore();
}

QRectF PageItem::boundingRect() const { return rect; }

QPainterPath PageItem::shape() const {
  QPainterPath path;
  path.addRect(rect);
  return path;
}
