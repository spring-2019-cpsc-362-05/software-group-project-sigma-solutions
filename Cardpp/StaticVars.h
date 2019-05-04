#ifndef STATICVARS_H
#define STATICVARS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>
#include <QRectF>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "mainwindow.h"

#define DEFAULT_BET 5
#define DEFAULT_BANK 1000
#define MAX_PLAYERS 7
#define INDEX_ERR 100

static int W_WIDTH = 1200;
static int W_HEIGHT = 625;
static int C_WIDTH = 73;
static int C_HEIGHT = 99;
static int P_WIDTH = 210;
static int P_HEIGHT = 270;
static int D_WIDTH = 510;
static int D_HEIGHT = 75;

static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> uni(75, 125);

static const QString CARD_BACK = ":/cards/cards/card_back.png";

static const std::vector<std::string> INDEX_STRS =
    { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
static const std::vector<std::string> SUIT_STRS =
    { "Spades", "Hearts", "Diamonds", "Clubs" };

static const int PLAYER_XPOS[8] = {975, 975, 735, 495, 255, 15, 15, 345};
static const int PLAYER_YPOS[8] = {45, 390, 390, 390, 390, 390, 45, 45};


static const char BASIC_STRAT_H[18][13] ={
    { 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H' },
    { 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D' },
    { 'H', 'H', 'H', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' }
};
static const int HARD_MOD = 4;

static const char BASIC_STRAT_S[9][13] = {
    { 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'H', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'D', 'D', 'D', 'D', 'D', 'S', 'S', 'H', 'H', 'H', 'H', 'H' },
    { 'S', 'S', 'S', 'S', 'S', 'D', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
};
static const int SOFT_MOD = 13;

static const char BASIC_STRAT_SPLIT[13][13] = {
    { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
    { 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'H', 'H', 'H', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H' },
    { 'H', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H' },
    { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
    { 'S', 'P', 'P', 'P', 'P', 'P', 'S', 'P', 'P', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
    { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' }
};
static const int SPLIT_MOD = 1;

#endif // STATICVARS_H
