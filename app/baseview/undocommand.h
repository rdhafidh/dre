#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <baseallitems.h>
#include <constvalue.h>
#include <itemshapebase.h>
#include <QUndoCommand>

class SceneView;
namespace XCommands {

enum class TypeUndoCommandList {
  MOVE_COMMAND_IS_UNDEFINED,
  MOVE_UNDO_COMMAND = 2,
  MOVE_POS_ONLY_COMMAND,
  INSERT_ITEM_COMMAND,
  DELETE_ITEM_COMMAND,
  MOVE_LINE_COMMAND
};

class MoveLineItemCommand : public QUndoCommand {
 public:
  MoveLineItemCommand(ItemShapeBase *item, const QLineF &newLine,
                      QUndoCommand *parent = nullptr);
  ~MoveLineItemCommand();
  void undo() override;
  void redo() override;
  int id() const override;

 private:
  QObject *currItem;
  QLineF oldLine;
  QLineF newLine;
};

class MoveItemCommand : public QUndoCommand {
 public:
  MoveItemCommand(ItemShapeBase *item, const QRectF &newRect,
                  QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;
  int id() const override;

 private:
  QRectF oldrect;
  QRectF newrect;
  QObject *curritem;
};

class MoveItemPosOnlyCommand : public QUndoCommand {
 public:
  MoveItemPosOnlyCommand(QGraphicsItem *item, const QPointF &newPos,
                         QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;
  int id() const override;

 private:
  QPointF newpos;
  QPointF oldpos;
  QGraphicsItem *curritem;
};

class InsertItemCommand : public QUndoCommand {
 public:
  /*
   * default behaivor ketika insert command
   * tetap selalu di create jadi cuman di mark
   * kalo terjadi undo di removeKindsItem
   * */
  InsertItemCommand(SceneView *fromscene, const QPointF &point,
                    const ItemConst::Tipe &type,
                    QUndoCommand *parent = nullptr);

  void undo() override;
  void redo() override;
  int id() const override;

 private:
  BaseAllItems *newitem;
  ItemConst::Tipe m_tipeitem;
  SceneView *scene;
  QPointF m_TopLeftInit;
};

class DeleteItemCommand : public QUndoCommand {
 public:
  DeleteItemCommand(BaseAllItems *atItem, QUndoCommand *parent = nullptr);

  void undo() override;
  void redo() override;
  int id() const override;

 private:
  BaseAllItems *fromitem;
  SceneView *fromscene;
};
}

#endif  // UNDOCOMMAND_H