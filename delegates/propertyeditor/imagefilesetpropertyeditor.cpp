#include "imagefilesetpropertyeditor.h"
#include "ui_imagefilesetpropertyeditor.h"

#include <propertyedititemdelegate.h>
#include <utiljsonstringproperty.h>
#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <QFileDialog>
#include <QImage>
#include <QThread>
#include <QTimer>

ImageFileSetPropertyEditor::ImageFileSetPropertyEditor(
    PropertyEditItemDelegate *dlg, QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageFileSetPropertyEditor), delegate(dlg) {
  ui->setupUi(this);
  lastdirimg.clear();
  choosenimg.clear();
  setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored));
  setFocusProxy(ui->toolButton_pilih_file);
}

ImageFileSetPropertyEditor::~ImageFileSetPropertyEditor() {
#ifdef DEBUGGING_ENABLED
  qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
#endif
  delete ui;
}

void ImageFileSetPropertyEditor::askUpdateFilePath(const QByteArray &buffer) {
  if (!isimgFromBuffer(buffer)) return;

  auto up = choosenimg =
      UtilJsonStringProperty::extractPlainPathImage1FieldFromPropertyFormat(
          buffer);
#ifdef DEBUGGING_ENABLED
  qDebug() << Q_FUNC_INFO << __LINE__;
#endif
  ui->lineEdit_file_path->setText(up);
}

QString ImageFileSetPropertyEditor::imgChoosen() const {
  return ui->lineEdit_file_path->text();
}

void ImageFileSetPropertyEditor::setDelegate(PropertyEditItemDelegate *dlg) {
  delegate = dlg;
}

void ImageFileSetPropertyEditor::openFileDialogImageDone(
    const QString &imagepath) {
  if (imagepath.isEmpty()) {
    lastdirimg.clear();
    prepareRelease();
    return;
  }

  auto buff = UtilJsonStringProperty::convertPlainImage1FieldToPropertyFormat(
      imagepath);
  if (!isimgFromBuffer(buff)) {
    prepareRelease();
    return;
  }
#ifdef DEBUGGING_ENABLED
  qDebug() << "choosen imagepath" << imagepath;

  qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
#endif
  ui->lineEdit_file_path->setText(imagepath);
  prepareRelease();
}

void ImageFileSetPropertyEditor::on_toolButton_pilih_file_clicked() {
  if (lastdirimg.isEmpty()) {
    lastdirimg = ".";
  }
  auto mfile =
      QFileDialog::getOpenFileName(this, tr("Pilih Gambar"), lastdirimg,
                                   tr("File Gambar (*.jpg *.jpeg *.png)"));
  this->openFileDialogImageDone(mfile);
}

bool ImageFileSetPropertyEditor::isimgFromBuffer(const QByteArray &buffer) {
  if (!UtilJsonStringProperty::isExistImage1FieldFromProperty(buffer))
    return false;

  QImage img;

  auto pimg =
      UtilJsonStringProperty::extractPlainPathImage1FieldFromPropertyFormat(
          buffer);
  bool e = img.load(pimg);
  QFileInfo inf;
  QString str;
  if (e) {
    str = UtilJsonStringProperty::extractPlainPathImage1FieldFromPropertyFormat(
        buffer);
    inf.setFile(str);
    lastdirimg = inf.absolutePath();
  }
  return e;
}

void ImageFileSetPropertyEditor::prepareRelease() {
  delegate->commitData(this);
  delegate->closeEditor(this);
}
