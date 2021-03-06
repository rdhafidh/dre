#ifndef BASEALLITEMS_H
#define BASEALLITEMS_H

#include <handlerpointerruler.h>
#include <itemshapebase.h>
#include <selectionlineitemhandler.h>
#include <QGraphicsObject>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QTextDocument>
#include <memory>

class SelectionMarkerHandleBase;
class BaseAllItems : public ItemShapeBase, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(
      QRectF geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
  Q_PROPERTY(qreal rotasi READ rotasi WRITE setRotasi NOTIFY rotasiChanged)
 public:
  friend class SelectionMarkerHandleBase;
  explicit BaseAllItems(QGraphicsItem *parent = 0);
  ~BaseAllItems();

  QRectF geometry() const;
  void setGeometry(const QRectF &geom);

  qreal rotasi() const;
  void setRotasi(qreal n);

  /*
   * internal state undo stack helper
   * Item dinyatakan valid berada dalam scene hanya ketika
   * itemIsRemoved()==false , sebaliknya bisa
   * jadi item tersebut masih berada dalam suatu internal state di undostack dan
   * jangan diubah ubah atau proses simpan ketika itemIsRemoved()==false.
   * */
  void setItemIsRemoved(bool e);
  bool itemIsRemoved() const;
  void checkOnlyOnceRulerPointerMode();

 Q_SIGNALS:
  /*
   * notifikasi biar trigger refresh item property
   * seperti info x,y dan z. serta spesialisasi
   * property tersebut
   * */
  void geometryChanged(const QRectF &geom);
  void emitRefreshItemProperty();
  void rotasiChanged(qreal n);
  void forceThisItemSelected(BaseAllItems *item);

  void askThisLineRightSideToMove(const QPointF &toPos, const QPointF &lastPos);
  void askThisLineLeftSideToMove(const QPointF &toPos, const QPointF &lastPos);

 public Q_SLOTS:
  void dumpPropertiInfo();

 protected:
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
  int type() const override;
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

 private:
  void setModeOnOffLineSelection(bool b);
  void setModeOnOffSelection(bool b);
  void updateHandlePos();

  bool modeselect = false;
  ItemConst::Tipe m_tipe;
  int markerSize = 9;
  ItemConst::ModeItemDesignOrPreview m_modedesignpreview;
  SelectionMarkerHandleBase *smpat;
  SelectionMarkerHandleBase *smpsk;
  SelectionMarkerHandleBase *smpsb;
  SelectionMarkerHandleBase *smpsknn;
  SelectionMarkerHandleBase *smh_a_k;
  SelectionMarkerHandleBase *smh_a_knn;
  SelectionMarkerHandleBase *smh_b_knn;
  SelectionMarkerHandleBase *smh_b_kr;
  std::unique_ptr<SelectionLineItemHandler> m_h_l_knn;
  std::unique_ptr<SelectionLineItemHandler> m_h_l_kr;
  qreal m_rotasi;
  bool m_itemIsRemoved;
  PointerModeRulerOfItem m_currentModeRulerPointer;
};

#endif  // BASEALLITEMS_H