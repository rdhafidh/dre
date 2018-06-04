#include "baseallitems.h"
#include <pageitem.h>
#include <sceneview.h>
#include <undocommand.h>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMetaObject>
#include <QMetaProperty>
#include "selectionmarkerhandlebase.h"
#include <QApplication>

BaseAllItems::BaseAllItems(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      ItemShapeBase(),m_itemIsRemoved(false),
      smpat(nullptr),
      smpsk(nullptr),
      smpsb(nullptr),
      smpsknn(nullptr),
      smh_a_k(nullptr),
      smh_a_knn(nullptr),
      smh_b_knn(nullptr),
      smh_b_kr(nullptr),
      m_rotasi(0) {
  setAcceptHoverEvents(true);
  setFlags(QGraphicsItem::ItemIsMovable |
           QGraphicsItem::ItemSendsScenePositionChanges |
           QGraphicsItem::ItemIsSelectable);
  connect(this, &BaseAllItems::askUpdate, [this]() {
    this->updateHandlePos();
    this->update(this->geometry());
  });
  connect(this, &BaseAllItems::geometryChanged,
          [this](const QRectF &geom) {    this->updateHandlePos(); this->update(geom); });
}

BaseAllItems::~BaseAllItems() {}

QRectF BaseAllItems::geometry() const {
  return QRectF(pos().x(), pos().y(), localrect.width(), localrect.height());
}

void BaseAllItems::setGeometry(const QRectF &geom) {
  QRectF localgeom(pos().x(), pos().y(), localrect.width(), localrect.height());
  if (localgeom == geom) return;

  prepareGeometryChange();
  setPos(geom.x(), geom.y());
  //  localrect.setX (geom.x ());
  //  localrect.setY (geom.y ());
  //  localrect.setWidth (geom.width ());
  //  localrect.setHeight (geom.height ());
  localrect = QRectF(geom.x(), geom.y(), geom.width(), geom.height());
  this->geometryChanged(geom);
}

qreal BaseAllItems::rotasi() const { return m_rotasi; }

void BaseAllItems::setRotasi(qreal n) {
  if (m_rotasi == n) return;

  setTransformOriginPoint (localrect.width ()/2,
                           localrect.height ()/2);
  setRotation(m_rotasi); 
  m_rotasi = n;
  updateHandlePos();
  update();
}

void BaseAllItems::setItemIsRemoved(bool e)
{
    m_itemIsRemoved=e;
}

bool BaseAllItems::itemIsRemoved() const
{
    return m_itemIsRemoved;
}

void BaseAllItems::dumpPropertiInfo() {
  const QMetaObject *metaObject = this->metaObject();
  for (int i = 0; i < metaObject->propertyCount(); ++i) {
    auto prop = QString::fromLatin1(metaObject->property(i).name());
    qDebug() << "prop " << prop << "type" << metaObject->property(i).type()
             << "isenum" << metaObject->property(i).isEnumType() << "value "
             << property(prop.toStdString().c_str());
  }
  qDebug() << "localrect" << localrect;
}

QRectF BaseAllItems::boundingRect() const { return this->rect(); }

QPainterPath BaseAllItems::shape() const {
  QPainterPath p;
  p.addRect(this->rect());
  return p;
}

void BaseAllItems::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  ItemShapeBase::paintShape(painter);
}

void BaseAllItems::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (event->modifiers() & Qt::ControlModifier) {
    event->ignore();
  } else {
    // dont emit  setSelected (true);
    // karena qgraphicsscene sudah ngatur via selection changed signal
    QGraphicsItem::mousePressEvent(event);
  }
}

