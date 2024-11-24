/********************************************************************************
** Form generated from reading UI file 'testwidget1.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET1_H
#define UI_TESTWIDGET1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWidget1
{
public:
    QPushButton *pushButton;
    QLCDNumber *lcdNumber;
    QLabel *clignoDroit;
    QLabel *clignoGauche;

    void setupUi(QWidget *TestWidget1)
    {
        if (TestWidget1->objectName().isEmpty())
            TestWidget1->setObjectName("TestWidget1");
        TestWidget1->resize(800, 600);
        pushButton = new QPushButton(TestWidget1);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 370, 331, 141));
        lcdNumber = new QLCDNumber(TestWidget1);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(200, 100, 341, 181));
        clignoDroit = new QLabel(TestWidget1);
        clignoDroit->setObjectName("clignoDroit");
        clignoDroit->setGeometry(QRect(640, 290, 91, 71));
        clignoDroit->setPixmap(QPixmap(QString::fromUtf8("arrow-right-gray.png")));
        clignoDroit->setScaledContents(true);
        clignoGauche = new QLabel(TestWidget1);
        clignoGauche->setObjectName("clignoGauche");
        clignoGauche->setGeometry(QRect(60, 290, 91, 71));
        clignoGauche->setPixmap(QPixmap(QString::fromUtf8("arrow-left-gray.png")));
        clignoGauche->setScaledContents(true);

        retranslateUi(TestWidget1);

        QMetaObject::connectSlotsByName(TestWidget1);
    } // setupUi

    void retranslateUi(QWidget *TestWidget1)
    {
        TestWidget1->setWindowTitle(QCoreApplication::translate("TestWidget1", "TestWidget1", nullptr));
        pushButton->setText(QCoreApplication::translate("TestWidget1", "Incr\303\251menter", nullptr));
        clignoDroit->setText(QString());
        clignoGauche->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TestWidget1: public Ui_TestWidget1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET1_H
