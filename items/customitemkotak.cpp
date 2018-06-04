#include "customitemkotak.h"
#include <stdlib.h>
#include <QAction>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
#include <QPointF>
#include "dialog/dialogresizeitem.h"

#include "selectionmarkerhandlebase.h"
#include <QApplication>
#include <customscene.h>

CustomItemKotak::CustomItemKotak(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      smpat(nullptr),
      smpsk(nullptr),
      smpsb(nullptr),
      smpsknn(nullptr),
      smh_a_k(nullptr),
      smh_a_knn(nullptr),
      smh_b_knn(nullptr),
    smh_b_kr(nullptr){
  setFlags(QGraphicsItem::ItemIsMovable |
          /* QGraphicsItem::ItemSendsGeometryChanges | */ QGraphicsItem::ItemSendsScenePositionChanges |
           QGraphicsItem::ItemIsSelectable  );
  setAcceptHoverEvents(true);
  typeitem=ItemConst::Tipe::KOTAK;
}

CustomItemKotak::~CustomItemKotak() {}

void CustomItemKotak::setRect(const QRectF &r) {
  prepareGeometryChange();
  m_rect = r;
}

void CustomItemKotak::setPen(const QPen &p) {
  mypen = p;
  update();
}

void CustomItemKotak::setHeight(qreal p) {
  if (m_rect.height() == p) return;

  prepareGeometryChange();
  m_rect = QRectF(m_rect.x(), m_rect.y(), m_rect.width(), p);
}

void CustomItemKotak::setWidth(qreal w) {
  if (m_rect.width() == w) return;

  prepareGeometryChange();
  m_rect = QRectF(m_rect.x(), m_rect.y(), w, m_rect.height());
}

void CustomItemKotak::setItemType(const ItemConst::Tipe &tipe)
{
    typeitem=tipe;
}

ItemConst::Tipe CustomItemKotak::getItemType() const
{
    return typeitem;
}

void CustomItemKotak::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setPen(mypen);
  auto gambarsegitiga=[this](QPainter *painter){
      painter->drawLine (m_rect.bottomLeft ().toPoint (),m_rect.bottomRight ().toPoint ());
      qreal tengah=this->m_rect.left () +this->m_rect.width ()/2;
      painter->drawLine (m_rect.bottomLeft ().toPoint (),QPoint(tengah,this->m_rect.top ()));
      painter->drawLine (m_rect.bottomRight ().toPoint (),QPoint(tengah,this->m_rect.top ()));
  };
  auto gambarteks=[this](QPainter *painter){
      painter->drawRect (this->m_rect);
      
  };

  switch (typeitem) {
  case ItemConst::Tipe::KOTAK: 
      painter->drawRect(m_rect);
      break;
  case ItemConst::Tipe::BULAT:
      painter->drawEllipse (m_rect);
      break;
  case ItemConst::Tipe::SEGITIGA: 
      gambarsegitiga(painter);
      break;
  default:
      break;
  }
}

