#include "imageitem.h"
#include <QFileInfo>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

ImageItem::ImageItem(QGraphicsItem *parent) : BaseAllItems(parent) {
  // 2 MB
  maxsizefile = 1024 * 1024 * 2;
  imgdata = QImage();
  setItemType(ItemConst::Tipe::GAMBAR);
}

ImageItem::~ImageItem() {}

void ImageItem::setImageFile(const QString &image) {
  QFile fn(image);
  if (!fn.open(QIODevice::ReadOnly)) {
    this->emitImageFileLoadFailed(image);
    return;
  }
  if (fn.size() > maxsizefile) {
    this->emitImageFileLoadTooBig(image);
    fn.close();
    return;
  }
  fn.close();
  if (!imgdata.load(image) || imgdata.isNull()) {
    this->emitImageFileLoadFailed(image);
    return;
  }
  imagefile = image;
  this->imageFileChanged(imagefile);
}

QString ImageItem::imageFile() const { return imagefile; }

void ImageItem::setScaleImgValue(qreal scale) {
  if (scale < 0.1) {
    return;
  }
  scalevalue = scale;
  this->emitScaleImgChanged(scalevalue);
}

qreal ImageItem::scaleImgValue() const { return scalevalue; }

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  painter->save();
  //     painter->translate(rect().center());
  //     painter->scale(m_scale, m_scale);
  //     painter->translate(m_delta);
  //     painter->drawPixmap(m_rect.topLeft(), m_pixmap);
  if (imgdata.isNull()) {
    QFont font;
    font.setPointSize((this->rect().height() / 10) +
                      (this->rect().width() / 20));
    painter->setFont(font);
    painter->drawText(this->rect(), Qt::AlignCenter, tr("No Image"));
    painter->setOpacity(0.2);
    painter->fillRect(this->rect(), QBrush(QPixmap(":/image/empty_kotak.png")));

  } else {
    painter->setOpacity(1.0);
    auto img = imgdata.scaled(this->rect().width(), this->rect().height(),
                              Qt::KeepAspectRatio, Qt::FastTransformation);
    painter->drawImage(this->rect().toRect(), img);
  }
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

void ImageItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  QAction *cpAction = menu.addAction("Copy");
  QAction *pasteAction = menu.addAction("Paste");
  QAction *delAction = menu.addAction("Delete");
  QAction *dumpPropertiAction = menu.addAction("Dump Properti");
  QAction *selectedAction = menu.exec(event->screenPos());
  if (selectedAction == cpAction) {
  } else if (selectedAction == pasteAction) {
  } else if (selectedAction == delAction) {
  } else if (selectedAction == dumpPropertiAction) {
    this->dumpPropertiInfo();
  }
}
