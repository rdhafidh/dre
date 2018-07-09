#include "undocommand.h"
#include <imageitem.h>
#include <sceneview.h>
#include <textitem.h>
#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <QGraphicsItem>
#include <QStringList>
#include <QVariantList>

XCommands::MoveItemCommand::MoveItemCommand(ItemShapeBase *item,
                                            const QRectF &newRect,
                                            QUndoCommand *parent)
    : QUndoCommand(parent),
      curritem(qobject_cast<QObject *>(item)),
      newrect(newRect) {
  auto var = curritem->property("geometry");
  if (var.isValid() && var.type() == QVariant::RectF) {
    oldrect = var.toRectF();
  }
  setText(QObject::tr("Resize Item"));
}

void XCommands::MoveItemCommand::undo() {
  curritem->setProperty("geometry", oldrect);
}

void XCommands::MoveItemCommand::redo() {
  curritem->setProperty("geometry", newrect);
}

int XCommands::MoveItemCommand::id() const {
  return static_cast<int>(XCommands::TypeUndoCommandList::MOVE_UNDO_COMMAND);
}

XCommands::MoveItemPosOnlyCommand::MoveItemPosOnlyCommand(QGraphicsItem *item,
                                                          const QPointF &newPos,
                                                          QUndoCommand *parent)
    : curritem(item), newpos(newPos), QUndoCommand(parent) {
  oldpos = curritem->pos();
  setText(QObject::tr("Move pos"));
}

void XCommands::MoveItemPosOnlyCommand::undo() { curritem->setPos(oldpos); }

void XCommands::MoveItemPosOnlyCommand::redo() { curritem->setPos(newpos); }

int XCommands::MoveItemPosOnlyCommand::id() const {
  return static_cast<int>(
      XCommands::TypeUndoCommandList::MOVE_POS_ONLY_COMMAND);
}

XCommands::InsertItemCommand::InsertItemCommand(SceneView *fromscene,
                                                const ItemConst::Tipe &type,
                                                QUndoCommand *parent)
    : QUndoCommand(parent),
      scene(fromscene),
      m_tipeitem(type),
      newitem(nullptr) {
  switch (m_tipeitem) {
    case ItemConst::Tipe::BARCODE:
      setText(QObject::tr("Insert Barcode"));
      break;
    case ItemConst::Tipe::BULAT:
      setText(QObject::tr("Insert Shape Ellipse"));
      break;
    case ItemConst::Tipe::GAMBAR:
      setText(QObject::tr("Insert Image"));
      break;
    case ItemConst::Tipe::GARIS:
      setText(QObject::tr("Insert Shape Line"));
      break;
    case ItemConst::Tipe::KOTAK:
      setText(QObject::tr("Insert Shape Rectangle"));
      break;
    case ItemConst::Tipe::SEGITIGA:
      setText(QObject::tr("Insert Shape Triangle"));
      break;
    case ItemConst::Tipe::TEKS:
      setText(QObject::tr("Insert Shape Teks"));
      break;
    default:
      setText(QObject::tr("Insert unknown shape id %1")
                  .arg(static_cast<int>(newitem->getItemType())));
      break;
  }
}

void XCommands::InsertItemCommand::undo() {
  if (newitem != nullptr) {
    scene->removeKindsItem(newitem);
  }
}

void XCommands::InsertItemCommand::redo() {
  if (newitem == nullptr) {
    switch (this->m_tipeitem) {
      case ItemConst::Tipe::TEKS:
        newitem = qobject_cast<SceneView *>(scene)->createTextitem(
            QPointF(10, 10), QSizeF(100, 200));
        break;
      case ItemConst::Tipe::GAMBAR:
        newitem = qobject_cast<SceneView *>(scene)->createImageitem(
            QPointF(10, 10), QSizeF(200, 300));
        break;
    case ItemConst::Tipe::GARIS:
        newitem=qobject_cast<SceneView *>(scene)->createLineItem(QPointF(0,20),QSizeF(180,20));
        break;
      default:
        break;
    }
    return;
  }
  if (newitem->itemIsRemoved()) {
    scene->addKindsItem(newitem);
  }
}

int XCommands::InsertItemCommand::id() const {
  return static_cast<int>(XCommands::TypeUndoCommandList::INSERT_ITEM_COMMAND);
}

XCommands::DeleteItemCommand::DeleteItemCommand(BaseAllItems *atItem,
                                                QUndoCommand *parent)
    : fromitem(atItem),
      QUndoCommand(parent),
      fromscene(qobject_cast<SceneView *>(fromitem->scene())) {
  setText(QObject::tr("Delete Item"));
}

void XCommands::DeleteItemCommand::undo() { fromscene->addKindsItem(fromitem); }

void XCommands::DeleteItemCommand::redo() {
  fromscene->removeKindsItem(fromitem);
}

int XCommands::DeleteItemCommand::id() const {
  return static_cast<int>(XCommands::TypeUndoCommandList::DELETE_ITEM_COMMAND);
}
