QT += quick quickcontrols2 websockets

CONFIG += c++11 debug

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
        client.cpp \
        main.cpp \
        pruefungsplanermanager.cpp \
        src/dataModel/day.cpp \
        src/dataModel/group.cpp \
        src/dataModel/module.cpp \
        src/dataModel/plan.cpp \
        src/dataModel/semester.cpp \
        src/dataModel/serializabledataobject.cpp \
        src/dataModel/timeslot.cpp \
        src/dataModel/week.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

QT_QUICK_CONTROLS_STYLE=fusion

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ExamListItem.qml \
    ExamListItemForm.ui.qml \
    NewGroupEditor.qml \
    NewGroupEditorForm.ui.qml \
    RemovableLabel.qml \
    RemovableLabelForm.ui.qml \
    ResultViewModuleItem.qml \
    ResultViewModuleItemForm.ui.qml \
    dummydata/availabilityModel.qml \
    dummydata/availabilityModel2.qml \
    dummydata/context/NOTAvailabilityEditor.qml \
    dummydata/context/NOTAvailabilityEditorForm.ui.qml \
    dummydata/context/test \
    dummydata/test \
    qtquickcontrols2.conf \
    res/fbi.png \
    res/hda.png

HEADERS += \
    client.h \
    pruefungsplanermanager.h \
    src/dataModel/day.h \
    src/dataModel/group.h \
    src/dataModel/module.h \
    src/dataModel/plan.h \
    src/dataModel/semester.h \
    src/dataModel/serializabledataobject.h \
    src/dataModel/timeslot.h \
    src/dataModel/week.h
