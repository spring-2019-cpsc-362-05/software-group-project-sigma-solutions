/********************************************************************************
** Form generated from reading UI file 'inGameMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INGAMEMENU_H
#define UI_INGAMEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_inGameMenu
{
public:
    QLabel *mainMenuLabel;
    QLabel *numberOfDecksLabel;
    QSpinBox *numberOfDecksSpinBox;
    QLabel *startingBankLabel;
    QLabel *minimumBetLabel;
    QLabel *playerOptionsLabel;
    QLabel *gameOptionsLabel;
    QGroupBox *player1GroupBox;
    QCheckBox *player1Active;
    QCheckBox *player1UC;
    QGroupBox *player2GroupBox;
    QCheckBox *player2Active;
    QCheckBox *player2UC;
    QGroupBox *player3GroupBox;
    QCheckBox *player3Active;
    QCheckBox *player3UC;
    QGroupBox *player4GroupBox;
    QCheckBox *player4Active;
    QCheckBox *player4UC;
    QGroupBox *player5GroupBox;
    QCheckBox *player5Active;
    QCheckBox *player5UC;
    QGroupBox *player7GroupBox;
    QCheckBox *player7Active;
    QCheckBox *player7UC;
    QGroupBox *player6GroupBox;
    QCheckBox *player6Active;
    QCheckBox *player6UC;
    QSpinBox *startingBankSpinBox;
    QSpinBox *minimumBetSpinBox;
    QLabel *label;
    QLabel *label_2;
    QPushButton *exitGameButton;
    QPushButton *startNewGameButton;
    QPushButton *closeMenuButton;

    void setupUi(QDialog *inGameMenu)
    {
        if (inGameMenu->objectName().isEmpty())
            inGameMenu->setObjectName(QString::fromUtf8("inGameMenu"));
        inGameMenu->resize(720, 370);
        inGameMenu->setMinimumSize(QSize(720, 370));
        inGameMenu->setMaximumSize(QSize(720, 370));
        mainMenuLabel = new QLabel(inGameMenu);
        mainMenuLabel->setObjectName(QString::fromUtf8("mainMenuLabel"));
        mainMenuLabel->setGeometry(QRect(20, 20, 261, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        mainMenuLabel->setFont(font);
        numberOfDecksLabel = new QLabel(inGameMenu);
        numberOfDecksLabel->setObjectName(QString::fromUtf8("numberOfDecksLabel"));
        numberOfDecksLabel->setGeometry(QRect(20, 260, 71, 21));
        QFont font1;
        font1.setPointSize(10);
        numberOfDecksLabel->setFont(font1);
        numberOfDecksSpinBox = new QSpinBox(inGameMenu);
        numberOfDecksSpinBox->setObjectName(QString::fromUtf8("numberOfDecksSpinBox"));
        numberOfDecksSpinBox->setGeometry(QRect(90, 260, 42, 22));
        numberOfDecksSpinBox->setFont(font1);
        numberOfDecksSpinBox->setMinimum(4);
        numberOfDecksSpinBox->setMaximum(8);
        startingBankLabel = new QLabel(inGameMenu);
        startingBankLabel->setObjectName(QString::fromUtf8("startingBankLabel"));
        startingBankLabel->setGeometry(QRect(140, 260, 91, 21));
        startingBankLabel->setFont(font1);
        minimumBetLabel = new QLabel(inGameMenu);
        minimumBetLabel->setObjectName(QString::fromUtf8("minimumBetLabel"));
        minimumBetLabel->setGeometry(QRect(330, 260, 91, 21));
        minimumBetLabel->setFont(font1);
        playerOptionsLabel = new QLabel(inGameMenu);
        playerOptionsLabel->setObjectName(QString::fromUtf8("playerOptionsLabel"));
        playerOptionsLabel->setGeometry(QRect(20, 70, 261, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        playerOptionsLabel->setFont(font2);
        gameOptionsLabel = new QLabel(inGameMenu);
        gameOptionsLabel->setObjectName(QString::fromUtf8("gameOptionsLabel"));
        gameOptionsLabel->setGeometry(QRect(20, 220, 261, 31));
        gameOptionsLabel->setFont(font2);
        player1GroupBox = new QGroupBox(inGameMenu);
        player1GroupBox->setObjectName(QString::fromUtf8("player1GroupBox"));
        player1GroupBox->setEnabled(true);
        player1GroupBox->setGeometry(QRect(140, 110, 71, 91));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        player1GroupBox->setFont(font3);
        player1Active = new QCheckBox(player1GroupBox);
        player1Active->setObjectName(QString::fromUtf8("player1Active"));
        player1Active->setGeometry(QRect(30, 30, 16, 17));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setWeight(50);
        player1Active->setFont(font4);
        player1UC = new QCheckBox(player1GroupBox);
        player1UC->setObjectName(QString::fromUtf8("player1UC"));
        player1UC->setEnabled(false);
        player1UC->setGeometry(QRect(30, 60, 16, 21));
        QFont font5;
        font5.setPointSize(8);
        font5.setBold(false);
        font5.setWeight(50);
        player1UC->setFont(font5);
        player2GroupBox = new QGroupBox(inGameMenu);
        player2GroupBox->setObjectName(QString::fromUtf8("player2GroupBox"));
        player2GroupBox->setGeometry(QRect(220, 110, 71, 91));
        player2GroupBox->setFont(font3);
        player2Active = new QCheckBox(player2GroupBox);
        player2Active->setObjectName(QString::fromUtf8("player2Active"));
        player2Active->setGeometry(QRect(30, 30, 21, 17));
        player2Active->setFont(font5);
        player2UC = new QCheckBox(player2GroupBox);
        player2UC->setObjectName(QString::fromUtf8("player2UC"));
        player2UC->setEnabled(false);
        player2UC->setGeometry(QRect(30, 60, 21, 21));
        player2UC->setFont(font5);
        player3GroupBox = new QGroupBox(inGameMenu);
        player3GroupBox->setObjectName(QString::fromUtf8("player3GroupBox"));
        player3GroupBox->setGeometry(QRect(300, 109, 71, 91));
        player3GroupBox->setFont(font3);
        player3Active = new QCheckBox(player3GroupBox);
        player3Active->setObjectName(QString::fromUtf8("player3Active"));
        player3Active->setGeometry(QRect(30, 30, 16, 17));
        player3Active->setFont(font5);
        player3UC = new QCheckBox(player3GroupBox);
        player3UC->setObjectName(QString::fromUtf8("player3UC"));
        player3UC->setEnabled(false);
        player3UC->setGeometry(QRect(30, 60, 16, 21));
        player3UC->setFont(font5);
        player4GroupBox = new QGroupBox(inGameMenu);
        player4GroupBox->setObjectName(QString::fromUtf8("player4GroupBox"));
        player4GroupBox->setGeometry(QRect(380, 110, 71, 91));
        player4GroupBox->setFont(font3);
        player4Active = new QCheckBox(player4GroupBox);
        player4Active->setObjectName(QString::fromUtf8("player4Active"));
        player4Active->setGeometry(QRect(30, 30, 16, 17));
        player4Active->setFont(font5);
        player4UC = new QCheckBox(player4GroupBox);
        player4UC->setObjectName(QString::fromUtf8("player4UC"));
        player4UC->setEnabled(false);
        player4UC->setGeometry(QRect(30, 60, 16, 21));
        player4UC->setFont(font5);
        player5GroupBox = new QGroupBox(inGameMenu);
        player5GroupBox->setObjectName(QString::fromUtf8("player5GroupBox"));
        player5GroupBox->setGeometry(QRect(460, 110, 71, 91));
        player5GroupBox->setFont(font3);
        player5Active = new QCheckBox(player5GroupBox);
        player5Active->setObjectName(QString::fromUtf8("player5Active"));
        player5Active->setGeometry(QRect(30, 30, 16, 17));
        player5Active->setFont(font5);
        player5UC = new QCheckBox(player5GroupBox);
        player5UC->setObjectName(QString::fromUtf8("player5UC"));
        player5UC->setEnabled(false);
        player5UC->setGeometry(QRect(30, 60, 16, 21));
        player5UC->setFont(font5);
        player7GroupBox = new QGroupBox(inGameMenu);
        player7GroupBox->setObjectName(QString::fromUtf8("player7GroupBox"));
        player7GroupBox->setGeometry(QRect(620, 110, 71, 91));
        player7GroupBox->setFont(font3);
        player7Active = new QCheckBox(player7GroupBox);
        player7Active->setObjectName(QString::fromUtf8("player7Active"));
        player7Active->setGeometry(QRect(30, 30, 21, 17));
        player7Active->setFont(font5);
        player7UC = new QCheckBox(player7GroupBox);
        player7UC->setObjectName(QString::fromUtf8("player7UC"));
        player7UC->setEnabled(false);
        player7UC->setGeometry(QRect(30, 60, 16, 21));
        player7UC->setFont(font5);
        player6GroupBox = new QGroupBox(inGameMenu);
        player6GroupBox->setObjectName(QString::fromUtf8("player6GroupBox"));
        player6GroupBox->setGeometry(QRect(540, 110, 71, 91));
        player6GroupBox->setFont(font3);
        player6Active = new QCheckBox(player6GroupBox);
        player6Active->setObjectName(QString::fromUtf8("player6Active"));
        player6Active->setGeometry(QRect(30, 30, 16, 17));
        player6Active->setFont(font5);
        player6UC = new QCheckBox(player6GroupBox);
        player6UC->setObjectName(QString::fromUtf8("player6UC"));
        player6UC->setEnabled(false);
        player6UC->setGeometry(QRect(30, 60, 16, 21));
        player6UC->setFont(font5);
        startingBankSpinBox = new QSpinBox(inGameMenu);
        startingBankSpinBox->setObjectName(QString::fromUtf8("startingBankSpinBox"));
        startingBankSpinBox->setGeometry(QRect(230, 260, 91, 22));
        startingBankSpinBox->setFont(font1);
        startingBankSpinBox->setMinimum(0);
        startingBankSpinBox->setMaximum(9999999);
        startingBankSpinBox->setSingleStep(1000);
        startingBankSpinBox->setValue(1000);
        minimumBetSpinBox = new QSpinBox(inGameMenu);
        minimumBetSpinBox->setObjectName(QString::fromUtf8("minimumBetSpinBox"));
        minimumBetSpinBox->setGeometry(QRect(420, 260, 91, 22));
        minimumBetSpinBox->setFont(font1);
        minimumBetSpinBox->setMinimum(0);
        minimumBetSpinBox->setMaximum(9999999);
        minimumBetSpinBox->setSingleStep(5);
        minimumBetSpinBox->setValue(5);
        label = new QLabel(inGameMenu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 140, 51, 21));
        label->setFont(font3);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(inGameMenu);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 170, 111, 21));
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        exitGameButton = new QPushButton(inGameMenu);
        exitGameButton->setObjectName(QString::fromUtf8("exitGameButton"));
        exitGameButton->setGeometry(QRect(620, 320, 81, 23));
        exitGameButton->setFont(font1);
        startNewGameButton = new QPushButton(inGameMenu);
        startNewGameButton->setObjectName(QString::fromUtf8("startNewGameButton"));
        startNewGameButton->setGeometry(QRect(410, 320, 111, 23));
        startNewGameButton->setFont(font1);
        closeMenuButton = new QPushButton(inGameMenu);
        closeMenuButton->setObjectName(QString::fromUtf8("closeMenuButton"));
        closeMenuButton->setGeometry(QRect(530, 320, 81, 23));
        closeMenuButton->setFont(font1);
        player7GroupBox->raise();
        player6GroupBox->raise();
        player5GroupBox->raise();
        player3GroupBox->raise();
        player4GroupBox->raise();
        player2GroupBox->raise();
        player1GroupBox->raise();
        mainMenuLabel->raise();
        numberOfDecksLabel->raise();
        numberOfDecksSpinBox->raise();
        startingBankLabel->raise();
        minimumBetLabel->raise();
        playerOptionsLabel->raise();
        gameOptionsLabel->raise();
        startingBankSpinBox->raise();
        minimumBetSpinBox->raise();
        label->raise();
        label_2->raise();
        exitGameButton->raise();
        startNewGameButton->raise();
        closeMenuButton->raise();

        retranslateUi(inGameMenu);

        QMetaObject::connectSlotsByName(inGameMenu);
    } // setupUi

    void retranslateUi(QDialog *inGameMenu)
    {
        inGameMenu->setWindowTitle(QApplication::translate("inGameMenu", "Card++ Game Menu", nullptr));
        mainMenuLabel->setText(QApplication::translate("inGameMenu", "CARD++ GAME MENU", nullptr));
        numberOfDecksLabel->setText(QApplication::translate("inGameMenu", "# of Decks", nullptr));
        startingBankLabel->setText(QApplication::translate("inGameMenu", "Starting Bank:", nullptr));
        minimumBetLabel->setText(QApplication::translate("inGameMenu", "Minimum Bet:", nullptr));
        playerOptionsLabel->setText(QApplication::translate("inGameMenu", "Player Options", nullptr));
        gameOptionsLabel->setText(QApplication::translate("inGameMenu", "Game Options", nullptr));
        player1GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 1", nullptr));
        player1Active->setText(QString());
        player1UC->setText(QString());
        player2GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 2", nullptr));
        player2Active->setText(QString());
        player2UC->setText(QString());
        player3GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 3", nullptr));
        player3Active->setText(QString());
        player3UC->setText(QString());
        player4GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 4", nullptr));
        player4Active->setText(QString());
        player4UC->setText(QString());
        player5GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 5", nullptr));
        player5Active->setText(QString());
        player5UC->setText(QString());
        player7GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 7", nullptr));
        player7Active->setText(QString());
        player7UC->setText(QString());
        player6GroupBox->setTitle(QApplication::translate("inGameMenu", "Player 6", nullptr));
        player6Active->setText(QString());
        player6UC->setText(QString());
        label->setText(QApplication::translate("inGameMenu", "Active", nullptr));
        label_2->setText(QApplication::translate("inGameMenu", "User Controlled", nullptr));
        exitGameButton->setText(QApplication::translate("inGameMenu", "Exit Game", nullptr));
        startNewGameButton->setText(QApplication::translate("inGameMenu", "Start New Game", nullptr));
        closeMenuButton->setText(QApplication::translate("inGameMenu", "Close Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inGameMenu: public Ui_inGameMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INGAMEMENU_H