void BaseAllItems::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  auto isalllHandelNotNull = [this]() {
    if (this->smh_a_k && this->smh_a_knn && this->smh_b_knn && this->smh_b_kr &&
        this->smpat && this->smpsb && this->smpsk && this->smpsknn &&
        this->scene()) {
      return true;
    }
    return false;
  };

  if (isSelected() && isalllHandelNotNull() && smpat->isModeResize()) {
    qreal minheight = smpat->rect().height() * 2;

    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minheight
             << "smpat pos" << smpat->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << localrect.bottom();

    prepareGeometryChange();
    qreal posTopCorner =
        localrect.top() + event->pos().y() - event->lastPos().y();
    qDebug() << "====================== before set ====================";
    qDebug() << "localrect.top ()" << localrect.top() << "posTopCorner"
             << posTopCorner;
    qDebug() << "======================  end =========================";

    qreal overlap = localrect.bottom() - localrect.top();
    if (overlap <= minheight && localrect.top() < posTopCorner) {
      qDebug() << "overlap " << overlap << "found localrect.top () "
               << localrect.top() << "posTopCorner" << posTopCorner << "bottom"
               << localrect.bottom();
      return;
    } 
    
    //disini cuman y sbg postopcorner
    
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posTopCorner = round(posTopCorner / gridsize) * gridsize;
    localrect.setTop(posTopCorner);
    updateHandlePos(); 
    
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    qDebug() << "rect top" << localrect.top() << "currentpoint"
             << "minheight" << (qreal)minheight << "posTopCorner"
             << posTopCorner;

    
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smpsb->isModeResize()) {
    qreal minheight = smpsb->rect().height() * 2;

    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minheight
             << "smpat pos" << smpat->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << localrect.bottom();

    prepareGeometryChange();
    qreal posBottom =
        localrect.bottom() + event->pos().y() - event->lastPos().y();

    qreal overlap = localrect.bottom() - localrect.top();
    qDebug() << "====================== before set ====================";
    qDebug() << "localrect.posBottom ()" << localrect.bottom() << "posBottom"
             << posBottom;
    qDebug() << "overlap" << overlap;
    qDebug() << "======================  end =========================";
    if (overlap <= minheight && localrect.bottom() > posBottom) {
      qDebug() << "found localrect.bottom () " << localrect.bottom()
               << "posbotom" << posBottom;
      return;
    } 
    
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posBottom = round(posBottom / gridsize) * gridsize; 
    
    localrect.setBottom(posBottom);
    updateHandlePos();
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    this->rectChanged(localrect);
    update(localrect);
    qDebug() << "rect bottom" << localrect.bottom() << "minheight"
             << (qreal)minheight << "posBottom" << posBottom;

    this->emitRefreshItemProperty();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smpsk->isModeResize()) {
    qreal minwidthhandle = smpsk->rect().width() * 2;
    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minwidthhandle
             << "smpat pos" << smpat->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << localrect.bottom();

    prepareGeometryChange();
    qreal posLeft = localrect.left() + event->pos().x() - event->lastPos().x();
    qreal overlap = localrect.right() - localrect.left();
    if (overlap <= minwidthhandle && localrect.left() < posLeft) {
      qDebug() << "overlap " << overlap << "found localrect.left () "
               << localrect.left() << "posLeft" << posLeft << "right"
               << localrect.right();
      return;
    }
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posLeft = round(posLeft / gridsize) * gridsize; 
    
    localrect.setLeft(posLeft);
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    updateHandlePos();
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smpsknn->isModeResize()) {
    qreal minwidthhandle = smpsknn->rect().width() * 2;
    qDebug() << "item y " << y() << " mouse y scene " << event->scenePos().y()
             << "mouse y screen" << event->screenPos().y() << "height"
             << boundingRect().height() << "min height" << minwidthhandle
             << "smpat pos" << smpsknn->pos() << "current item pos" << pos()
             << "mapToScene (event->pos ()).y()" << mapToScene(event->pos()).y()
             << "bottom" << localrect.bottom();

    prepareGeometryChange();
    qreal posRight =
        localrect.right() + event->pos().x() - event->lastPos().x();
    qreal overlap = localrect.right() - localrect.left();
    if (overlap <= minwidthhandle && localrect.right() > posRight) {
      qDebug() << "overlap " << overlap << "found localrect.right () "
               << localrect.right() << "posRight" << posRight << "left"
               << localrect.left();
      return;
    }
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posRight = round(posRight / gridsize) * gridsize; 
    
    localrect.setRight(posRight);
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    updateHandlePos();
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smh_b_knn->isModeResize()) {
    prepareGeometryChange();
    // double handle bawah sama kanan
    // bawah dulu
    qreal minheighthandlebottom = smpsb->rect().height() * 2;
    qreal posBottom =
        localrect.bottom() + event->pos().y() - event->lastPos().y();

    qreal overlap = localrect.bottom() - localrect.top();
    if (overlap <= minheighthandlebottom && localrect.bottom() > posBottom) {
      qDebug() << "found localrect.bottom () phase bawah kanan bag bawah "
               << localrect.bottom() << "posbotom" << posBottom;
      return;
    }
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posBottom = round(posBottom / gridsize) * gridsize; 
    
    localrect.setBottom(posBottom);

    // baru kanan
    qreal minwidthandlekanan = smpsknn->rect().width() * 2;
    qreal posRight =
        localrect.right() + event->pos().x() - event->lastPos().x();
    overlap = localrect.right() - localrect.left();
    if (overlap <= minwidthandlekanan && localrect.right() > posRight) {
      qDebug() << "overlap " << overlap
               << "found localrect.right () phase bawah kanan bag kanan"
               << localrect.right() << "posRight" << posRight << "left"
               << localrect.left();
      return;
    } 
    posRight = round(posRight / gridsize) * gridsize; 
    localrect.setRight(posRight);
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    updateHandlePos();
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }

  if (isSelected() && isalllHandelNotNull() && smh_a_k->isModeResize()) {
    prepareGeometryChange();
    // double handle atas sama kiri
    // atas dulu
    qreal posTopCorner =
        localrect.top() + event->pos().y() - event->lastPos().y();
    qreal minheight_bag_atas = smpat->rect().height() * 2;

    qreal overlap = localrect.bottom() - localrect.top();
    if (overlap <= minheight_bag_atas && localrect.top() < posTopCorner) {
      qDebug() << "overlap  phase atas kiri bag atas " << overlap
               << "found localrect.top () " << localrect.top() << "posTopCorner"
               << posTopCorner << "bottom" << localrect.bottom();
      return;
    }
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posTopCorner = round(posTopCorner / gridsize) * gridsize; 
    localrect.setTop(posTopCorner);
    // handle sisi kiri
    qreal minwidth_bag_kiri = smh_a_k->rect().width() * 2;
    qreal posLeft = localrect.left() + event->pos().x() - event->lastPos().x();
    overlap = localrect.right() - localrect.left();
    if (overlap <= minwidth_bag_kiri && localrect.left() < posLeft) {
      qDebug() << "overlap phase atas kiri bag kiri" << overlap
               << "found localrect.left () " << localrect.left() << "posLeft"
               << posLeft << "right" << localrect.right();
      return;
    } 
    posLeft = round(posLeft / gridsize) * gridsize; 
    localrect.setLeft(posLeft);
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    updateHandlePos();
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }
  if (isSelected() && isalllHandelNotNull() && smh_a_knn->isModeResize()) {
    prepareGeometryChange();
    // double handle atas sama kanan
    // atas dulu
    qreal posTopCorner =
        localrect.top() + event->pos().y() - event->lastPos().y();
    qreal minheight_bag_atas = smh_a_knn->rect().height() * 2;

    qreal overlap = localrect.bottom() - localrect.top();
    if (overlap <= minheight_bag_atas && localrect.top() < posTopCorner) {
      qDebug() << "overlap  phase atas kanan bag atas " << overlap
               << "found localrect.top () " << localrect.top() << "posTopCorner"
               << posTopCorner << "bottom" << localrect.bottom();
      return;
    }
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posTopCorner = round(posTopCorner / gridsize) * gridsize; 
    localrect.setTop(posTopCorner);
    // handle sisi kanan
    qreal minwidth_bag_kanan = smh_a_knn->rect().width() * 2;
    qreal posRight =
        localrect.right() + event->pos().x() - event->lastPos().x();
    overlap = localrect.right() - localrect.left();
    if (overlap <= minwidth_bag_kanan && localrect.right() > posRight) {
      qDebug() << "overlap phase atas kanan bag kanan" << overlap
               << "found localrect.right () " << localrect.right() << "posRight"
               << posRight << "left" << localrect.left();
      return;
    } 
    posRight = round(posRight / gridsize) * gridsize; 
    localrect.setRight(posRight);
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    updateHandlePos();
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }

  if (isSelected() && isalllHandelNotNull() && smh_b_kr->isModeResize()) {
    prepareGeometryChange();
    // doubel handle bawah kiri pojok
    // handle bawah dulu
    qreal minheighthandlebottom = smpsb->rect().height() * 2;
    qreal posBottom =
        localrect.bottom() + event->pos().y() - event->lastPos().y();

    qreal overlap = localrect.bottom() - localrect.top();
    if (overlap <= minheighthandlebottom && localrect.bottom() > posBottom) {
      qDebug() << "found localrect.bottom () phase bawah kiri bag bawah "
               << localrect.bottom() << "posbotom" << posBottom;
      return;
    }
    int gridsize =
        qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize(); 
    posBottom = round(posBottom / gridsize) * gridsize; 
    localrect.setBottom(posBottom);
    // handle sisi kiri
    qreal minwidthhandlekiri = smpsk->rect().width() * 2;
    qreal posLeft = localrect.left() + event->pos().x() - event->lastPos().x();
    overlap = localrect.right() - localrect.left();
    if (overlap <= minwidthhandlekiri && localrect.left() < posLeft) {
      qDebug() << "overlap phase bawah kiri bagian kiri" << overlap
               << "found localrect.left () " << localrect.left() << "posLeft"
               << posLeft << "right" << localrect.right();
      return;
    }
    posLeft = round(posLeft / gridsize) * gridsize; 
    localrect.setLeft(posLeft);
    SceneView *scn = qobject_cast<SceneView *>(this->scene());
    QRectF localgeom(pos().x(), pos().y(), localrect.width(),
                     localrect.height());
    scn->undostack()->push(new XCommands::MoveItemCommand(this, localgeom));
    updateHandlePos();
    this->rectChanged(localrect);
    update(localrect);

    this->emitRefreshItemProperty();
    return;
  }

  QGraphicsItem::mouseMoveEvent(event);
  SceneView *scn = qobject_cast<SceneView *>(this->scene());
  scn->undostack()->push(new XCommands::MoveItemPosOnlyCommand(this, pos()));

  this->emitRefreshItemProperty();
}

