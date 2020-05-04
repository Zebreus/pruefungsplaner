#include "serializabledataobject.h"
#include "group.h"

int SerializableDataObject::idc = 0;

void SerializableDataObject::simpleValuesFromJsonObject(const QJsonObject &content)
{
    auto metaObject = this->metaObject();
    for(QString key: content.keys()){
        const char* keyChars = key.toStdString().c_str();
        //Find index of property
        int propIndex = metaObject->indexOfProperty(keyChars);
        if ( propIndex < 0 ){
            continue;
        }

        QJsonValue jsonValue = content.value(key);
        if (jsonValue.isBool() || jsonValue.isDouble() || jsonValue.isString()) {
            QVariant variant = this->property(keyChars);
            this->setProperty(key.toLatin1().data(), jsonValue.toVariant());
        }

    }
}

QJsonObject SerializableDataObject::recursiveToJsonObject() const
{
    QJsonObject jsonObject;
    auto metaObject = this->metaObject();
    //TODO metaobject->superclass auch für weitere vererbung
    for(int i = metaObject->superClass()->propertyOffset()-1; i < metaObject->propertyCount(); ++i) {
        QMetaProperty prop = metaObject->property(i);
        QVariant variant = property(prop.name());

        if ( variant.canConvert<SerializableDataObject *>() ) {
            SerializableDataObject* sub_obj = variant.value<SerializableDataObject*>();
            jsonObject.insert( prop.name(), sub_obj->toJsonObject() );

        }else if ( variant.canConvert<QList<QVariant>>() ) {
            jsonObject.insert( prop.name(), toJsonArray(variant.value<QList<QVariant>>()) );

        } else{
            jsonObject.insert(prop.name(), QJsonValue::fromVariant(variant));
        }
    }

    return jsonObject;
}

QJsonArray SerializableDataObject::toJsonArray(const QList<SerializableDataObject *> &list) const
{
    if(list.size() > 0){
        if(list.front()->parent() == this){
            return toObjectJsonArray(list);
        }else{
            return toIdJsonArray(list);
        }
    }else{
        return QJsonArray();
    }
}

QJsonArray SerializableDataObject::toJsonArray(const QList<QVariant> &list) const
{
    if(list.size() > 0){
        QVariant firstEntry = list.front();

        //If QList contains SerializableDataObjects
        if(firstEntry.canConvert<SerializableDataObject*>()){
            //TODO Continue looking for a nicer way to convert QList<QVariant> to QList<SerializableDataObject>
            QList<SerializableDataObject*> sdoPointerList;
            for(QVariant variant: list){
                sdoPointerList.push_back(variant.value<SerializableDataObject*>());
            }
            return toJsonArray(sdoPointerList);
        }

        //Use default JsonValue fromVariant if no SerializableDataObject
        //TODO check other types, that cannot be converted directly
        QJsonArray returnArray;
        for(QVariant variant: list){
            returnArray.append(QJsonValue::fromVariant(variant));
        }
        return returnArray;
    }
    return QJsonArray();
}

QJsonArray SerializableDataObject::toObjectJsonArray(const QList<SerializableDataObject *> &list) const
{
    QJsonArray activeGroupArray;
    for(SerializableDataObject* sdo: list){
        activeGroupArray.push_back( sdo->toJsonObject() );
    }
    return activeGroupArray;
}

QJsonArray SerializableDataObject::toIdJsonArray(const QList<SerializableDataObject *> &list) const
{
    QJsonArray activeGroupArray;
    for(SerializableDataObject* sdo: list){
        activeGroupArray.push_back(sdo->id);
    }
    return activeGroupArray;
}

int SerializableDataObject::getId()
{
    return id;
}

SerializableDataObject::SerializableDataObject(QObject *parent, int id) : QObject(parent), id(id)
{
}
