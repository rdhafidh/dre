#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QGraphicsView>

class Baseview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Baseview(QWidget *parent = 0);
    ~Baseview();
    
    void setZoomFactor(qreal factor);
    
    void setZoom(qreal scalefactor);
    void scaleView(qreal scaleFactor);
    
    
signals:
    void cursorPosition(const QPointF &pos);
    /*
     * trigger ketika scaled view terjadi 
     * update zoom factor horizontal dan vertical ruler
     * 
     * */
    void scaled(qreal n);
public slots: 
    void initZoomLevel();
    
protected:
   void mouseMoveEvent(QMouseEvent *event);
   void wheelEvent(QWheelEvent *event);
private:
};

#endif // BASEVIEW_H