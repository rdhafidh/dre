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
    case PointerModeRulerOfItem::POINTER_MODE_TOP:
      this->buildSingleLineHor(fromParent);
      break;
    case PointerModeRulerOfItem::POINTER_MODE_LEFT:
    case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
      this->buildSingleLineVert(fromParent);
      break;
    case PointerModeRulerOfItem::POINTER_MODE_TOPLEFT:
      this->buildMultiLineTopLeft(fromParent);
      break;
    case PointerModeRulerOfItem::POINTER_MODE_TOPRIGHT:
      this->buildMultiLineTopRight(fromParent);
      break;
  }
}

HandlerPointerRuler::~HandlerPointerRuler() {
  switch (m_mode) {
    case PointerModeRulerOfItem::POINTER_MODE_TOPLEFT:
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOMLEFT:
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOMRIGHT:
    case PointerModeRulerOfItem::POINTER_MODE_TOPRIGHT:
      askToDestroyMultiLineItem();
      break;
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
    case PointerModeRulerOfItem::POINTER_MODE_LEFT:
    case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
    case PointerModeRulerOfItem::POINTER_MODE_TOP:
      askToDestroySingleLineItem();
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

void HandlerPointerRuler::updateMultiLineCentralPos(
    const std::pair<QPointF, QPointF> &pf) {
  switch (m_mode) {
    case PointerModeRulerOfItem::POINTER_MODE_TOPLEFT:
      this->updatePosLeftAndTop(pf);
      break;
    case PointerModeRulerOfItem::POINTER_MODE_TOPRIGHT:
      this->updatePosRightAndTop(pf);
      break;
  }
}

QGraphicsLineItem *HandlerPointerRuler::singleLineItem() {
  return m_single_line;
}

bool HandlerPointerRuler::isMultiLineItem() const {
  auto l_s = this->m_multiLineMap.find("line1");
  auto t_s = this->m_multiLineMap.find("line2");
  if (l_s != m_multiLineMap.end() && t_s != m_multiLineMap.end() &&
      l_s->second != nullptr && t_s->second != nullptr) {
    return true;
  }
  return false;
}

void HandlerPointerRuler::askToDestroyMultiLineItem() {
  auto l_s = this->m_multiLineMap.find("line1");
  auto t_s = this->m_multiLineMap.find("line2");
  if (l_s != m_multiLineMap.end() && t_s != m_multiLineMap.end() &&
      l_s->second != nullptr && t_s->second != nullptr) {
    SceneView *scn = qobject_cast<SceneView *>(l_s->second->scene());
    if (scn) {
      scn->removeItem(l_s->second);
      scn->removeItem(t_s->second);
      delete l_s->second;
      delete t_s->second;
    }
  }
  m_multiLineMap.clear();
}

void HandlerPointerRuler::askToDestroySingleLineItem() {
  if (m_single_line != nullptr) {
    SceneView *scn = qobject_cast<SceneView *>(m_single_line->scene());
    if (scn) {
      scn->removeItem(m_single_line);
      delete m_single_line;
    }
  }
}

void HandlerPointerRuler::buildSingleLineHor(BaseAllItems *fromParent) {
  SceneView *scn = qobject_cast<SceneView *>(fromParent->scene());
  if (scn) {
    m_single_line = new QGraphicsLineItem(fromParent);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor("blue"));
    m_single_line->setPen(pen);
    QPointF left;
    QPointF right;
    switch (m_mode) {
      case PointerModeRulerOfItem::POINTER_MODE_TOP:
        left.setX(-scn->width());
        left.setY(fromParent->rect().y());
        right.setX(scn->pageItemDesign()->getRect().right());
        right.setY(fromParent->rect().y());
        m_single_line->setLine(QLineF(left, right));
        break;
      case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
        left.setX(-scn->width());
        left.setY(fromParent->rect().bottom());
        right.setX(scn->pageItemDesign()->getRect().right());
        right.setY(fromParent->rect().bottom());
        m_single_line->setLine(QLineF(left, right));
        break;
      default:
        break;
    }
  }
}

void HandlerPointerRuler::buildSingleLineVert(BaseAllItems *fromParent) {
  SceneView *scn = qobject_cast<SceneView *>(fromParent->scene());
  if (scn) {
    m_single_line = new QGraphicsLineItem(fromParent);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor("blue"));
    m_single_line->setPen(pen);
    QPointF top;
    QPointF down;
    switch (m_mode) {
      case PointerModeRulerOfItem::POINTER_MODE_LEFT:
        top.setX(fromParent->rect().left());
        top.setY(-scn->height());
        down.setX(fromParent->rect().left());
        down.setY(scn->pageItemDesign()->getRect().bottom());
        m_single_line->setLine(QLineF(top, down));
        break;
      case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
        top.setX(fromParent->rect().right());
        top.setY(-scn->height());
        down.setX(fromParent->rect().right());
        down.setY(scn->pageItemDesign()->getRect().bottom());
        m_single_line->setLine(QLineF(top, down));
        break;
      default:
        break;
    }
  }
}

