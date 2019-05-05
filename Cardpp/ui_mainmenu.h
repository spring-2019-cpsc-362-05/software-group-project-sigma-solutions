/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_mainMenu
{
public:
    QDialogButtonBox *buttonBox;
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
    QPushButton *startButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *mainMenu)
    {
        if (mainMenu->objectName().isEmpty())
            mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        mainMenu->resize(720, 320);
        mainMenu->setMinimumSize(QSize(720, 320));
        mainMenu->setMaximumSize(QSize(720, 320));
        buttonBox = new QDialogButtonBox(mainMenu);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(620, 250, 81, 41));
        QFont font;
        font.setPointSize(10);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        mainMenuLabel = new QLabel(mainMenu);
        mainMenuLabel->setObjectName(QString::fromUtf8("mainMenuLabel"));
        mainMenuLabel->setGeometry(QRect(20, 20, 261, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        mainMenuLabel->setFont(font1);
        numberOfDecksLabel = new QLabel(mainMenu);
        numberOfDecksLabel->setObjectName(QString::fromUtf8("numberOfDecksLabel"));
        numberOfDecksLabel->setGeometry(QRect(20, 260, 71, 21));
        numberOfDecksLabel->setFont(font);
        numberOfDecksSpinBox = new QSpinBox(mainMenu);
        numberOfDecksSpinBox->setObjectName(QString::fromUtf8("numberOfDecksSpinBox"));
        numberOfDecksSpinBox->setGeometry(QRect(90, 260, 42, 22));
        numberOfDecksSpinBox->setFont(font);
        numberOfDecksSpinBox->setMinimum(4);
        numberOfDecksSpinBox->setMaximum(8);
        startingBankLabel = new QLabel(mainMenu);
        startingBankLabel->setObjectName(QString::fromUtf8("startingBankLabel"));
        startingBankLabel->setGeometry(QRect(140, 260, 91, 21));
        startingBankLabel->setFont(font);
        minimumBetLabel = new QLabel(mainMenu);
        minimumBetLabel->setObjectName(QString::fromUtf8("minimumBetLabel"));
        minimumBetLabel->setGeometry(QRect(330, 260, 91, 21));
        minimumBetLabel->setFont(font);
        playerOptionsLabel = new QLabel(mainMenu);
        playerOptionsLabel->setObjectName(QString::fromUtf8("playerOptionsLabel"));
        playerOptionsLabel->setGeometry(QRect(20, 70, 261, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        playerOptionsLabel->setFont(font2);
        gameOptionsLabel = new QLabel(mainMenu);
        gameOptionsLabel->setObjectName(QString::fromUtf8("gameOptionsLabel"));
        gameOptionsLabel->setGeometry(QRect(20, 220, 261, 31));
        gameOptionsLabel->setFont(font2);
        player1GroupBox = new QGroupBox(mainMenu);
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
        player1Active->setGeometry(QRect(30, 30, 21, 17));
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
        player1UC->setCheckable(true);
        player2GroupBox = new QGroupBox(mainMenu);
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
        player3GroupBox = new QGroupBox(mainMenu);
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
        player4GroupBox = new QGroupBox(mainMenu);
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
        player5GroupBox = new QGroupBox(mainMenu);
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
        player7GroupBox = new QGroupBox(mainMenu);
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
        player6GroupBox = new QGroupBox(mainMenu);
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
        startingBankSpinBox = new QSpinBox(mainMenu);
        startingBankSpinBox->setObjectName(QString::fromUtf8("startingBankSpinBox"));
        startingBankSpinBox->setGeometry(QRect(230, 260, 91, 22));
        startingBankSpinBox->setFont(font);
        startingBankSpinBox->setMinimum(0);
        startingBankSpinBox->setMaximum(9999999);
        startingBankSpinBox->setSingleStep(1000);
        startingBankSpinBox->setValue(1000);
        minimumBetSpinBox = new QSpinBox(mainMenu);
        minimumBetSpinBox->setObjectName(QString::fromUtf8("minimumBetSpinBox"));
        minimumBetSpinBox->setGeometry(QRect(420, 260, 91, 22));
        minimumBetSpinBox->setFont(font);
        minimumBetSpinBox->setMinimum(0);
        minimumBetSpinBox->setMaximum(9999999);
        minimumBetSpinBox->setSingleStep(5);
        minimumBetSpinBox->setValue(5);
        label = new QLabel(mainMenu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 140, 51, 21));
        label->setFont(font3);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(mainMenu);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 170, 111, 21));
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        startButton = new QPushButton(mainMenu);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(534, 260, 81, 23));
        startButton->setFont(font);
        pushButton_2 = new QPushButton(mainMenu);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 220, 75, 23));
        player7GroupBox->raise();
        player6GroupBox->raise();
        player5GroupBox->raise();
        player3GroupBox->raise();
        player4GroupBox->raise();
        player2GroupBox->raise();
        player1GroupBox->raise();
        buttonBox->raise();
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
        startButton->raise();
        pushButton_2->raise();

        retranslateUi(mainMenu);
        QObject::connect(buttonBox, SIGNAL(accepted()), mainMenu, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), mainMenu, SLOT(reject()));

        QMetaObject::connectSlotsByName(mainMenu);
    } // setupUi

    void retranslateUi(QDialog *mainMenu)
    {
        mainMenu->setWindowTitle(QApplication::translate("mainMenu", "Card++ Main Menu", nullptr));
        mainMenuLabel->setText(QApplication::translate("mainMenu", "CARD++ MAIN MENU", nullptr));
        numberOfDecksLabel->setText(QApplication::translate("mainMenu", "# of Decks", nullptr));
        startingBankLabel->setText(QApplication::translate("mainMenu", "Starting Bank:", nullptr));
        minimumBetLabel->setText(QApplication::translate("mainMenu", "Minimum Bet:", nullptr));
        playerOptionsLabel->setText(QApplication::translate("mainMenu", "Player Options", nullptr));
        gameOptionsLabel->setText(QApplication::translate("mainMenu", "Game Options", nullptr));
        player1GroupBox->setTitle(QApplication::translate("mainMenu", "Player 1", nullptr));
        player1Active->setText(QString());
        player1UC->setText(QString());
        player2GroupBox->setTitle(QApplication::translate("mainMenu", "Player 2", nullptr));
        player2Active->setText(QString());
        player2UC->setText(QString());
        player3GroupBox->setTitle(QApplication::translate("mainMenu", "Player 3", nullptr));
        player3Active->setText(QString());
        player3UC->setText(QString());
        player4GroupBox->setTitle(QApplication::translate("mainMenu", "Player 4", nullptr));
        player4Active->setText(QString());
        player4UC->setText(QString());
        player5GroupBox->setTitle(QApplication::translate("mainMenu", "Player 5", nullptr));
        player5Active->setText(QString());
        player5UC->setText(QString());
        player7GroupBox->setTitle(QApplication::translate("mainMenu", "Player 7", nullptr));
        player7Active->setText(QString());
        player7UC->setText(QString());
        player6GroupBox->setTitle(QApplication::translate("mainMenu", "Player 6", nullptr));
        player6Active->setText(QString());
        player6UC->setText(QString());
        label->setText(QApplication::translate("mainMenu", "Active", nullptr));
        label_2->setText(QApplication::translate("mainMenu", "User Controlled", nullptr));
        startButton->setText(QApplication::translate("mainMenu", "Start Game", nullptr));
        pushButton_2->setText(QApplication::translate("mainMenu", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainMenu: public Ui_mainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
