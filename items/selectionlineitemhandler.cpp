#include "selectionlineitemhandler.h"
#include <QBrush>
#include <QCursor>

SelectionLineItemHandler::SelectionLineItemHandler(QGraphicsItem *parent)
    : QGraphicsRectItem(parent) {
  setAcceptHoverEvents(true);
  setOpacity(0.5);
  setBrush(QBrush(Qt::green));
}
bool SelectionLineItemHandler::isModeEdgeMove() const {
  return m_mode_edge_move;
}
void SelectionLineItemHandler::hoverEnterEvent(
    QGraphicsSceneHoverEvent *event) {
  m_mode_edge_move = true;
  setCursor(QCursor(Qt::SizeAllCursor));
  QGraphicsRectItem::hoverEnterEvent(event);
}
void SelectionLineItemHandler::hoverLeaveEvent(
    QGraphicsSceneHoverEvent *event) {
  m_mode_edge_move = false;
  setCursor(QCursor(Qt::ArrowCursor));
  QGraphicsRectItem::hoverLeaveEvent(event);
}