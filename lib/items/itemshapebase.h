#ifndef ITEMSHAPEBASE_H
#define ITEMSHAPEBASE_H
#include <QObject>
#include <QPainter> 
#include <constvalue.h> 

class BaseAllItems; 
class  ItemShapeBase : public QObject {
  Q_OBJECT
    Q_PROPERTY(BorderLineFlags borderLine READ borderLineFlags WRITE
                   setBorderLineFlags DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(qreal borderLineWidth READ borderLineWidth WRITE setBorderLineWidth DESIGNABLE true  )
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor )
    Q_PROPERTY(bool visibleItem READ visibleItem WRITE setVisibleItem ) 
    Q_PROPERTY(qreal lineWidth READ getLineWidth WRITE setLineWidth NOTIFY
                   lineWidthChanged)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY
                   lineColorChanged) 
    Q_PROPERTY(QColor fillColorShape READ getFillColorShape WRITE
                   setFillColorShape NOTIFY fillColorShapeChanged)
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
  
  void setItemType(const ItemConst::Tipe &tipe);
  ItemConst::Tipe getItemType() const;
  
  bool isInUndoStack()const;
  void setInUndoStack(bool e);
  
  void setLineWidth(qreal w);
  qreal getLineWidth() const;

  void setLineColor(const QColor &color);
  QColor getLineColor() const;

  void setFillColorShape(const QColor &color);
  QColor getFillColorShape() const;
 
  
Q_SIGNALS:
  void askUpdate(); 
  void rectChanged(const QRectF & r); 
  
  void lineWidthChanged(qreal w);
  void lineColorChanged(const QColor &warna);
  void fillColorShapeChanged(const QColor &warna);
 
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
  
  QColor m_lineColor;
  qreal m_lineWidth;
  QColor m_fillColor;
};

#endif  // ITEMSHAPEBASE_H