void CustomItemKotak::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    
   auto isalllHandelNotNull=[this]() {
          if(this->smh_a_k && this->smh_a_knn
                  && this->smh_b_knn && this->smh_b_kr
                  && this->smpat && this->smpsb 
                  && this->smpsk && this->smpsknn ){
              return true;
          }
          return false;
    };
  if (isSelected() && isalllHandelNotNull() && smpat->isModeResize()  ) {
    qreal minheight = smpat->getRect().height() * 2;

    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minheight
             << "smpat pos" << smpat->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << m_rect.bottom();

    prepareGeometryChange();
    qreal posTopCorner = m_rect.top() + event->pos().y() - event->lastPos().y();
    qDebug() << "====================== before set ====================";
    qDebug() << "m_rect.top ()" << m_rect.top() << "posTopCorner"
             << posTopCorner;
    qDebug() << "======================  end =========================";

    qreal overlap = m_rect.bottom() - m_rect.top();
    if (overlap <= minheight && m_rect.top() < posTopCorner) {
      qDebug() << "overlap " << overlap << "found m_rect.top () "
               << m_rect.top() << "posTopCorner" << posTopCorner << "bottom"
               << m_rect.bottom();
      return;
    }
//    int gridsize=qobject_cast<CustomScene*>(scene())->getGridSize ();
//    int xtop=(int)std::floor(posTopCorner)% gridsize;
//     qreal xxtop =posTopCorner-xtop;
    m_rect.setTop(posTopCorner);
    updateHandlePos();
    qDebug() << "rect top" << m_rect.top() << "currentpoint" << currentpoint.y()
             << "minheight" << (qreal)minheight << "posTopCorner"
             << posTopCorner;
    update();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smpsb->isModeResize()) {
    qreal minheight = smpsb->getRect().height() * 2;

    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minheight
             << "smpat pos" << smpat->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << m_rect.bottom();

    prepareGeometryChange();
    qreal posBottom = m_rect.bottom() + event->pos().y() - event->lastPos().y();

    qreal overlap = m_rect.bottom() - m_rect.top();
    qDebug() << "====================== before set ====================";
    qDebug() << "m_rect.posBottom ()" << m_rect.bottom() << "posBottom"
             << posBottom;
    qDebug() << "overlap" << overlap;
    qDebug() << "======================  end =========================";
    if (overlap <= minheight && m_rect.bottom() > posBottom) {
      qDebug() << "found m_rect.bottom () " << m_rect.bottom() << "posbotom"
               << posBottom;
      return;
    }
    m_rect.setBottom(posBottom);
    updateHandlePos();
    update();
    qDebug() << "rect bottom" << m_rect.bottom() << "currentpoint"
             << currentpoint.y() << "minheight" << (qreal)minheight
             << "posBottom" << posBottom;

    return;
  }
  if (isSelected() && isalllHandelNotNull() && smpsk->isModeResize()) {
    qreal minwidthhandle = smpsk->getRect().width() * 2;
    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minwidthhandle
             << "smpat pos" << smpat->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << m_rect.bottom();

    prepareGeometryChange();
    qreal posLeft = m_rect.left() + event->pos().x() - event->lastPos().x();
    qreal overlap = m_rect.right() - m_rect.left();
    if (overlap <= minwidthhandle && m_rect.left() < posLeft) {
      qDebug() << "overlap " << overlap << "found m_rect.left () "
               << m_rect.left() << "posLeft" << posLeft << "right"
               << m_rect.right();
      return;
    }
    m_rect.setLeft(posLeft);
    updateHandlePos();
    update();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smpsknn->isModeResize()) {
    qreal minwidthhandle = smpsknn->getRect().width() * 2;
    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minwidthhandle
             << "smpat pos" << smpsknn->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << m_rect.bottom();

    prepareGeometryChange();
    qreal posRight = m_rect.right() + event->pos().x() - event->lastPos().x();
    qreal overlap = m_rect.right() - m_rect.left();
    if (overlap <= minwidthhandle && m_rect.right() > posRight) {
      qDebug() << "overlap " << overlap << "found m_rect.right () "
               << m_rect.right() << "posRight" << posRight << "left"
               << m_rect.left();
      return;
    }
    m_rect.setRight(posRight);
    updateHandlePos();
    update();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smh_b_knn->isModeResize()) {
      prepareGeometryChange ();
      //double handle bawah sama kanan
      //bawah dulu
      qreal minheighthandlebottom = smpsb->getRect().height() * 2;
      qreal posBottom = m_rect.bottom() + event->pos().y() - event->lastPos().y();
  
      qreal overlap = m_rect.bottom() - m_rect.top();
      if (overlap <= minheighthandlebottom && m_rect.bottom() > posBottom) {
        qDebug() << "found m_rect.bottom () phase bawah kanan bag bawah " << m_rect.bottom() << "posbotom"
                 << posBottom;
        return;
      }
      m_rect.setBottom(posBottom);
      
      //baru kanan
      qreal minwidthandlekanan = smpsknn->getRect().width() * 2;
      qreal posRight = m_rect.right() + event->pos().x() - event->lastPos().x();
      overlap = m_rect.right() - m_rect.left();
      if (overlap <= minwidthandlekanan && m_rect.right() > posRight) {
        qDebug() << "overlap " << overlap << "found m_rect.right () phase bawah kanan bag kanan"<< m_rect.right() << "posRight" << posRight << "left"
                 << m_rect.left();
        return;
      }
      m_rect.setRight(posRight);
      
      updateHandlePos ();
      update ();
      return;
  }

  if (isSelected() && isalllHandelNotNull() && smh_a_k->isModeResize()) {
    prepareGeometryChange();
    // double handle atas sama kiri
    // atas dulu
    qreal posTopCorner = m_rect.top() + event->pos().y() - event->lastPos().y();
    qreal minheight_bag_atas = smpat->getRect().height() * 2;

    qreal overlap = m_rect.bottom() - m_rect.top();
    if (overlap <= minheight_bag_atas && m_rect.top() < posTopCorner) {
      qDebug() << "overlap  phase atas kiri bag atas " << overlap
               << "found m_rect.top () " << m_rect.top() << "posTopCorner"
               << posTopCorner << "bottom" << m_rect.bottom();
      return;
    }
    m_rect.setTop(posTopCorner);
    // handle sisi kiri
    qreal minwidth_bag_kiri = smh_a_k->getRect().width() * 2;
    qreal posLeft = m_rect.left() + event->pos().x() - event->lastPos().x();
    overlap = m_rect.right() - m_rect.left();
    if (overlap <= minwidth_bag_kiri && m_rect.left() < posLeft) {
      qDebug() << "overlap phase atas kiri bag kiri" << overlap
               << "found m_rect.left () " << m_rect.left() << "posLeft"
               << posLeft << "right" << m_rect.right();
      return;
    }
    m_rect.setLeft(posLeft);

    updateHandlePos();
    update();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smh_a_knn->isModeResize()) {
    prepareGeometryChange();
    // double handle atas sama kanan
    // atas dulu
    qreal posTopCorner = m_rect.top() + event->pos().y() - event->lastPos().y();
    qreal minheight_bag_atas = smh_a_knn->getRect().height() * 2;

    qreal overlap = m_rect.bottom() - m_rect.top();
    if (overlap <= minheight_bag_atas && m_rect.top() < posTopCorner) {
      qDebug() << "overlap  phase atas kanan bag atas " << overlap
               << "found m_rect.top () " << m_rect.top() << "posTopCorner"
               << posTopCorner << "bottom" << m_rect.bottom();
      return;
    }
    m_rect.setTop(posTopCorner);
    // handle sisi kanan
    qreal minwidth_bag_kanan = smh_a_knn->getRect().width() * 2;
    qreal posRight = m_rect.right() + event->pos().x() - event->lastPos().x();
    overlap = m_rect.right() - m_rect.left();
    if (overlap <= minwidth_bag_kanan && m_rect.right() > posRight) {
      qDebug() << "overlap phase atas kanan bag kanan" << overlap
               << "found m_rect.right () " << m_rect.right() << "posRight"
               << posRight << "left" << m_rect.left();
      return;
    }
    m_rect.setRight(posRight);

    updateHandlePos();
    update();
    return;
  }

  if(isSelected () && isalllHandelNotNull() && smh_b_kr->isModeResize ()){
      prepareGeometryChange ();
      //doubel handle bawah kiri pojok
      //handle bawah dulu
      qreal minheighthandlebottom = smpsb->getRect().height() * 2;
      qreal posBottom = m_rect.bottom() + event->pos().y() - event->lastPos().y();
  
      qreal overlap = m_rect.bottom() - m_rect.top();
      if (overlap <= minheighthandlebottom && m_rect.bottom() > posBottom) {
        qDebug() << "found m_rect.bottom () phase bawah kiri bag bawah " << m_rect.bottom() << "posbotom"
                 << posBottom;
        return;
      }
      m_rect.setBottom(posBottom);
      //handle sisi kiri
      qreal minwidthhandlekiri = smpsk->getRect().width() * 2;  
      qreal posLeft = m_rect.left() + event->pos().x() - event->lastPos().x();
      overlap = m_rect.right() - m_rect.left();
      if (overlap <= minwidthhandlekiri && m_rect.left() < posLeft) {
        qDebug() << "overlap phase bawah kiri bagian kiri" << overlap << "found m_rect.left () "
                 << m_rect.left() << "posLeft" << posLeft << "right"
                 << m_rect.right();
        return;
      }
      m_rect.setLeft(posLeft);
      
      updateHandlePos();
      update();
      return;
  }
  
  QGraphicsItem::mouseMoveEvent(event);
}
void CustomItemKotak::mousePressEvent(QGraphicsSceneMouseEvent *event)

