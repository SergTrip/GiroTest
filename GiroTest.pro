#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T06:48:26
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GiroTest
TEMPLATE = app


SOURCES += main.cpp\
        girotestwidget.cpp \
    girodatareciever.cpp

HEADERS  += girotestwidget.h \
    girodatareciever.h

FORMS    += girotestwidget.ui


# Если операционная система Windows
win32 {
    # Путь к библиотеки libQGLViewer
    LIB_QGLVIEWER_INCLUDEPATH   = D:/Qt/libQGlViewerLibs/libQGLViewer-2.6.1

    # Путь к библиотекам
    LIB_QGLVIEWER_PATH          = D:/Qt/libQGlViewerLibs/libQGLViewer-2.6.1/build

    CONFIG ( release, debug | release   ) {
        message( " Version libQGLViewer-2.6.1 - Release " )

        # Добавить путь к библиотекам
        LIBS    += -L$$LIB_QGLVIEWER_PATH/release/

        LIBS    += -lQGLViewer2

        message( $$LIBS )
    }

    CONFIG ( debug, debug | release   ) {
        message( " Version libQGLViewer-2.6.1 - Release " )

        # Добавить путь к библиотекам
        LIBS    += -L$$LIB_QGLVIEWER_PATH/debug/

        LIBS    += -lQGLViewerd2

        message( $$LIBS )
    }
}

# Если операционная система Linux
unix {
#    # Путь к корню .h файлов
#    OPENCV_INCLUDE_PATH        = ~/Libs/OpenCV/opencv-3.0.0-alpha/include
#    OPENCV_INCLUDE_MODULE_PATH = ~/Libs/OpenCV/opencv-3.0.0-alpha/build/modules

#    # Путь к библиотекам
#    OPENCV_LIBS_PATH           = ~/Libs/OpenCV/opencv-3.0.0-alpha/build/lib

#    CONFIG ( release ) {
#        LIBS    += -L$$OPENCV_LIBS_PATH
#        LIBS    += -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_objdetect
#    }

#    CONFIG ( debug ) {
#        LIBS    += -L$$OPENCV_LIBS_PATH
#        LIBS    += -lopencv_cored -lopencv_imgcodecsd -lopencv_imgprocd -lopencv_objdetectd
#    }
}

INCLUDEPATH += $$LIB_QGLVIEWER_INCLUDEPATH
message( $$LIB_QGLVIEWER_INCLUDEPATH )
