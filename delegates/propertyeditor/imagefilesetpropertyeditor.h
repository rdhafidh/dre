#ifndef IMAGEFILESETPROPERTYEDITOR_H
#define IMAGEFILESETPROPERTYEDITOR_H

#include <QList>
#include <QPair>
#include <QWidget>

namespace Ui {
class ImageFileSetPropertyEditor;
}
class PropertyEditItemDelegate;

class ImageFileSetPropertyEditor : public QWidget {
  Q_OBJECT

 public:
  explicit ImageFileSetPropertyEditor(PropertyEditItemDelegate *dlg,
                                      QWidget *parent);
  ~ImageFileSetPropertyEditor();
  void askUpdateFilePath(const QByteArray &buffer);
  QString imgChoosen() const;
  void setDelegate(PropertyEditItemDelegate *dlg);

 Q_SIGNALS:
  void emitImgChoosen(const QString &mfile);
  void editFinished();
 
 public Q_SLOTS:
  void openFileDialogImageDone(const QString &imagepath);

 private slots:
  void on_toolButton_pilih_file_clicked();

 private:
  bool isimgFromBuffer(const QByteArray &buffer);
  void prepareRelease();

  QString choosenimg;
  Ui::ImageFileSetPropertyEditor *ui;
  QString lastdirimg;
  PropertyEditItemDelegate *delegate;
};
#endif  // IMAGEFILESETPROPERTYEDITOR_H
