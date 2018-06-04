#ifndef UTILJSONSTRINGPROPERTY_H
#define UTILJSONSTRINGPROPERTY_H

#include <QJsonDocument>
#include <QJsonObject>

class UtilJsonStringProperty
{
public:
    UtilJsonStringProperty();
    static QByteArray convertPlainImage1FieldToPropertyFormat(const QString &path);
    static QString extractPlainPathImage1FieldFromPropertyFormat(const QByteArray &buffer);
    static bool isExistImage1FieldFromProperty(const QByteArray &buffer);
    static bool isTypeBufferContainImage1FieldFromProperty(const QByteArray &buffer);
    static QString extractFileNameFromPathImage1Field(const QByteArray &buffer);
    
};

#endif // UTILJSONSTRINGPROPERTY_H