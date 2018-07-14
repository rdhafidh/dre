#include "lineitem.h"
#include <sceneview.h>
#include <undocommand.h>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

LineItem::LineItem(QGraphicsItem *parent)
    : BaseAllItems(parent)  {
  setItemType(ItemConst::Tipe::GARIS);
  connect(this, SIGNAL(askThisLineRightSideToMove(QPointF, QPointF)), this,
          SLOT(updateRightSideLineToMove(QPointF, QPointF)));
  connect(this, SIGNAL(askThisLineLeftSideToMove(QPointF, QPointF)), this,
          SLOT(updateLeftSideLineToMove(QPointF, QPointF))); 
  setProperty("borderLine", BORDER_KOSONG);
  setProperty("fillColorShape", QColor("black"));
  setProperty ("lineColor",QColor("black"));
  setProperty ("lineWidth",1.5f);
}

LineItem::~LineItem() {}

void LineItem::drawLine(const QLineF &line) {
  if (m_currentLine == line) {
    return;
  }
  m_currentLine = line;
  auto path = shape();
  setProperty("geometry", path.controlPointRect());
  update();
}

QLineF LineItem::getLine() const { return m_currentLine; }

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  painter->save();
  auto path = shape();
  painter->setBrush(QBrush(this->getFillColorShape()));
  painter->drawPath(path);
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

QPainterPath LineItem::shape() const {
  QPen pen;
  pen.setColor(this->getLineColor());
  pen.setWidthF(this->getLineWidth());
  QPainterPathStroker stroke(pen);
  QPainterPath path;
  path.moveTo(m_currentLine.p1());
  path.lineTo(m_currentLine.p2());
  return stroke.createStroke(path);
}

void LineItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  QAction *cpAction = menu.addAction("Copy");
  QAction *pasteAction = menu.addAction("Paste");
  QAction *delAction = menu.addAction("Delete");
  QAction *dumpPropertiAction = menu.addAction("Dump Properti");
  QAction *selectedAction = menu.exec(event->screenPos());
  if (selectedAction == cpAction) {
  } else if (selectedAction == pasteAction) {
  } else if (selectedAction == delAction) {
  } else if (selectedAction == dumpPropertiAction) {
    this->dumpPropertiInfo();
  }
}

void LineItem::updateRightSideLineToMove(const QPointF &to,
                                         const QPointF &lastpos) {
  Q_UNUSED(lastpos)
  auto nl = QLineF(m_currentLine.p1(), to);
  this->saveCurrentLinePosStack(nl);
  drawLine(nl);
}

void LineItem::updateLeftSideLineToMove(const QPointF &to,
                                        const QPointF &lastpos) {
  Q_UNUSED(lastpos)
  auto nl = QLineF(to, m_currentLine.p2());
  this->saveCurrentLinePosStack(nl);
  drawLine(nl);
}

void LineItem::saveCurrentLinePosStack(const QLineF &newLine) {
  SceneView *scn = qobject_cast<SceneView *>(this->scene());
  scn->undostack()->push(new XCommands::MoveLineItemCommand(this, newLine));
}
