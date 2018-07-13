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
   void destroyEditor(QWidget *editor, const QModelIndex &index) const override;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor,
                     const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override; 
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;
QSize	sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
 override;
private Q_SLOTS:
    void commiteditor();  
       
 private:  
    mutable bool need_editor_image1_delete=false;
};

#endif  // PROPERTYEDITITEMDELEGATE_H