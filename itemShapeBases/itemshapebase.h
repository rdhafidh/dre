#ifndef ITEMSHAPEBASE_H
#define ITEMSHAPEBASE_H
#include <QObject>
#include <QPainter> 
#include <constvalue.h>
namespace QQuickItem {
class ItemChangeData;
}
enum class ItemShapeChangeDecision {
  ITEM_DATA_IS_UNDEFINED = 2,
  ITEM_DATA_IS_FROM_QML = 4,
  ITEM_DATA_IS_FROM_GRAPHICSITEM=8
};
struct ItemShapeChangeValue {
  QQuickItem::ItemChangeData *data_qml_change;
  QVariant data_graphicsitem_change;
  ItemShapeChangeDecision decison_data;
};
ItemShapeChangeValue makeItemShapeChangeDecisionValue(
    const ItemShapeChangeDecision &decision,
    QQuickItem::ItemChangeData *fromqml, const QVariant &fromgraphicsitem); 
class BaseAllItems; 
class  ItemShapeBase : public QObject {
  Q_OBJECT
    Q_PROPERTY(BorderLineFlags borderLine READ borderLineFlags WRITE
                   setBorderLineFlags DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(qreal borderLineWidth READ borderLineWidth WRITE setBorderLineWidth DESIGNABLE true  )
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor )
    Q_PROPERTY(bool visibleItem READ visibleItem WRITE setVisibleItem ) 
 public: 
    friend class BaseAllItems; 
  explicit ItemShapeBase(QObject *parent = 0);
  ~ItemShapeBase();
    enum BorderLineTypeFlag {
      BORDER_KOSONG = 2,
      BORDER_ATAS =4 ,
      BORDER_BAWAH=8 ,
      BORDER_KANAN =16,
      BORDER_KIRI  =32,
      BORDER_SEMUA=  BORDER_ATAS|BORDER_BAWAH|BORDER_KANAN|BORDER_KIRI
    };
    Q_DECLARE_FLAGS(BorderLineFlags, BorderLineTypeFlag)
    Q_FLAG(BorderLineFlags)
    
   ItemShapeBase::BorderLineFlags borderLineFlags()const;
   void setBorderLineFlags(const ItemShapeBase::BorderLineFlags & b);
   
   qreal borderLineWidth() const;
   void setBorderLineWidth(qreal n);
   
   QColor borderColor()const;
   void setBorderColor(const QColor & col);
   
   bool visibleItem()const;
   void setVisibleItem(bool n);
   
  void setRect(const QRectF &r);
  QRectF rect() const;
  /*
   * Generated qml api dari html5 canvas api
   * */
  QString generateSceneItem() const;
  QString generateFuncDefs()const;
  void setItemType(const ItemConst::Tipe &tipe);
  ItemConst::Tipe getItemType() const;
  
  bool isInUndoStack()const;
  void setInUndoStack(bool e);
  
Q_SIGNALS:
  void askUpdate(); 
  void rectChanged(const QRectF & r); 
 protected:
  /*
   * ketika paint
   * */
  virtual void paintShape(QPainter *painter) ;  
  virtual void createContextMenu(QGraphicsSceneContextMenuEvent *event) ;
  
 private: 
  void drawSingleItemBorder(QPainter *painter);
  void drawSingleItemTopLine(QPainter *painter, QRectF rect);
  void drawSingleItemBotomLine(QPainter *painter, QRectF rect);
  void drawSingleItemRightLine(QPainter *painter, QRectF rect);
  void drawSingleItemLeftLine(QPainter *painter, QRectF rect);
  QPen borderPen()const;
  bool m_isindostack;
  ItemShapeBase::BorderLineFlags m_borderflag;
  QRectF localrect;
  qreal m_borderwidth;
  QColor m_bordercolor;
  bool m_visible;
  ItemConst::Tipe m_tipeitem;
  QString m_itemstr;
  QString m_funcdef;
};

#endif  // ITEMSHAPEBASE_H