int BaseAllItems::type() const { return static_cast<int>(getItemType()); }

void BaseAllItems::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseReleaseEvent(event);
}

void BaseAllItems::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
  QGraphicsItem::hoverMoveEvent(event);
}

QVariant BaseAllItems::itemChange(QGraphicsItem::GraphicsItemChange change,
                                  const QVariant &value) {
  if (change == QGraphicsItem::ItemSelectedChange) {
    this->setModeOnOffSelection(value.toBool());
  }
  if (change == QGraphicsItem::ItemPositionHasChanged) {
    this->emitRefreshItemProperty();
  }
  if (change == QGraphicsItem::ItemPositionChange && scene()) {
    QPointF newpos = value.toPointF();
    if (QApplication::mouseButtons() == Qt::LeftButton &&
        qobject_cast<SceneView *>(scene())) {
      int gridsize =
          qobject_cast<SceneView *>(scene())->pageItemDesign()->gridSize();
      qreal x = round(newpos.x() / gridsize) * gridsize;
      qreal y = round(newpos.y() / gridsize) * gridsize;
      return QPointF(x, y);
    }
  }
  return QGraphicsItem::itemChange(change, value);
}

void BaseAllItems::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  if (!isSelected()) this->forceThisItemSelected(this);

  this->createContextMenu(event);
}

