#ifndef PROPERTYEDITITEMDELEGATE_H
#define PROPERTYEDITITEMDELEGATE_H

#include <QStyledItemDelegate>
enum class RoleEditorProperty{
    EDITIMAGE_1=Qt::UserRole+1
};
class ImageFileSetPropertyEditor;
class PropertyEditItemDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  explicit PropertyEditItemDelegate(QObject *parent = 0);
  ~PropertyEditItemDelegate();  
     
 protected:
   void destroyEditor(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const Q_DECL_OVERRIDE;
  void setEditorData(QWidget *editor,
                     const QModelIndex &index) const Q_DECL_OVERRIDE;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const Q_DECL_OVERRIDE; 
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const Q_DECL_OVERRIDE;
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const Q_DECL_OVERRIDE;
QSize	sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
 Q_DECL_OVERRIDE;
private Q_SLOTS:
    void commiteditor();  
       
 private:  
    mutable bool need_editor_image1_delete=false;
};

#endif  // PROPERTYEDITITEMDELEGATE_H