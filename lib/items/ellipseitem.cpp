#include "ellipseitem.h" 
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPen> 
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

EllipseItem::EllipseItem(QGraphicsItem *parent)
    : BaseAllItems(parent) {
  setItemType(ItemConst::Tipe::BULAT);
  setProperty("borderLine", BORDER_KOSONG);
  setProperty ("lineColor",QColor("black"));
  setProperty ("lineWidth",1.5f);
  setProperty ("fillColorShape",QColor("white"));
}

EllipseItem::~EllipseItem() {}

void EllipseItem::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {

    painter->save ();
    auto path=shape();
    painter->setBrush (QBrush(this->getFillColorShape ()));
    painter->drawPath (path);
    painter->restore ();
    BaseAllItems::paint (painter,option,widget);
}

QPainterPath EllipseItem::shape() const {
    QPen pen;
    pen.setWidthF (this->getLineWidth ());
    pen.setColor (this->getLineColor ());
    
    QPainterPathStroker stroke(pen);
    QPainterPath path; 
    path.addEllipse (this->rect ());
    return stroke.createStroke (path);
}

void EllipseItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
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
