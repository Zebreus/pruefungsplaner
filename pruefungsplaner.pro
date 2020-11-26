QT += quick quickcontrols2 websockets svg

CONFIG += c++2a lrelease embed_translations

include($$PWD/libs/pruefungsplaner-datamodel/pruefungsplaner-datamodel.pri)
include($$PWD/libs/security-provider/client/client.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/client.cpp \
        src/connectionmanager.cpp \
        src/main.cpp \
        src/pruefungsplanermanager.cpp \
        src/schedulerclient.cpp

RESOURCES += res/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

QM_FILES_RESOURCE_PREFIX = /translations

TRANSLATIONS += translations/planner_en.ts
TRANSLATIONS += translations/planner_de.ts

wasm{
#     QMAKE_WASM_PTHREAD_POOL_SIZE = 4
#     QMAKE_WASM_TOTAL_MEMORY = 1GB
}

wasm{
    #target.files += $${TARGET}.js
    #target.files += $${TARGET}.html
    #target.files += qtlogo.svg
    target.files += $${TARGET}.wasm
    target.files += res/web/index.html
    target.files += res/web/favicon.ico
    target.files += res/web/rings.svg
    target.files += qtloader.js
    target.path += /
    target.CONFIG += no_check_exist
}else:unix{
    target.path = /usr/bin
}

!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/client.h \
    src/connectionmanager.h \
    src/pruefungsplanermanager.h \
    src/schedulerclient.h

DISTFILES += \
    res/qml/dummydata/dummysemesters.qml
