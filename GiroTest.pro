#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T06:48:26
#
#-------------------------------------------------

QT       += core gui xml opengl serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GiroTest
TEMPLATE = app

SOURCES +=  main.cpp                \
            girotestwidget.cpp      \
            girodatareciever.cpp

HEADERS  += girotestwidget.h        \
            girodatareciever.h

FORMS    += girotestwidget.ui

# Если операционная система Windows
win32 {
    # Путь к библиотеки libQGLViewer
    LIB_QGLVIEWER_INCLUDEPATH   = D:/Qt/libQGlViewerLibs/libQGLViewer-2.6.1
    # Путь к библиотекам
    LIB_QGLVIEWER_PATH          = D:/Qt/libQGlViewerLibs/libQGLViewer-2.6.1/build

    CONFIG ( release, debug | release   ){
        message( " Win - Version libQGLViewer-2.6.1 - Release " )
        # Добавить путь к библиотекам
        LIBS    += -L$$LIB_QGLVIEWER_PATH/release/ -lQGLViewer2
        message( $$LIBS )
    }

    CONFIG ( debug, debug | release   ){
        message( " Win - libQGLViewer-2.6.1 - Release " )
        # Добавить путь к библиотекам
        LIBS    += -L$$LIB_QGLVIEWER_PATH/debug/ -lQGLViewerd2
        message( $$LIBS )
    }
}

# Если операционная система Linux
unix {
    # Путь к корню .h файлов
    LIB_QGLVIEWER_INCLUDEPATH   = /home/sergey/Libs/libQGLViewer-2.6.1
    # Путь к библиотекам
    LIB_QGLVIEWER_PATH          = /home/sergey/Libs/libQGLViewer-2.6.1/build

    CONFIG ( release, debug | release   ){
        message( " Linux - Version libQGLViewer-2.6.1 - Release " )
        LIBS    += -L$$LIB_QGLVIEWER_PATH -lQGLViewer
    }

    CONFIG ( debug , debug | release   ){
        message( " Linux - Version libQGLViewer-2.6.1 - Debug " )
        LIBS    += -L$$LIB_QGLVIEWER_PATH -lQGLViewer
    }
}

INCLUDEPATH += $$LIB_QGLVIEWER_INCLUDEPATH
message( $$LIB_QGLVIEWER_INCLUDEPATH )

win32 {
    # FACE_RECOGNIZER_PATH =
}
unix{
    FACE_RECOGNIZER_PATH = /home/sergey/MyProjects/Camera/Qt/FaceDetectorDll

    CONFIG ( release, debug | release   ){
        message( " Linux - FaceDetectorDll - Release " )
        LIBS    += -L$$FACE_RECOGNIZER_PATH/build/Release -lFaceDetectorDll

        message( $$LIBS )
    }

    CONFIG ( debug , debug | release   ){
        message( " Linux -FaceDetectorDll - Debug " )
        LIBS    += -L$$FACE_RECOGNIZER_PATH/build/Debug -lFaceDetectorDlld

        message( $$LIBS )
    }
}

INCLUDEPATH += $$FACE_RECOGNIZER_PATH

# Если операционная система Windows
win32 {
    # Путь к корню .h файлов
    OPENCV_INCLUDE_PATH         = D:/Qt/opencv3/OpenCV_Git/include
    OPENCV_INCLUDE_MODULE_PATH  = D:/Qt/opencv3/OpenCV_Git/modules

    # Путь к библиотекам
    OPENCV_LIBS_PATH            = D:/Qt/opencv3/OpenCV_Git_Make/lib

    CONFIG (  release, debug | release    ) {

        message( " Version OpenCV - 3.00 - Release " )
        message( $$OPENCV_LIBS_PATH )

        LIBS    += -L$$OPENCV_LIBS_PATH/Release
        LIBS    += -lopencv_core300         -lopencv_imgproc300
        LIBS    += -lopencv_objdetect300    -lopencv_videoio300
    }

    CONFIG ( debug, debug | release   ) {

        message( " Version OpenCV - 3.00 - Debug " )
        message( $$OPENCV_LIBS_PATH )

        LIBS    += -L$$OPENCV_LIBS_PATH/Debug
        LIBS    += -lopencv_core300d        -lopencv_imgproc300d
        LIBS    += -lopencv_objdetect300d   -lopencv_videoio300d
    }
}

# Если операционная система Linux
unix {
    # Путь к корню .h файлов
    OPENCV_INCLUDE_PATH        =  /home/sergey/Libs/opencv/include
#        OPENCV_INCLUDE_MODULE_PATH =  /home/sergey/Libs/opencv/modules

    # Путь к библиотекам
    OPENCV_LIBS_PATH           = /home/sergey/Libs/opencv/build_release/lib

    CONFIG ( release, debug | release ){

        message( " Unix - Version OpenCV - 3.00 - Release " )
        message( $$OPENCV_LIBS_PATH )

        LIBS    += -L$$OPENCV_LIBS_PATH
        LIBS    += -lopencv_objdetect   -lopencv_imgproc
        LIBS    += -lopencv_videoio     -lopencv_core
    }

    CONFIG ( debug, debug | release ){

        message( " Unix - Version OpenCV - 3.00 - Debug " )
        message( $$OPENCV_LIBS_PATH )

        LIBS    += -L$$OPENCV_LIBS_PATH
        LIBS    += -lopencv_objdetect   -lopencv_imgproc
        LIBS    += -lopencv_videoio     -lopencv_core
    }
}


message( $$OPENCV_INCLUDE_PATH )
message( $$OPENCV_INCLUDE_MODULE_PATH )

