#ifndef HANDLERPOINTERRULER_H
#define HANDLERPOINTERRULER_H

#include <QPointF>
#include <map>
#include <utility>

enum class PointerModeRulerOfItem {
  POINTER_MODE_IS_UNDEFINED,
  POINTER_MODE_TOPLEFT,
  POINTER_MODE_TOP,
  POINTER_MODE_TOPRIGHT,
  POINTER_MODE_RIGHT,
  POINTER_MODE_BOTTOMRIGHT,
  POINTER_MODE_BOTTOM,
  POINTER_MODE_BOTTOMLEFT,
  POINTER_MODE_LEFT
};
class BaseAllItems;
class QGraphicsLineItem;

class HandlerPointerRuler {
 public:
  HandlerPointerRuler(const PointerModeRulerOfItem &mode,
                      BaseAllItems *fromParent);
  ~HandlerPointerRuler();
  void updateCentralPos(const QPointF &pos);
  void updateMultiLineCentralPos(const std::pair<QPointF, QPointF> &pf);

  QGraphicsLineItem *singleLineItem();
  bool isMultiLineItem() const;

  void askToDestroyMultiLineItem();
  void askToDestroySingleLineItem();

 private:
  void buildSingleLineHor(BaseAllItems *fromParent);
  void buildSingleLineVert(BaseAllItems *fromParent);
  void buildMultiLineTopLeft(BaseAllItems *fromParent);
  void buildMultiLineTopRight(BaseAllItems *fromParent);
  void buildMultiLineLeftBottom(BaseAllItems *fromParent);
  void buildMultiLineRightBottom(BaseAllItems *fromParent);

  void updatePosCentralAtas(const QPointF &p);
  void updatePosCentralKiri(const QPointF &p);
  void updatePosCentralBawah(const QPointF &p);
  void updatePosCentralKanan(const QPointF &p);
  void updatePosLeftAndTop(const std::pair<QPointF, QPointF> &lt);
  void updatePosRightAndTop(const std::pair<QPointF, QPointF> &lt);
  void updatePosLeftAndBottom(const std::pair<QPointF, QPointF> &lt);
  void updatePosRightAndBottom(const std::pair<QPointF, QPointF> &lt);

  std::pair<QGraphicsLineItem *, QGraphicsLineItem *> getPairMultiLineItem();

  QGraphicsLineItem *m_single_line;
  PointerModeRulerOfItem m_mode;
  std::map<std::string, QGraphicsLineItem *> m_multiLineMap;
};

#endif  // HANDLERPOINTERRULER_H