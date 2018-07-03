#include "handlerpointerruler.h"
#include <baseallitems.h>
#include <pageitem.h>
#include <sceneview.h>
#include <QGraphicsLineItem>

HandlerPointerRuler::HandlerPointerRuler(const PointerModeRulerOfItem &mode,
                                         BaseAllItems *fromParent) {
  m_single_line = nullptr;
  m_mode = mode;
  switch (m_mode) {
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
    case PointerModeRulerOfItem::POINTER_MODE_LEFT:
    case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
    case PointerModeRulerOfItem::POINTER_MODE_TOP:
      this->buildSingleLine(fromParent);
      break;
  }
}

HandlerPointerRuler::~HandlerPointerRuler() {
  switch (m_mode) {
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
    case PointerModeRulerOfItem::POINTER_MODE_LEFT:
    case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
    case PointerModeRulerOfItem::POINTER_MODE_TOP:
      if (m_single_line) {
        delete m_single_line;
      }
      break;
  }
}

void HandlerPointerRuler::updateCentralPos(const QPointF &pos) {
  if (m_single_line) {
    switch (m_mode) {
      case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
        this->updatePosCentralBawah(pos);
        break;
      case PointerModeRulerOfItem::POINTER_MODE_LEFT:
        this->updatePosCentralKiri(pos);
        break;
      case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
        this->updatePosCentralKanan(pos);
        break;
      case PointerModeRulerOfItem::POINTER_MODE_TOP:
        this->updatePosCentralAtas(pos);
        break;
    }
  }
}

QGraphicsLineItem *HandlerPointerRuler::singleLineItem() {
  return m_single_line;
}

void HandlerPointerRuler::buildSingleLine(BaseAllItems *fromParent) {
  SceneView *scn = qobject_cast<SceneView *>(fromParent->scene());
  if (scn) {
    m_single_line = new QGraphicsLineItem(fromParent);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor("blue"));
    m_single_line->setPen(pen);
    QPointF left(-scn->width (),
                 fromParent->rect().y());
    QPointF right(scn->pageItemDesign()->getRect().right(),
                  fromParent->rect().y());
    m_single_line->setLine(QLineF(left, right));
  }
}

void HandlerPointerRuler::updatePosCentralAtas(const QPointF &p) { 
  if (m_single_line) {
    SceneView *scn = qobject_cast<SceneView *>(m_single_line->scene());
    if (scn) {
      QPointF left(-scn->width (),
                   p.y());
      QPointF right(scn->pageItemDesign()->getRect().right(),
                    p.y());
      m_single_line->setLine(QLineF(left, right));
    }
  }
}

void HandlerPointerRuler::updatePosCentralKiri(const QPointF &p) {}

void HandlerPointerRuler::updatePosCentralBawah(const QPointF &p) {}

void HandlerPointerRuler::updatePosCentralKanan(const QPointF &p) {}