void HandlerPointerRuler::buildMultiLineTopLeft(BaseAllItems *fromParent) {
  SceneView *scn = qobject_cast<SceneView *>(fromParent->scene());
  if (scn) {
    auto line_left = new QGraphicsLineItem(fromParent);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor("blue"));
    line_left->setPen(pen);
    QPointF top;
    QPointF down;
    top.setX(fromParent->rect().left());
    top.setY(-scn->height());
    down.setX(fromParent->rect().left());
    down.setY(scn->pageItemDesign()->getRect().bottom());
    line_left->setLine(QLineF(top, down));

    auto line_top = new QGraphicsLineItem(fromParent);
    line_top->setPen(pen);
    QPointF left;
    QPointF right;
    left.setX(-scn->width());
    left.setY(fromParent->rect().y());
    right.setX(scn->pageItemDesign()->getRect().right());
    right.setY(fromParent->rect().y());
    line_top->setLine(QLineF(left, right));
    m_multiLineMap.insert(std::make_pair("line1", line_left));
    m_multiLineMap.insert(std::make_pair("line2", line_top));
  }
}

void HandlerPointerRuler::buildMultiLineTopRight(BaseAllItems *fromParent) {
  SceneView *scn = qobject_cast<SceneView *>(fromParent->scene());
  if (scn) {
    auto line_top = new QGraphicsLineItem(fromParent);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor("blue"));
    line_top->setPen(pen);
    QPointF left;
    QPointF right;
    left.setX(-scn->width());
    left.setY(fromParent->rect().y());
    right.setX(scn->pageItemDesign()->getRect().right());
    right.setY(fromParent->rect().y());
    line_top->setLine(QLineF(left, right));

    auto line_right = new QGraphicsLineItem(fromParent);
    line_right->setPen(pen);
    QPointF top;
    QPointF down;
    top.setX(fromParent->rect().right());
    top.setY(-scn->height());
    down.setX(fromParent->rect().right());
    down.setY(scn->pageItemDesign()->getRect().bottom());
    line_right->setLine(QLineF(top, down));
    m_multiLineMap.insert(std::make_pair("line1", line_top));
    m_multiLineMap.insert(std::make_pair("line2", line_right));
  }
}

void HandlerPointerRuler::updatePosCentralAtas(const QPointF &p) {
  if (m_single_line) {
    SceneView *scn = qobject_cast<SceneView *>(m_single_line->scene());
    if (scn) {
      QPointF left(-scn->width(), p.y());
      QPointF right(scn->pageItemDesign()->getRect().right(), p.y());
      m_single_line->setLine(QLineF(left, right));
    }
  }
}

void HandlerPointerRuler::updatePosCentralKiri(const QPointF &p) {
  if (m_single_line) {
    SceneView *scn = qobject_cast<SceneView *>(m_single_line->scene());
    if (scn) {
      QPointF top(p.x(), -scn->height());
      QPointF down(p.x(), scn->pageItemDesign()->getRect().bottom());
      m_single_line->setLine(QLineF(top, down));
    }
  }
}

void HandlerPointerRuler::updatePosCentralBawah(const QPointF &p) {
  updatePosCentralAtas(p);
}

void HandlerPointerRuler::updatePosCentralKanan(const QPointF &p) {
  updatePosCentralKiri(p);
}

void HandlerPointerRuler::updatePosLeftAndTop(
    const std::pair<QPointF, QPointF> &lt) {
  auto l_s = m_multiLineMap.find("line1");
  auto t_s = m_multiLineMap.find("line2");
  if (l_s != m_multiLineMap.end() && t_s != m_multiLineMap.end()) {
    SceneView *scn = qobject_cast<SceneView *>(l_s->second->scene());
    if (scn) {
      QPointF top(lt.first.x(), -scn->height());
      QPointF down(lt.first.x(), scn->pageItemDesign()->getRect().bottom());
      l_s->second->setLine(QLineF(top, down));

      QPointF left(-scn->width(), lt.second.y());
      QPointF right(scn->pageItemDesign()->getRect().right(), lt.second.y());
      t_s->second->setLine(QLineF(left, right));
    }
  }
}

void HandlerPointerRuler::updatePosRightAndTop(
    const std::pair<QPointF, QPointF> &lt) {
  auto t_s = m_multiLineMap.find("line1");
  auto r_s = m_multiLineMap.find("line2");
  if (t_s != m_multiLineMap.end() && r_s != m_multiLineMap.end()) {
    SceneView *scn = qobject_cast<SceneView *>(t_s->second->scene());
    if (scn) {
      QPointF left(-scn->width(), lt.first.y());
      QPointF right(scn->pageItemDesign()->getRect().right(), lt.first.y());
      t_s->second->setLine(QLineF(left, right));

      QPointF top(lt.second.x(), -scn->height());
      QPointF down(lt.second.x(), scn->pageItemDesign()->getRect().bottom());
      r_s->second->setLine(QLineF(top, down));
    }
  }
}
