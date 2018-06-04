#include "propertyedititemdelegate.h"
#include <imagefilesetpropertyeditor.h>
#include <utiljsonstringproperty.h>
#include <QDebug>
#include <QPainter>
#include <QStandardItem>

PropertyEditItemDelegate::PropertyEditItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)  { 
}

PropertyEditItemDelegate::~PropertyEditItemDelegate() {}
 

void PropertyEditItemDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
//    if (UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(
//            index.data().toByteArray())) {
//        qDebug()<<Q_FUNC_INFO <<"CALLED"; 
//        return;
//    }
      qDebug()<<Q_FUNC_INFO <<"CALLED"; 
    QStyledItemDelegate::destroyEditor (editor,index);
}

QWidget *PropertyEditItemDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  if (UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(
          index.data().toByteArray())) { 
   ImageFileSetPropertyEditor *e = new ImageFileSetPropertyEditor(const_cast<PropertyEditItemDelegate*>(this),parent); 
   // connect(e,SIGNAL(editFinished()),SLOT(commiteditor())); 
    
    e->setGeometry(option.rect);
    return e;
  }
  
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void PropertyEditItemDelegate::setEditorData(QWidget *editor,
                                             const QModelIndex &index) const {
  if (UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(
          index.data().toByteArray())) {
    ImageFileSetPropertyEditor *o =
        qobject_cast<ImageFileSetPropertyEditor *>(editor);
    if (o) {
      o->askUpdateFilePath(index.data().toByteArray());  
      return;
    }
  }
  QStyledItemDelegate::setEditorData(editor, index);
}

void PropertyEditItemDelegate::setModelData(QWidget *editor,
                                            QAbstractItemModel *model,
                                            const QModelIndex &index) const {
  if (UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(
          index.data().toByteArray())) {
    ImageFileSetPropertyEditor *o =
        qobject_cast<ImageFileSetPropertyEditor *>(editor);
    if (o) {
      model->setData(
          index,
          UtilJsonStringProperty::convertPlainImage1FieldToPropertyFormat(
              o->imgChoosen())); 
      return;
    }
  }
  QStyledItemDelegate::setModelData(editor, model, index);
}

void PropertyEditItemDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}

void PropertyEditItemDelegate::paint(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  QImage img;
  if (UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(
          index.data().toByteArray())) { 
    if (option.state & QStyle::State_Selected) {
      painter->fillRect(option.rect, option.palette.highlight());
    } else {
      painter->fillRect(option.rect, option.palette.base());
    } 
    bool okimg=!UtilJsonStringProperty::
            extractPlainPathImage1FieldFromPropertyFormat(
                index.data().toByteArray()).isEmpty () &&
            img.load(UtilJsonStringProperty::
                         extractPlainPathImage1FieldFromPropertyFormat(
                             index.data().toByteArray()));
    if (UtilJsonStringProperty::isExistImage1FieldFromProperty(
            index.data().toByteArray()) && okimg) {  
      qreal marginup=option.rect.height ()/4;
      marginup += marginup/3 ;
      marginup +=option.rect.top ();  
      qreal marginleft= option.rect.left ()+option.rect.width ()/10;
      QRect r(marginleft,marginup,option.rect.width ()/6,option.rect.height ()/2); 
      img=img.scaled(r.width (), r.height ()); 
      QFont font;
      qreal ps=r.height ()/2;
      font.setPointSize (ps);
      QFontMetrics f(font);
      auto elided_text=f.elidedText (UtilJsonStringProperty::extractFileNameFromPathImage1Field(index.data ().toByteArray ()),Qt::ElideRight,
                                     option.rect.width ()-r.width ()-4); 
      QRectF trs(r.right ()+4,r.y (),option.rect.width ()-r.width ()-4,r.height ()  );
      painter->setFont (font);
      painter->drawText (trs,elided_text);
      painter->drawImage(r,img );
    } else { 
        
    } 
    return;
  }
  QStyledItemDelegate::paint(painter, option, index);
}

QSize PropertyEditItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  if (UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(
          index.data().toByteArray())) {
    return QSize(98, 39);
  }
  return QStyledItemDelegate::sizeHint(option, index);
}

void PropertyEditItemDelegate::commiteditor() {
  ImageFileSetPropertyEditor *editor =
      qobject_cast<ImageFileSetPropertyEditor *>(sender()); 
  need_editor_image1_delete=true;
  emit commitData(editor);
  emit closeEditor(editor); 
}
                                     
 
