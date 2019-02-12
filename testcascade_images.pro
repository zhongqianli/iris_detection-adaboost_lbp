TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


DESTDIR = $$PWD


INCLUDEPATH += /usr/local/include \
INCLUDEPATH += /usr/local/include/opencv \
INCLUDEPATH += /usr/local/include/opencv2 \
INCLUDEPATH += /usr/local/include/opencv2/core \
INCLUDEPATH += /usr/local/include/opencv2/dnn \
INCLUDEPATH += /usr/local/include/opencv2/highgui \
INCLUDEPATH += /usr/local/include/opencv2/imgcodecs \
INCLUDEPATH += /usr/local/include/opencv2/imgproc \
INCLUDEPATH += /usr/local/include/opencv2/ml \
INCLUDEPATH += /usr/local/include/opencv2/objdetect \
INCLUDEPATH += /usr/local/include/opencv2/video \
INCLUDEPATH += /usr/local/include/opencv2/videoio \

unix:LIBS += `pkg-config opencv --cflags --libs`

SOURCES += testcascade_images.cpp
