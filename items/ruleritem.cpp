#include "ruleritem.h"
#include <QAction>
#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <QFont>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

RulerItem::RulerItem(Qt::Orientation ori, QGraphicsItem *parent)
    : QGraphicsObject(parent) {
  m_orientation = ori;
  m_ratiounit = 5.0;
  // setFlag (QGraphicsItem::ItemIsMovable);
  m_cursorpos = QPointF(0, 0);

  if (ori == Qt::Horizontal) {
    pArrow << QPointF(0.0, 0.0);
    pArrow << QPointF(5.0, 5.0);
    pArrow << QPointF(10.0, 0.0);

    pArrow.translate(0, 6);
  } else {
    pArrow << QPointF(0.0, 0.0);
    pArrow << QPointF(5.0, 5.0);
    pArrow << QPointF(0.0, 10.0);

    pArrow.translate(6, 0);
  }
}

RulerItem::~RulerItem() {}

void RulerItem::setRatioUnit(double mm) {
  if (m_ratiounit == mm) return;

  m_ratiounit = mm;
  update();
}

double RulerItem::ratioUnit() const { return m_ratiounit; }

void RulerItem::setRect(const QRectF &rect) {
  if (m_rect == rect) return;

  m_rect = rect;

  // always truncated rect
  if (m_orientation == Qt::Horizontal) {
    m_rect.setHeight(30);
  } else {
    m_rect.setWidth(30);
  }
  update();
}

QRectF RulerItem::rect() const { return m_rect; }

QPointF RulerItem::cursorPos() const { return m_cursorpos; }

void RulerItem::setCursorPos(const QPointF &m_pos) { m_cursorpos = m_pos; update();}

void RulerItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPen pen;
  QFont tfont;
  tfont.setWeight(7);
  // QFontMetrics fm(tfont);
  pen.setColor(QColor(Qt::black));
  pen.setCosmetic(true);
  p->setFont(tfont);
  p->setPen(pen);
  p->setBrush(QColor(Qt::white));
  QRect r(rect().toRect());
  p->drawRect(r);
  // 10 mm marks
  double i10 = 0;
  // 5 mm marks
  double i5 = 5;

  int cnt = 1;
  int h = m_rect.height(), w = m_rect.width();
  if (m_orientation == Qt::Horizontal) {
    double coeff = (double)w / m_ratiounit;

    while (i5 < m_ratiounit) {
      // 10 mm
      int x = int(i10 * w / m_ratiounit);
      p->drawLine(x, h, x, h - 10);

      if (coeff >= 1.5 || (coeff >= 0.7 && !(cnt % 2)) ||
          (coeff >= 0.3 && !(cnt % 4)))
        p->drawText(x - 12, 0, 32, m_rect.height() / 2, Qt::AlignHCenter,
                    QString::number(i10 / 10));

      // 5 mm
      if (coeff >= 1) {
        x = int(i5 * w / m_ratiounit);
        p->drawLine(x, h, x, h - 8);
      }

      // 1 mm
      if (coeff >= 2) {
        for (int i = 1; i < 10; ++i) {
          x = int((double)(i10 + i) * w / m_ratiounit);
          p->drawLine(x, h, x, h - 3);
        }
      }

      i10 += 10;
      i5 += 10;
      cnt++;
    }
    
    // DRAW cursor 
    p->save ();
    p->translate (m_cursorpos.x (),6);
    p->drawConvexPolygon (pArrow);
    p->restore ();
  } else {
    double coeff = (double)h / m_ratiounit;

    while (i5 < m_ratiounit) {
      // 10 mm
      int x = int(i10 * h / m_ratiounit);
      p->drawLine(w, x, w - 10, x);

      if (coeff >= 1.5 || (coeff >= 0.7 && !(cnt % 2)) ||
          (coeff >= 0.3 && !(cnt % 4))) {
        p->rotate(-90);
        p->drawText(int(-(i10 * h / m_ratiounit + 18)), 0, 32, w,
                    Qt::AlignHCenter, QString::number(i10 / 10));
        p->rotate(90);
      }

      // 5 mm
      if (coeff >= 1) {
        x = int(i5 * h / m_ratiounit);
        p->drawLine(w, x, w - 8, x);
      }

      // 1 mm
      if (coeff >= 2) {
        for (int i = 1; i < 10; ++i) {
          x = int((double)(i10 + i) * h / m_ratiounit);
          p->drawLine(w, x, w - 3, x);
        }
      }

      i10 += 10;
      i5 += 10;
      cnt++;
    }
    // DRAW cursor 
    p->save ();
    p->translate (6,m_cursorpos.y ());
    p->drawConvexPolygon (pArrow);
    p->restore ();
  }
  
}

QRectF RulerItem::boundingRect() const { return rect(); }

QPainterPath RulerItem::shape() const {
  QPainterPath path;
  path.addRect(rect());
  return path;
}

void RulerItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  auto act_dumpinfopos = menu.addAction(tr("dump info pos"));
  QAction *selectedAction = menu.exec(event->screenPos());
  if (selectedAction == act_dumpinfopos) {
      #ifdef DEBUGGING_ENABLED
    qDebug() << "geom info "
             << "pos:" << pos() << "rect:" << m_rect;
#endif
  }
}
