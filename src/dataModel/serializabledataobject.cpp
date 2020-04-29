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
            QJsonArray jsonArray = {};
            QList<QVariant> list = variant.value<QList<QVariant>>();
                for(QVariant listElement : list){
                    if( listElement.canConvert<SerializableDataObject *>() ){
                        jsonArray.append(listElement.value<SerializableDataObject *>()->toJsonObject());
                    }else{
                        jsonArray.append(QJsonValue::fromVariant(listElement));
                    }
                }

            jsonObject.insert( prop.name(), jsonArray );
        } else{
            jsonObject.insert(prop.name(), QJsonValue::fromVariant(variant));
        }
    }

    return jsonObject;
}

QJsonArray SerializableDataObject::toObjectJsonArray(const QList<SerializableDataObject *> list) const
{

}

QJsonArray SerializableDataObject::toIdJsonArray(const QList<SerializableDataObject *> list) const
{

}

int SerializableDataObject::getId()
{
    return id;
}

SerializableDataObject::SerializableDataObject(QObject *parent, int id) : QObject(parent), id(id)
{
}