{
  setSelected(true);
  currentpoint = event->scenePos();
  QGraphicsItem::mousePressEvent(event);
}

void CustomItemKotak::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseReleaseEvent(event);
}

QVariant CustomItemKotak::itemChange(QGraphicsItem::GraphicsItemChange change,
                                     const QVariant &value) { 
  if (change == QGraphicsItem::ItemSelectedChange) {
    this->setModeOnOffSelection(value.toBool());
  }
  if (change == QGraphicsItem::ItemPositionHasChanged) {
    //  updateSelectionMarker();
      //  this->setModeOnOffSelection (true);
  }
  if( change==QGraphicsItem::ItemPositionChange && scene()){
     QPointF newpos=value.toPointF ();
     if(QApplication::mouseButtons () ==Qt::LeftButton && qobject_cast<CustomScene*>(scene())){
         int gridsize=qobject_cast<CustomScene*>(scene())->getGridSize ();
         qreal x=round(newpos.x ()/gridsize)*gridsize;
         qreal y=round(newpos.y ()/gridsize)*gridsize;
         return QPointF(x,y);
     }
  }
  return QGraphicsItem::itemChange(change, value);
}

QRectF CustomItemKotak::boundingRect() const { return m_rect; }

QPainterPath CustomItemKotak::shape() const {
  QPainterPath path;
  path.addRect(m_rect);
  return path;
}

