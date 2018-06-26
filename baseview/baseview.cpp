#include "baseview.h"
#include <QMouseEvent>
#include <QDebug>

Baseview::Baseview(QWidget *parent) : QGraphicsView(parent) { }

Baseview::~Baseview() {}

void Baseview::setZoomFactor(qreal factor) {
  setZoom(factor); 
  // todo adjust vertical horizontal ruler zoom factor
}

void Baseview::setZoom(qreal scalefactor) { scale(scalefactor, scalefactor); }

void Baseview::scaleView(qreal scaleFactor) {
  qreal factor = matrix()
                     .scale(scaleFactor, scaleFactor)
                     .mapRect(QRectF(0, 0, 1, 1))
                     .width(); 
  if (factor < 0.30 || factor > 1.3 ) return;
  
  qDebug()<<"current factor"<<factor;
  scale(scaleFactor, scaleFactor);

  emit scaled(scaleFactor);
}

void Baseview::initZoomLevel()
{
    
}
 

void Baseview::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  QPointF point = mapToScene(event->pos());
  this->cursorPosition(point); 
}

void Baseview::wheelEvent(QWheelEvent *event) {
  scaleView(pow((double)2, event->delta() / 520.0));
}
