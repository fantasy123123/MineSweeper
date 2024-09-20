QT       += core gui multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/randomeventthree.cpp \
    Sources/randomeventtwo.cpp \
    Sources/randomeventone.cpp \
    Sources/reborn.cpp \
    Sources/advertisement.cpp \
    Sources/feedback.cpp \
    Sources/about.cpp \
	Sources/custom.cpp \
    Sources/instruction.cpp \
    Sources/musicwindow.cpp \
	Sources/record.cpp \
	Sources/success.cpp \
	Sources/main.cpp \
        Sources/minesweeper.cpp \
          Sources/listwidget.cpp \



HEADERS += \
   Sources/randomeventthree.h \
    Sources/randomeventtwo.h \
    Sources/randomeventone.h \
    Sources/reborn.h \
    Sources/advertisement.h \
    Sources/feedback.h \
    Sources/about.h \
	Sources/custom.h \
    Sources/instruction.h \
    Sources/musicwindow.h \
	Sources/record.h \
	Sources/success.h \
        Sources/minesweeper.h \
          Sources/listwidget.h\


FORMS += \
    Forms/about.ui \
    Forms/advertisement.ui \
	Forms/custom.ui \
    Forms/feedback.ui \
	Forms/minesweeper.ui \
    Forms/musicwindow.ui \
    Forms/randomeventone.ui \
    Forms/randomeventthree.ui \
    Forms/randomeventtwo.ui \
    Forms/reborn.ui \
	Forms/record.ui \
	Forms/success.ui \
    Forms/instruction.ui \
Forms/listwidget.ui \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resource.qrc

RC_ICONS = Images/icon.ico
