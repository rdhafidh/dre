#include "utiljsonstringproperty.h"
#include <QFileInfo>

UtilJsonStringProperty::UtilJsonStringProperty() {}

QByteArray UtilJsonStringProperty::convertPlainImage1FieldToPropertyFormat(
    const QString &path) {
  QJsonObject obj;
  obj["gambar1"] = path;
  QJsonDocument doc(obj);
  return doc.toJson(QJsonDocument::Compact);
}

QString UtilJsonStringProperty::extractPlainPathImage1FieldFromPropertyFormat(
    const QByteArray &buffer) {
  QJsonDocument doc = QJsonDocument::fromJson(buffer);
  if (doc.isNull() || !doc.isObject ()) {
    return QString("");
  }
  auto obj=doc.object ();
  if( obj["gambar1"].isNull() ||
          !obj["gambar1"].isString()
          ){
      return QString("");
  }
  auto str=obj["gambar1"].toString ();
  if(str.isEmpty ()) return QString("");
  
  return obj["gambar1"].toString();
}

bool UtilJsonStringProperty::isExistImage1FieldFromProperty(
    const QByteArray &buffer) {
  QJsonDocument doc = QJsonDocument::fromJson(buffer);
  if (doc.isNull() || !doc.isObject ()) {
    return false;
  }
  auto obj=doc.object ();
  if( obj["gambar1"].isNull() ||
          !obj["gambar1"].isString()
              ){
      return false;
  }
  auto str=obj["gambar1"].toString ();
  if(str.isEmpty ()) return false;
  QFileInfo inf(obj["gambar1"].toString ());
  if(!inf.isFile ()
          || !inf.isReadable ()) return false;
  
  return true;
}

bool UtilJsonStringProperty::isTypeBufferContainImage1FieldFromProperty(const QByteArray &buffer)
{
  //permit empty string tapi tetap harus ada d gambar1 field di json buffer
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    if (doc.isNull() || !doc.isObject ()) {
      return false;
    }
    auto obj=doc.object ();
    if( obj["gambar1"].isNull() ||
            !obj["gambar1"].isString()
              ){
        return false;
    }
    return true;
}

QString UtilJsonStringProperty::extractFileNameFromPathImage1Field(const QByteArray &buffer)
{
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    if (doc.isNull() || !doc.isObject ()) {
      return QString("");
    }
    auto obj=doc.object ();
    if( obj["gambar1"].isNull() ||
            !obj["gambar1"].isString()
                ){
        return QString("");
    }
    auto str=obj["gambar1"].toString ();
    if(str.isEmpty ()) return QString("");
    QFileInfo inf(obj["gambar1"].toString ());
    
    return inf.fileName ();
}