void CustomItemKotak::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  QAction *act = menu.addAction(QObject::tr("resize"));
  QObject::connect(act, &QAction::triggered, [this](bool a) {
    qDebug() << "resize fired!!";
    this->handleCustomCmdResize();
  });
  menu.exec(event->screenPos());
}

void CustomItemKotak::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  qDebug() << "hover mouse pos" << mapToScene(event->pos());
  QGraphicsItem::hoverEnterEvent(event);
}

int CustomItemKotak::type() const {
  return static_cast<int>(typeitem);
}

void CustomItemKotak::setModeOnOffSelection(bool b) {
  modeselect = b;
  if (b && !smpat && !smpsk && !smpsb && !smpsknn && !smh_a_k) {
    smpat = new SelectionMarkerHandleBase(this);
    smpat->setCursorType(Qt::SizeVerCursor);
    smpat->setForParentItemType(ItemConst::Tipe::KOTAK);
    updateHandlePos();
    smpat->setSelectionMarkerSize(markerSize);
    smpat->setBrushMarker(QBrush(Qt::green));
    smpat->setPos(0, 0);
    smpat->setVisible(true);

    smpsk = new SelectionMarkerHandleBase(this);
    smpsk->setCursorType(Qt::SizeHorCursor);
    smpsk->setForParentItemType(ItemConst::Tipe::KOTAK);
    updateHandlePos();
    smpsk->setSelectionMarkerSize(markerSize);
    smpsk->setBrushMarker(QBrush(Qt::green));
    smpsk->setPos(0, 0);
    smpsk->setVisible(true);

    smpsb = new SelectionMarkerHandleBase(this);
    smpsb->setCursorType(Qt::SizeVerCursor);
    smpsb->setForParentItemType(ItemConst::Tipe::KOTAK);
    smpsb->setSelectionMarkerSize(markerSize);
    smpsb->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smpsb->setPos(0, 0);
    smpsb->setVisible(true);

    smpsknn = new SelectionMarkerHandleBase(this);
    smpsknn->setCursorType(Qt::SizeHorCursor);
    smpsknn->setForParentItemType(ItemConst::Tipe::KOTAK);
    smpsknn->setSelectionMarkerSize(markerSize);
    smpsknn->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smpsknn->setPos(0, 0);
    smpsknn->setVisible(true);

    smh_a_k = new SelectionMarkerHandleBase(this);
    smh_a_k->setCursorType(Qt::SizeFDiagCursor);
    smh_a_k->setForParentItemType(ItemConst::Tipe::KOTAK);
    smh_a_k->setSelectionMarkerSize(markerSize);
    smh_a_k->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_a_k->setPos(0, 0);
    smh_a_k->setVisible(true);

    smh_a_knn = new SelectionMarkerHandleBase(this);
    smh_a_knn->setCursorType(Qt::SizeBDiagCursor);
    smh_a_knn->setForParentItemType(ItemConst::Tipe::KOTAK);
    smh_a_knn->setSelectionMarkerSize(markerSize);
    smh_a_knn->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_a_knn->setPos(0, 0);
    smh_a_knn->setVisible(true);

    smh_b_knn = new SelectionMarkerHandleBase(this);
    smh_b_knn->setCursorType(Qt::SizeFDiagCursor);
    smh_b_knn->setForParentItemType(ItemConst::Tipe::KOTAK);
    smh_b_knn->setSelectionMarkerSize(markerSize);
    smh_b_knn->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_b_knn->setPos(0, 0);
    smh_b_knn->setVisible(true);
    
    smh_b_kr = new SelectionMarkerHandleBase(this);
    smh_b_kr->setCursorType(Qt::SizeBDiagCursor);
    smh_b_kr->setForParentItemType(ItemConst::Tipe::KOTAK);
    smh_b_kr->setSelectionMarkerSize(markerSize);
    smh_b_kr->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_b_kr->setPos(0, 0);
    smh_b_kr->setVisible(true);
    qDebug() << Q_FUNC_INFO << "called baris" << __LINE__
             << " SET selection";
  } else {
    if (scene() && smpat && smpsk && smpsb /* blabla */) {
      scene()->removeItem(smpat);
      delete smpat;
      smpat = nullptr;

      scene()->removeItem(smpsk);
      delete smpsk;
      smpsk = nullptr;

      scene()->removeItem(smpsb);
      delete smpsb;
      smpsb = nullptr;

      scene()->removeItem(smpsknn);
      delete smpsknn;
      smpsknn = nullptr;

      scene()->removeItem(smh_a_k);
      delete smh_a_k;
      smh_a_k = nullptr;

      scene()->removeItem(smh_a_knn);
      delete smh_a_knn;
      smh_a_knn = nullptr;

      scene()->removeItem(smh_b_knn);
      delete smh_b_knn;
      smh_b_knn = nullptr;
      
      scene()->removeItem(smh_b_kr);
      delete smh_b_kr;
      smh_b_kr=nullptr;
      qDebug() << Q_FUNC_INFO << "called baris" << __LINE__
               << "clear selection";
    }
  }

}

