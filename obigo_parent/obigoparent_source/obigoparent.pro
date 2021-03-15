TEMPLATE = app
TARGET = obigo_parent

QT += quick
CONFIG += c++14 link_pkgconfig

contains(DEFINES, X86_64) {
    INCLUDEPATH += $$JSONPARSERPATH
    LIBS += -L$$CCOS_LIB_DIR -lhmiappcommon
} else {
    PKGCONFIG += hmiappcommon
    PKGCONFIG += wayland-client
    PKGCONFIG += CommonAPI
    PKGCONFIG += CommonAPI-DBus
    PKGCONFIG += dbus-1
}

CONFIG(debug, debug|release) {
    message(debug)
} else {
    message(release)
    CONFIG += qtquickcompiler
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERPATH = $$PWD/include
SOURCEPATH = $$PWD/src

INCLUDEPATH += \
    $$HEADERPATH \
    $$PWD/../../CommonAPI/src-gen \
    $$(SDKTARGETSYSROOT)/usr/include/CommonAPI-3.1 \
    $$(SDKTARGETSYSROOT)/usr/include/dbus-1.0 \
    $$(SDKTARGETSYSROOT)/usr/lib64/dbus-1.0/include \


SOURCES += \
    $$SOURCEPATH/main.cpp \
    $$SOURCEPATH/LogContext.cpp \
    $$SOURCEPATH/ExampleAppService.cpp \
    $$SOURCEPATH/window/ExampleFrontWindow.cpp \
    $$SOURCEPATH/scene/SceneExampleMain.cpp \
    $$SOURCEPATH/obigo/ObigoStub.cpp \
    $$SOURCEPATH/obigo/ObigoTestStubImpl.cpp \
    $$SOURCEPATH/obigo/SubSurfaceManager.cpp \
    $$PWD/../../CommonAPI/src-gen/v1/commonapi/examples/ObigoTestStubDefault.cpp \
    $$PWD/../../CommonAPI/src-gen/v1/commonapi/examples/ObigoTestDBusStubAdapter.cpp \
    $$PWD/../../CommonAPI/src-gen/v1/commonapi/examples/ObigoTestDBusDeployment.cpp \


HEADERS += \
    $$HEADERPATH/LogContext.h \
    $$HEADERPATH/ExampleAppService.h \
    $$HEADERPATH/window/ExampleFrontWindow.h \
    $$HEADERPATH/scene/SceneExampleMain.h \
    $$HEADERPATH/obigo/ObigoStub.h \
    $$HEADERPATH/obigo/ObigoTestStubImpl.h \
    $$HEADERPATH/obigo/SubSurfaceManager.h \

RESOURCES += \
    qml/window/window.qrc \
    qml/scene/scene.qrc \
    qml/form/form.qrc \

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    CONFIG += file_copies
    COPIES += app_info_json

    app_info_json.files = $$files(appinfo.json)
    app_info_json.path = $$OUT_PWD
    app_info_json.base = $$_PRO_FILE_PWD_
}

target.path = $$CCOS_APP_HMI_DIR/$$TARGET

#message($${target.path})

json.files = $$files(appinfo.json)
#json.files += $$files(theme.json)
json.path = $$CCOS_APP_HMI_DIR/$$TARGET

INSTALLS += target json
