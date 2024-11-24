#include "testwidget1.h"
#include "ui_testwidget1.h"

TestWidget1::TestWidget1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget1)
{
    ui->setupUi(this);
    this->compteur = 0;

    this->ui->clignoDroit->setPixmap(QPixmap("/home/bmi/BacASable/testwidget1/arrow-right-green.png"));
    this->ui->clignoGauche->setPixmap(QPixmap("/home/bmi/BacASable/testwidget1/arrow-left-gray.png"));

    this->clientMqtt = new QMqttClient(this);
    this->clientMqtt->setHostname("manmiddle.local");
    this->clientMqtt->setPort(1883);
    this->clientMqtt->setClientId("pc");
    this->clientMqtt->connectToHost();

    connect(this->clientMqtt,SIGNAL(connected()),this,SLOT(isConnected()));
}

void TestWidget1::isConnected() {
    QMqttTopicFilter topClignoDroit("cligno/droit");
    this->clignoDroit = this->clientMqtt->subscribe(topClignoDroit);
    if (!this->clignoDroit) {
        QMessageBox::critical(this,"ERREUR","Souscription cligno droit impossible");
        return;
    }
    else
        connect(this->clignoDroit, &QMqttSubscription::messageReceived, this, &TestWidget1::receiveClignoDroitMessage);
    QMqttTopicFilter topClignoGauche("cligno/gauche");
    this->clignoGauche = this->clientMqtt->subscribe(topClignoGauche);
    if (!this->clignoGauche) {
        QMessageBox::critical(this,"ERREUR","Souscription cligno gauche impossible");
        return;
    }
    else
        connect(this->clignoGauche, &QMqttSubscription::messageReceived, this, &TestWidget1::receiveClignoGaucheMessage);

}

void TestWidget1::updateDisplay(int valeur) {
    ui->lcdNumber->display(valeur);
}

void TestWidget1::receiveClignoDroitMessage(const QMqttMessage &message) {
    if (message.payload().toStdString()=="on") {
        this->ui->clignoDroit->setPixmap(QPixmap("/home/bmi/BacASable/testwidget1/arrow-right-green.png"));
    }
    else if (message.payload().toStdString() == "off") {
        this->ui->clignoDroit->setPixmap(QPixmap("/home/bmi/BacASable/testwidget1/arrow-right-gray.png"));
    }
}

void TestWidget1::receiveClignoGaucheMessage(const QMqttMessage &message) {
    if (message.payload().toStdString()=="on") {
        this->ui->clignoGauche->setPixmap(QPixmap("/home/bmi/BacASable/testwidget1/arrow-left-green.png"));
    }
    else if (message.payload().toStdString() == "off") {
        this->ui->clignoGauche->setPixmap(QPixmap("/home/bmi/BacASable/testwidget1/arrow-left-gray.png"));
    }
}



TestWidget1::~TestWidget1()
{
    delete ui;
}

