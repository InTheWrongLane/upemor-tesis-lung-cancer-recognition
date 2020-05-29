#-------------------------------------------------
#
# Project created by Javier Gallardo Vargas 2015-09-05T06:49:11
#
#-------------------------------------------------

QT           += core
QT           -= gui
QT_CONFIG    -= no-pkg-config
CONFIG       += link_pkgconfig
CONFIG += c++11

LIBS += -L/usr/local/lib
#LIBS += -lopencv_cudabgsegm
#LIBS += -lopencv_cudaobjdetect
#LIBS += -lopencv_cudastereo
LIBS += -lopencv_stitching
#LIBS += -lopencv_cudafeatures2d
LIBS += -lopencv_superres
#LIBS += -lopencv_cudacodec
LIBS += -lopencv_videostab
#LIBS += -lopencv_cudaoptflow
#LIBS += -lopencv_cudalegacy
#LIBS += -lopencv_cudawarping
#LIBS += -lopencv_adas
LIBS += -lopencv_bgsegm
LIBS += -lopencv_bioinspired
LIBS += -lopencv_ccalib
#LIBS += -lopencv_cvv
LIBS += -lopencv_datasets
LIBS += -lopencv_face
#LIBS += -lopencv_latentsvm
LIBS += -lopencv_objdetect
LIBS += -lopencv_line_descriptor
LIBS += -lopencv_optflow
LIBS += -lopencv_reg
LIBS += -lopencv_rgbd
LIBS += -lopencv_saliency
LIBS += -lopencv_surface_matching
LIBS += -lopencv_text
LIBS += -lopencv_tracking
LIBS += -lopencv_xfeatures2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_features2d
LIBS += -lopencv_shape
LIBS += -lopencv_video
LIBS += -lopencv_ml
LIBS += -lopencv_flann
LIBS += -lopencv_ximgproc
LIBS += -lopencv_xobjdetect
LIBS += -lopencv_xphoto
LIBS += -lopencv_highgui
LIBS += -lopencv_videoio
LIBS += -lopencv_photo
LIBS += -lopencv_imgcodecs
#LIBS += -lopencv_cudaimgproc
#LIBS += -lopencv_cudafilters
LIBS += -lopencv_imgproc
#LIBS += -lopencv_cudaarithm
LIBS += -lopencv_core
#LIBS += -lopencv_cudev
#LIBS += -lopencv_hal

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CancerRecognition
TEMPLATE = app

DEFINES += APP_VERSION=\\\"1.0.0\\\"

SOURCES +=  main.cpp \
            gui/mainwindow.cpp \
            gui/svmform.cpp \
            gui/my_qlabel.cpp \
            core/lung.cpp \
            core/watershedsegmenter.cpp \
            core/featuredetector.cpp \
            qt/io_img.cpp \
            qt/mat_and_qimage.cpp \


HEADERS  += gui/mainwindow.h \
            gui/my_qlabel.h \
            gui/svmform.h \
            core/lung.h \
            core/watershedsegmenter.h \
            core/featuredetector.h \
            qt/mat_and_qimage.hpp \
            qt/io_img.hpp \


FORMS    += gui/mainwindow.ui \
            gui/svmform.ui

