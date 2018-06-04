#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <baseallitems.h>
#include <QGraphicsObject>

class TextItem : public BaseAllItems {
  Q_OBJECT
    Q_PROPERTY(QString teks READ teks WRITE setTeks NOTIFY teksChanged)
    Q_PROPERTY(qreal textLineHeight READ textLineHeight WRITE setTextLineHeight NOTIFY textLineHeightChanged)
 public:
  explicit TextItem(QGraphicsItem *parent = 0);
  ~TextItem();  
  
  void setTextLineHeight(qreal n);
  qreal textLineHeight();
    
  void setMarginSize(int n);
  int marginSize() const;

  void setTeksIndentWidth(qreal n);
  qreal teksIndentWidth() const;

  void setTeks(const QString &str);
  QString teks() const;
  
  typedef QSharedPointer<QTextDocument> Docptr;

 Q_SIGNALS:
  void textLineHeightChanged(qreal n);
  void marginChanged(int n);
  void teksIndentWidthChanged(qreal n);
  void teksChanged(const QString &str); 

 protected:  
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) Q_DECL_OVERRIDE;
 void createContextMenu (QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;
 private:
  Docptr teksData();
  int marginsize = 4;
  qreal textindentsize = 0   ; 
  qreal textlineheight=1;
  QString m_teks;
};

#endif  // TEXTITEM_H