#include "textitem.h"
#include <QAbstractTextDocumentLayout>
#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <mainwindow.h>
#include <sceneview.h>
#include <undocommand.h>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QMetaObject>
#include <QMetaProperty>
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextCursor>

TextItem::TextItem(QGraphicsItem *parent) : BaseAllItems(parent) {
  setItemType(ItemConst::Tipe::TEKS);
  setTeks(
      tr("kata kunci kata kunci  kata kunci kata kunci kata kunci kata kunci "
         "kata kunci kata kunci kata kunci kata kunci"));
}

TextItem::~TextItem() {}

void TextItem::setTextLineHeight(qreal n) {
  if (textlineheight == n) return;

  textlineheight = n;
  this->textLineHeightChanged(n);
  update();
}

qreal TextItem::textLineHeight() { return textlineheight; }

void TextItem::setMarginSize(int n) {
  if (n == marginsize) return;

  marginsize = n;
  this->marginChanged(marginsize);
  update(boundingRect());
}

int TextItem::marginSize() const { return marginsize; }

void TextItem::setTeksIndentWidth(qreal n) {
  if (n == textindentsize) return;

  textindentsize = n;
  this->teksIndentWidthChanged(n);
  update(boundingRect());
}

qreal TextItem::teksIndentWidth() const { return textindentsize; }

void TextItem::setTeks(const QString &str) {
  if (m_teks == str) return;

  m_teks = str;
  this->teksChanged(str);
  update(boundingRect());
}

QString TextItem::teks() const { return m_teks; }

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->save();
  if (!painter->clipRegion().isEmpty()) {
    QRegion clipReg = painter->clipRegion().xored(
        painter->clipRegion().subtracted(boundingRect().toRect()));
    painter->setClipRegion(clipReg);
  } else {
    painter->setClipRect(boundingRect());
  }
  auto doc = teksData();
  painter->translate(this->rect().topLeft().x(), this->rect().top());
  QAbstractTextDocumentLayout::PaintContext ctx;
  doc->documentLayout()->draw(painter, ctx);
  painter->restore();
  BaseAllItems::paint(painter, option, widget);
}

void TextItem::createContextMenu(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  auto ondelete = [this]() {
    SceneView *scn = qobject_cast<SceneView *>(scene());
    if (scn != nullptr) {
      scn->undostack()->push(new XCommands::DeleteItemCommand(this));
    }
  };
  QAction *cpAction = menu.addAction("Copy");
  QAction *pasteAction = menu.addAction("Paste");
  QAction *delAction = menu.addAction("Delete");
  QAction *dumpPropertiAction = menu.addAction("Dump Properti");
  QAction *selectedAction = menu.exec(event->screenPos());
  if (selectedAction == cpAction) {
  } else if (selectedAction == pasteAction) {
  } else if (selectedAction == delAction) {
    QMessageBox box;
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setText(
        tr("Apakah anda yakin akan menghapus item dengan nama obyek %1 ?")
            .arg(objectName()));
    box.setDefaultButton(QMessageBox::No);
    int ret = box.exec();
    switch (ret) {
      case QMessageBox::Yes:
        ondelete();
        break;
      default:
        break;
    }
  } else if (selectedAction == dumpPropertiAction) {
    this->dumpPropertiInfo();
  }
}

TextItem::Docptr TextItem::teksData() {
  Docptr text(new QTextDocument);
  // TODO add default textcursor

  text->setHtml(m_teks);
  text->setDocumentMargin(marginsize);
  text->setPageSize(QSizeF(this->rect().width(), this->rect().height()));
  text->setTextWidth(this->rect().width());
  for (QTextBlock block = text->begin(); block.isValid();
       block = block.next()) {
    QTextCursor tc = QTextCursor(block);
    QTextBlockFormat fmt = block.blockFormat();
    fmt.setTextIndent(textindentsize);
    fmt.setLineHeight(textlineheight, QTextBlockFormat::LineDistanceHeight);
    tc.setBlockFormat(fmt);
  }
  return text;
}