void BaseAllItems::setModeOnOffSelection(bool b) {
  modeselect = b;
  if (b && !smpat && !smpsk && !smpsb && !smpsknn && !smh_a_k) {
    smpat = new SelectionMarkerHandleBase(this);
    smpat->setCursorType(Qt::SizeVerCursor);
    smpat->setForParentItemType(getItemType());
    updateHandlePos();
    smpat->setSelectionMarkerSize(markerSize);
    smpat->setBrushMarker(QBrush(Qt::green));
    smpat->setPos(0, 0);
    smpat->setVisible(true);

    smpsk = new SelectionMarkerHandleBase(this);
    smpsk->setCursorType(Qt::SizeHorCursor);
    smpsk->setForParentItemType(getItemType());
    updateHandlePos();
    smpsk->setSelectionMarkerSize(markerSize);
    smpsk->setBrushMarker(QBrush(Qt::green));
    smpsk->setPos(0, 0);
    smpsk->setVisible(true);

    smpsb = new SelectionMarkerHandleBase(this);
    smpsb->setCursorType(Qt::SizeVerCursor);
    smpsb->setForParentItemType(getItemType());
    smpsb->setSelectionMarkerSize(markerSize);
    smpsb->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smpsb->setPos(0, 0);
    smpsb->setVisible(true);

    smpsknn = new SelectionMarkerHandleBase(this);
    smpsknn->setCursorType(Qt::SizeHorCursor);
    smpsknn->setForParentItemType(getItemType());
    smpsknn->setSelectionMarkerSize(markerSize);
    smpsknn->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smpsknn->setPos(0, 0);
    smpsknn->setVisible(true);

    smh_a_k = new SelectionMarkerHandleBase(this);
    smh_a_k->setCursorType(Qt::SizeFDiagCursor);
    smh_a_k->setForParentItemType(getItemType());
    smh_a_k->setSelectionMarkerSize(markerSize);
    smh_a_k->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_a_k->setPos(0, 0);
    smh_a_k->setVisible(true);

    smh_a_knn = new SelectionMarkerHandleBase(this);
    smh_a_knn->setCursorType(Qt::SizeBDiagCursor);
    smh_a_knn->setForParentItemType(getItemType());
    smh_a_knn->setSelectionMarkerSize(markerSize);
    smh_a_knn->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_a_knn->setPos(0, 0);
    smh_a_knn->setVisible(true);

    smh_b_knn = new SelectionMarkerHandleBase(this);
    smh_b_knn->setCursorType(Qt::SizeFDiagCursor);
    smh_b_knn->setForParentItemType(getItemType());
    smh_b_knn->setSelectionMarkerSize(markerSize);
    smh_b_knn->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_b_knn->setPos(0, 0);
    smh_b_knn->setVisible(true);

    smh_b_kr = new SelectionMarkerHandleBase(this);
    smh_b_kr->setCursorType(Qt::SizeBDiagCursor);
    smh_b_kr->setForParentItemType(getItemType());
    smh_b_kr->setSelectionMarkerSize(markerSize);
    smh_b_kr->setBrushMarker(QBrush(Qt::green));
    updateHandlePos();
    smh_b_kr->setPos(0, 0);
    smh_b_kr->setVisible(true);
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
      smh_b_kr = nullptr;
    }
  }
}

