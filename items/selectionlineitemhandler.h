#ifndef SELECTIONLINEITEMHANDLER_H
#define SELECTIONLINEITEMHANDLER_H

#include <QGraphicsRectItem>

class SelectionLineItemHandler : public QGraphicsRectItem {
 public:
  explicit SelectionLineItemHandler(QGraphicsItem *parent = nullptr);
  ~SelectionLineItemHandler() {}

  bool isModeEdgeMove() const;

 protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

 private:
  bool m_mode_edge_move = false;
};

#endif  // SELECTIONLINEITEMHANDLER_H