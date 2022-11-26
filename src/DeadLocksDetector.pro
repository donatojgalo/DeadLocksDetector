#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T16:13:42
#
#-------------------------------------------------

QT += core gui

TARGET = DeadLocksDetector
TEMPLATE = app

SOURCES += main.cpp \
	mainWindow.cpp \
	workspace.cpp \
	createDetectorDialog.cpp \
	addActivityDialog.cpp \
    selectResourceDialog.cpp \
    detectorExecutor.cpp

HEADERS += mainWindow.h \
	resource.h \
	process.h \
	detectorData.h \
	workspace.h \
	createDetectorDialog.h \
	addActivityDialog.h \
    selectResourceDialog.h \
    activity.h \
    resourceSelected.h \
    detectorExecutor.h

FORMS += mainWindow.ui \
	workspace.ui \
	createDetectorDialog.ui \
	addActivityDialog.ui \
    selectResourceDialog.ui

RESOURCES += \
	images.qrc