void BaseAllItems::updateHandlePos() {
  if (!smpat || !smpsk || !smpsb || !smpsknn || !smh_a_k || !smh_a_knn ||
      !smh_b_knn || !smh_b_kr)
    return;

  smpat->setRect(QRectF(localrect.left() + localrect.width() / 2 - markerSize,
                        localrect.top() - markerSize, markerSize * 2,
                        markerSize * 2));
  smpsk->setRect(
      QRectF(localrect.left() - markerSize,
             localrect.bottom() - localrect.height() / 2 - markerSize,
             markerSize * 2, markerSize * 2));
  smpsb->setRect(QRectF(localrect.left() + localrect.width() / 2 - markerSize,
                        localrect.bottom() - markerSize, markerSize * 2,
                        markerSize * 2));
  smpsknn->setRect(
      QRectF(localrect.right() - markerSize,
             localrect.bottom() - localrect.height() / 2 - markerSize,
             markerSize * 2, markerSize * 2));

  smh_a_k->setRect(QRectF(localrect.topLeft().x() - markerSize,
                          localrect.top() - markerSize, markerSize * 2,
                          markerSize * 2));

  smh_a_knn->setRect(QRectF(localrect.topRight().x() - markerSize,
                            localrect.top() - markerSize, markerSize * 2,
                            markerSize * 2));
  smh_b_knn->setRect(QRectF(localrect.bottomRight().x() - markerSize,
                            localrect.bottom() - markerSize, markerSize * 2,
                            markerSize * 2));
  smh_b_kr->setRect(QRectF(localrect.bottomLeft().x() - markerSize,
                           localrect.bottom() - markerSize, markerSize * 2,
                           markerSize * 2));
}