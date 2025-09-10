#-------------------------------------------------
#
# Project created by QtCreator 2025-09-10T16:07:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plugin_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        appcontext.h \
        iplugin.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# 根据构建模式自动切换输出路径
CONFIG(debug, debug|release) {
    # Debug 模式：动态库输出到主项目的 libs/debug 目录
    DESTDIR = $$PWD/../bin/debug
} else {
    # Release 模式：动态库输出到主项目的 libs/release 目录
    DESTDIR = $$PWD/../bin/release
}

message("动态库输出目录: $$DESTDIR")  # 编译时显示当前输出目录，方便验证

# 4. 区分 Debug 和 Release 模式，指定中间文件目录
CONFIG(debug, debug|release) {
    # Debug 模式中间文件目录（带debug标识）
    MOC_DIR = $$PWD/build/debug/moc      # moc 生成文件路径
    OBJECTS_DIR = $$PWD/build/debug/obj  # 目标文件（.obj）路径
    RCC_DIR = $$PWD/build/debug/rcc      # 资源文件编译路径
} else {
    # Release 模式中间文件目录（带release标识）
    MOC_DIR = $$PWD/build/release/moc    # moc 生成文件路径
    OBJECTS_DIR = $$PWD/build/release/obj# 目标文件（.obj）路径
    RCC_DIR = $$PWD/build/release/rcc    # 资源文件编译路径
}
message("中间文件根目录: $$PWD/build")  # 显示中间文件根目录
