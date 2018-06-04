#include "itemshapebase.h"
#include <QDebug>
#ifdef BUILD_GRAPHICSVIEW
#include <QPainterPath>
#else
#define BALUTSTR(d) std::string(d)

#endif
ItemShapeBase::ItemShapeBase(QObject *parent) : QObject(parent) {
    m_borderflag=BORDER_SEMUA;
    m_borderwidth=1;
    localrect=QRectF(0,0,0,0);
    m_bordercolor=QColor(Qt::black);
    m_visible=true;
    m_tipeitem=ItemConst::Tipe::KOTAK;
    m_itemstr="";
    m_funcdef="";
}

ItemShapeBase::~ItemShapeBase() {}

ItemShapeBase::BorderLineFlags ItemShapeBase::borderLineFlags() const {
  return m_borderflag;
}

void ItemShapeBase::setBorderLineFlags(
    const ItemShapeBase::BorderLineFlags &b) {
  if (m_borderflag == b) return;

  m_borderflag = b;
  this->askUpdate();
}

qreal ItemShapeBase::borderLineWidth() const { return m_borderwidth; }

void ItemShapeBase::setBorderLineWidth(qreal n) {
  if (m_borderwidth == n) return;

  m_borderwidth = n;
  this->askUpdate();
}

QColor ItemShapeBase::borderColor() const { return m_bordercolor; }

void ItemShapeBase::setBorderColor(const QColor &col) {
  if (m_bordercolor == col) return;

  m_bordercolor = col;
  this->askUpdate();
}

bool ItemShapeBase::visibleItem() const { return m_visible; }

void ItemShapeBase::setVisibleItem(bool n) {
  if (m_visible == n) return;

  m_visible = n;
  this->askUpdate();
}

void ItemShapeBase::setRect(const QRectF &r) {
  if (localrect == r) return;

  localrect = r;
  this->rectChanged (localrect);
  this->askUpdate();
}

QRectF ItemShapeBase::rect() const { return localrect; }

QString ItemShapeBase::generateSceneItem() const
{
    return m_itemstr;
}

QString ItemShapeBase::generateFuncDefs() const
{
    return m_funcdef;
}

void ItemShapeBase::setItemType(const ItemConst::Tipe &tipe) {
  if (m_tipeitem == tipe) return;

  m_tipeitem = tipe; 
}

ItemConst::Tipe ItemShapeBase::getItemType() const { return m_tipeitem; }

bool ItemShapeBase::isInUndoStack() const
{
    return m_isindostack;
}

void ItemShapeBase::setInUndoStack(bool e)
{
    m_isindostack=e;
}

void ItemShapeBase::paintShape(QPainter *painter) {
#ifdef BUILD_GRAPHICSVIEW
  if (painter != nullptr && m_visible) { 
    drawSingleItemBorder(painter); 
  }
#else
  Q_UNUSED(painter)
  if(!m_visible) return;
  
  this->m_itemstr.append("\n");
  auto r = R"( drawBorder(ctx, %1,%2,%3,%4); )";
  this->m_itemstr.append(QString::fromStdString(r)
                             .arg(this->rect().x())
                             .arg(this->rect().y())
                             .arg(this->rect().width())
                             .arg(this->rect().height()));
  
  drawSingleItemBorder (nullptr);
   
#endif
}

void ItemShapeBase::createContextMenu(QGraphicsSceneContextMenuEvent *event)
{
    Q_UNUSED(event)
}