void CustomItemKotak::handleCustomCmdResize() {
  if (scene() && scene()->views().size() > 0) {
    QGraphicsView *vw = scene()->views().at(0);
    if (vw) {
      DialogResizeItem *itm = new DialogResizeItem(vw);
      itm->prepareItemShowPos(pos());
      itm->prepareShownSetWidthAndHeight(this->m_rect.width(),
                                         this->m_rect.height());
      itm->setAttribute(Qt::WA_DeleteOnClose);
      QObject::connect(itm, &DialogResizeItem::emitPosXdanY,
                       [this](int x, int y) { setPos(x, y); });
      QObject::connect(itm, &DialogResizeItem::emitSetWidthDanHeight,
                       [this](int w, int h) {
                         qDebug() << "emitted change w " << w << "h" << h;
                         this->setWidth(w);
                         this->setHeight(h);

                       });
      itm->exec();
    }
  }
}

void CustomItemKotak::updateHandlePos() {
  // guard
  if (!smpat || !smpsk || !smpsb || !smpsknn || !smh_a_k || !smh_a_knn ||
      !smh_b_knn
          || !smh_b_kr)
    return;

  smpat->setRect(QRectF(m_rect.left() + m_rect.width() / 2 - markerSize,
                        m_rect.top() - markerSize, markerSize * 2,
                        markerSize * 2));
  smpsk->setRect(QRectF(m_rect.left() - markerSize,
                        m_rect.bottom() - m_rect.height() / 2 - markerSize,
                        markerSize * 2, markerSize * 2));
  smpsb->setRect(QRectF(m_rect.left() + m_rect.width() / 2 - markerSize,
                        m_rect.bottom() - markerSize, markerSize * 2,
                        markerSize * 2));
  smpsknn->setRect(QRectF(m_rect.right() - markerSize,
                          m_rect.bottom() - m_rect.height() / 2 - markerSize,
                          markerSize * 2, markerSize * 2));

  smh_a_k->setRect(QRectF(m_rect.topLeft().x() - markerSize,
                          m_rect.top() - markerSize, markerSize * 2,
                          markerSize * 2));

  smh_a_knn->setRect(QRectF(m_rect.topRight().x() - markerSize,
                            m_rect.top() - markerSize, markerSize * 2,
                            markerSize * 2));
  smh_b_knn->setRect(QRectF(m_rect.bottomRight().x() - markerSize,
                            m_rect.bottom() - markerSize, markerSize * 2,
                            markerSize * 2));
   smh_b_kr->setRect(QRectF(m_rect.bottomLeft ().x() - markerSize,
                                    m_rect.bottom() - markerSize, markerSize * 2,
                                    markerSize * 2));
}
