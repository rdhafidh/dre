#ifndef SELECTIONMARKERHANDLEBASE_H
#define SELECTIONMARKERHANDLEBASE_H

#include <constvalue.h>
#include <handlerpointerruler.h>
#include <QBrush>
#include <QGraphicsObject>
#include <QTimer>
#include <memory>
#include <utility>

enum class HandlePosType { UNDEFINED = 0x0, TOP = 1, LEFT, BOTTOM, RIGHT };

class SelectionMarkerHandleBase : public QGraphicsItem {
 public:
  explicit SelectionMarkerHandleBase(QGraphicsItem *parent = nullptr);
  ~SelectionMarkerHandleBase();

  void setItemHandlePosType(HandlePosType type);
  void setCursorType(Qt::CursorShape shape);
  void setForParentItemType(const ItemConst::Tipe &tipeItem);
  void setSelectionMarkerSize(int n);
  void setBrushMarker(const QBrush &b);
  bool isModeResize() const;
  void setRect(const QRectF &r);
  QRectF rect() const;
  void setPointerModeRulerOfItemType(const PointerModeRulerOfItem &ty);
  void updatePointerModeRuleOfItemLinePos(const QPointF &pos);
  void updatePointerModeRuleOfItemLinePos(
      const std::pair<QPointF, QPointF> &pmo);

  void deleteExistingActiveRulerPointer();

 protected:
  // sistem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

 private:
  void handlePointerRulerFromCursorType(const PointerModeRulerOfItem &cursor);

  int markerSize;
  bool moderesize;
  QBrush brush;
  QRectF m_rect;
  ItemConst::Tipe itemType;
  Qt::CursorShape m_cursorshape;
  HandlePosType posisi_handle = HandlePosType::UNDEFINED;
  std::unique_ptr<HandlerPointerRuler> m_hpr;
  QTimer m_show_pointer_timer;
  PointerModeRulerOfItem m_mode_pointer_ruler;
};

#endif  // SELECTIONMARKERHANDLEBASE_H