void ItemShapeBase::drawSingleItemBorder(QPainter *painter) {
#ifdef BUILD_GRAPHICSVIEW
  if (this->m_borderflag & BORDER_ATAS)
    drawSingleItemTopLine(painter, this->rect());
  if (this->m_borderflag & BORDER_KANAN)
    drawSingleItemRightLine(painter, this->rect());
  if (this->m_borderflag & BORDER_KIRI)
    drawSingleItemLeftLine(painter, this->rect());
  if (this->m_borderflag & BORDER_BAWAH)
    drawSingleItemBotomLine(painter, this->rect());
#else
  Q_UNUSED(painter)
  this->m_funcdef.append("\n");
  auto r = BALUTSTR(R"(
             function drawBorder(ctx, xPos, yPos, width, height) { )");
  if (this->m_borderflag & BORDER_ATAS)
    r += BALUTSTR(R"( \n drawtopline(ctx, xPos, yPos, width, height); )");
  if (this->m_borderflag & BORDER_BAWAH)
    r += BALUTSTR(R"( \n  drawbottom(ctx, xPos, yPos, width, height); )");
  if (this->m_borderflag & BORDER_KANAN)
    r += BALUTSTR(R"( \n  drawright(ctx, xPos, yPos, width, height); )");
  if (this->m_borderflag & BORDER_KIRI)
    r += BALUTSTR(R"( \n  drawleft(ctx, xPos, yPos, width, height); )");

  r += BALUTSTR("\n }");
  this->m_funcdef.append(QString::fromStdString(r));
  if (this->m_borderflag & BORDER_ATAS)
    drawSingleItemTopLine(nullptr, this->rect());
  if (this->m_borderflag & BORDER_KANAN)
    drawSingleItemRightLine(nullptr, this->rect());
  if (this->m_borderflag & BORDER_KIRI)
    drawSingleItemLeftLine(nullptr, this->rect());
  if (this->m_borderflag & BORDER_BAWAH)
    drawSingleItemBotomLine(nullptr, this->rect());
#endif
}

void ItemShapeBase::drawSingleItemTopLine(QPainter *painter, QRectF rect) {
#ifdef BUILD_GRAPHICSVIEW
  QPainterPath path;
    path.moveTo (rect.topLeft ());
    path.lineTo (rect.topRight ());
    painter->setPen (borderPen ());
    painter->drawPath (path);
#else
  Q_UNUSED(painter)
  Q_UNUSED(rect)
  auto r = BALUTSTR(R"(
            function drawtopline(ctx, x, y, w, h) {
                        ctx.beginPath();
                        ctx.moveTo(x, y);
                        ctx.lineTo(w, y);
                        ctx.strokeStyle = '%1';
                        ctx.lineWidth = %2;
                        ctx.stroke();
                    }
            )");
  this->m_funcdef.append("\n");
  this->m_funcdef.append(QString::fromStdString(r)
                             .arg(this->m_bordercolor.name(QColor::HexRgb))
                             .arg(this->m_borderwidth));

#endif
}

void ItemShapeBase::drawSingleItemBotomLine(QPainter *painter, QRectF rect) {
#ifdef BUILD_GRAPHICSVIEW
  QPainterPath path;
      path.moveTo (rect.bottomLeft ());
      path.lineTo (rect.bottomRight ());
      painter->setPen (borderPen ());
      painter->drawPath (path);
#else
  Q_UNUSED(painter)
  Q_UNUSED(rect)
  auto r = R"(
             function drawbottom(ctx, x, y, w, h) {
                         ctx.beginPath();
                         ctx.moveTo(x, h);
                         ctx.lineTo(w, h);
                         ctx.strokeStyle = '%1';
                         ctx.lineWidth = %2;
                         ctx.stroke();
                     }
              )";
  this->m_funcdef.append("\n");
  this->m_funcdef.append(QString::fromStdString(r)
                             .arg(this->m_bordercolor.name(QColor::HexRgb))
                             .arg(this->m_borderwidth));
#endif
}

void ItemShapeBase::drawSingleItemRightLine(QPainter *painter, QRectF rect) {
#ifdef BUILD_GRAPHICSVIEW
  QPainterPath path;
      path.moveTo (rect.topRight ());
      path.lineTo (rect.bottomRight ());
      painter->setPen (borderPen ());
      painter->drawPath (path);
  //    qDebug()<<"base draw height"<<rect.height ();
#else
  Q_UNUSED(painter)
  Q_UNUSED(rect)
  auto r = R"(
             function drawright(ctx, x, y, w, h) {
                         ctx.beginPath();
                         ctx.moveTo(w, y);
                         ctx.lineTo(w, h);
                         ctx.strokeStyle = '%1';
                         ctx.lineWidth = %2;
                         ctx.stroke();
                     }
              )";
  this->m_funcdef.append("\n");
  this->m_funcdef.append(QString::fromStdString(r)
                             .arg(this->m_bordercolor.name(QColor::HexRgb))
                             .arg(this->m_borderwidth));
#endif
}

void ItemShapeBase::drawSingleItemLeftLine(QPainter *painter, QRectF rect) {
#ifdef BUILD_GRAPHICSVIEW
  QPainterPath path;
      path.moveTo (rect.topLeft ());
      path.lineTo (rect.bottomLeft ());
      painter->setPen (borderPen ());
      painter->drawPath (path);
#else
  Q_UNUSED(painter)
  Q_UNUSED(rect)
  auto r = R"(
             function drawleft(ctx, x, y, w, h) {
                         ctx.beginPath();
                         ctx.moveTo(x, y);
                         ctx.lineTo(x, h);
                         ctx.strokeStyle = '%1';
                         ctx.lineWidth = %2;
                         ctx.stroke();
                     }
              )";
  this->m_funcdef.append("\n");
  this->m_funcdef.append(QString::fromStdString(r)
                             .arg(this->m_bordercolor.name(QColor::HexRgb))
                             .arg(this->m_borderwidth));
#endif
}

QPen ItemShapeBase::borderPen() const {
  QPen pen;
  pen.setBrush(QBrush(m_bordercolor));
  pen.setWidth(m_borderwidth);
  pen.setStyle(Qt::SolidLine);
  return pen;
}

ItemShapeChangeValue makeItemShapeChangeDecisionValue(
    const ItemShapeChangeDecision &decision,
    QQuickItem::ItemChangeData *fromqml, const QVariant &fromgraphicsitem) {
  ItemShapeChangeValue value;
  value.decison_data = decision;
  value.data_qml_change = fromqml;
  value.data_graphicsitem_change = fromgraphicsitem;
  return value;
}
