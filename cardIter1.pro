#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T23:37:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cardIter1
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

CONFIG += c++11

SOURCES += \
        card.cpp \
        game.cpp \
        main.cpp \
        myrect.cpp

HEADERS += \
    card.h \
    game.h \
    myrect.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Desktop/Playing Cards/PNG-cards-1.3/10_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/10_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/10_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/10_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/2_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/2_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/2_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/2_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/3_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/3_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/3_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/3_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/4_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/4_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/4_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/4_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/5_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/5_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/5_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/5_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/6_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/6_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/6_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/6_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/7_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/7_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/7_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/7_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/8_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/8_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/8_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/8_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/9_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/9_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/9_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/9_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/ace_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/ace_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/ace_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/ace_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/ace_of_spades2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/black_joker.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_clubs2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_diamonds2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_hearts2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/jack_of_spades2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_clubs2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_diamonds2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_hearts2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/king_of_spades2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_clubs.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_clubs2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_diamonds.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_diamonds2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_hearts.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_hearts2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_spades.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/queen_of_spades2.png \
    ../../Desktop/Playing Cards/PNG-cards-1.3/red_joker.png

RESOURCES += \
    resource.qrc
