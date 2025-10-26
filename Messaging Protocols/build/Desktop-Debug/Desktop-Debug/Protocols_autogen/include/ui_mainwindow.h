/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *messageEdit;
    QPushButton *connectButton;
    QPushButton *sendButton;
    QPushButton *fileButton;
    QTextEdit *chatLog;
    QCheckBox *serverCheckBox;
    QLineEdit *roomKeyEdit;
    QLabel *Username;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        usernameEdit = new QLineEdit(centralwidget);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setGeometry(QRect(130, 70, 113, 26));
        passwordEdit = new QLineEdit(centralwidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(130, 110, 113, 26));
        passwordEdit->setEchoMode(QLineEdit::Password);
        messageEdit = new QLineEdit(centralwidget);
        messageEdit->setObjectName("messageEdit");
        messageEdit->setGeometry(QRect(130, 160, 521, 31));
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");
        connectButton->setGeometry(QRect(130, 250, 88, 26));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(227, 250, 101, 26));
        fileButton = new QPushButton(centralwidget);
        fileButton->setObjectName("fileButton");
        fileButton->setGeometry(QRect(340, 250, 88, 26));
        chatLog = new QTextEdit(centralwidget);
        chatLog->setObjectName("chatLog");
        chatLog->setGeometry(QRect(130, 300, 531, 70));
        serverCheckBox = new QCheckBox(centralwidget);
        serverCheckBox->setObjectName("serverCheckBox");
        serverCheckBox->setGeometry(QRect(460, 250, 92, 24));
        roomKeyEdit = new QLineEdit(centralwidget);
        roomKeyEdit->setObjectName("roomKeyEdit");
        roomKeyEdit->setGeometry(QRect(130, 210, 113, 26));
        roomKeyEdit->setEchoMode(QLineEdit::Password);
        Username = new QLabel(centralwidget);
        Username->setObjectName("Username");
        Username->setGeometry(QRect(40, 70, 66, 18));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 110, 66, 18));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 170, 101, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 220, 81, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 320, 66, 18));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Protocols", nullptr));
        passwordEdit->setInputMask(QString());
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        fileButton->setText(QCoreApplication::translate("MainWindow", "Share File", nullptr));
        serverCheckBox->setText(QCoreApplication::translate("MainWindow", "server", nullptr));
        Username->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Message Box", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Room Key", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Chat Box", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
