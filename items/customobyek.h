#ifndef CUSTOMOBYEK_H
#define CUSTOMOBYEK_H

#include <QGraphicsObject>
#include <QPainterPath>
#include <QTextDocument>

class CustomObyek : public QGraphicsObject {
  Q_OBJECT
 public:
  explicit CustomObyek(QGraphicsItem *parent = 0);
  ~CustomObyek();
    void setRect(const QRectF &r);
    QRectF rect()const ;
    
    void setTeks(const QString &t);
    QString teks()const ;

 signals:

 public slots:

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) Q_DECL_OVERRIDE;
  void mousePressEvent(QGraphicsSceneMouseEvent *e) Q_DECL_OVERRIDE;
  QPainterPath shape() const Q_DECL_OVERRIDE;
  QRectF boundingRect() const Q_DECL_OVERRIDE;

 private:
  QRectF m_rect;
  QTextDocument doc;
};

#endif  // CUSTOMOBYEK_H