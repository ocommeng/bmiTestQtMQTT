#include "testwidget1.h"
#include "ui_testwidget1.h"

TestWidget1::TestWidget1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget1)
{
    ui->setupUi(this);
    this->compteur = 0;

    leftIndicator = new QLabel(this);
    leftIndicator->setGeometry(50, 100, 50, 50);  // Position et taille
    leftIndicator->setStyleSheet("background-color: green; border-radius: 25px;");
    leftIndicator->show();

    rightIndicator = new QLabel(this);
    rightIndicator->setGeometry(670, 100, 50, 50);  // Position et taille
    rightIndicator->setStyleSheet("background-color: green; border-radius: 25px;");
    rightIndicator->hide(); // Cacher initialement


    this->clientMqtt = new QMqttClient(this);
    this->clientMqtt->setHostname("manmiddle.local");
    this->clientMqtt->setPort(1883);
    this->clientMqtt->setClientId("pc");
    this->clientMqtt->connectToHost();

    connect(this->clientMqtt,SIGNAL(connected()),this,SLOT(isConnected()));
}

void TestWidget1::isConnected() {
    QMqttTopicFilter top("topic/test");
    QMqttTopicFilter topClignoDroit("cligno/droit");
    //this->souscription = this->clientMqtt->subscribe(top);
    /*if (!this->souscription) {
        QMessageBox::critical(this,"ERREUR","Souscription impossible");
        return;
    }
    else
        connect(this->souscription, &QMqttSubscription::messageReceived, this, &TestWidget1::receivedMessage);*/
    this->clignoDroit = this->clientMqtt->subscribe(topClignoDroit);
    if (!this->clignoDroit) {
        QMessageBox::critical(this,"ERREUR","Souscription cligno droit impossible");
        return;
    }
    else
        connect(this->clignoDroit, &QMqttSubscription::messageReceived, this, &TestWidget1::receivedMessage);

}

void TestWidget1::updateDisplay(int valeur) {
    ui->lcdNumber->display(valeur);
}

void TestWidget1::receivedMessage(const QMqttMessage &message) {
    this->rightIndicator->setVisible(!this->rightIndicator->isVisible());
    this->leftIndicator->setVisible(!this->leftIndicator->isVisible());
    this->updateDisplay(message.payload().toInt());
}

void TestWidget1::receiveClignoDroitMessage(const QMqttMessage &message) {
    if (message.payload() == "on") {
        this->rightIndicator->setVisible(true);
    }
    if (message.payload() == "off") {
        this->rightIndicator->setVisible(false);
    }
    this->updateDisplay(message.payload().toInt());

}



TestWidget1::~TestWidget1()
{
    delete ui;
}

