#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <baseallitems.h>
#include <QImage>

class ImageItem : public BaseAllItems {
  Q_OBJECT
  Q_PROPERTY(QString imageFile READ imageFile WRITE setImageFile NOTIFY
                 imageFileChanged)

 public:
  explicit ImageItem(QGraphicsItem *parent = 0);
  ~ImageItem();
  void setImageFile(const QString &image);
  QString imageFile() const;

  void setScaleImgValue(qreal scale);
  qreal scaleImgValue() const;

 Q_SIGNALS:
  void imageFileChanged(const QString &file);
  void emitImageFileLoadFailed(const QString &file);
  void emitImageFileLoadTooBig(const QString &file);
  void emitScaleImgChanged(qreal d);

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void createContextMenu(QGraphicsSceneContextMenuEvent *event) override;

 private:
  qreal scalevalue = 1.0;
  QString imagefile;
  QImage imgdata;
  qint64 maxsizefile;
};

#endif  // IMAGEITEM_H