#include "testwidget1.h"
#include "ui_testwidget1.h"

TestWidget1::TestWidget1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget1)
{
    ui->setupUi(this);
    this->compteur = 0;

    this->ui->info->setPixmap(QPixmap(PICTURE_PATH"voyantMoteurOFF.png"));

    //Phase de connexion au broker MQTT
    this->clientMqtt = new QMqttClient(this);
    //this->clientMqtt->setHostname("manmiddle.local");
    this->clientMqtt->setHostname("127.0.0.1");
    this->clientMqtt->setPort(1883);
    this->clientMqtt->setClientId("pc");
    this->clientMqtt->connectToHost();

    connect(this->clientMqtt,SIGNAL(connected()),this,SLOT(isConnected()));
}

void TestWidget1::isConnected() {
    QMqttTopicFilter topicInfo("info");
    this->topicInfo = this->clientMqtt->subscribe(topicInfo);
    if (!this->topicInfo) {
        QMessageBox::critical(this,"ERREUR","Souscription au topic info impossible");
        return;
    }
    else
        connect(this->topicInfo, &QMqttSubscription::messageReceived,this, &TestWidget1::receiveTopicInfo );
}

void TestWidget1::updateDisplay(int valeur) {
    ui->lcdNumber->display(valeur);
}

void TestWidget1::receiveTopicInfo(const QMqttMessage &message) {
    if(message.payload()=="on") {
        this->ui->info->setPixmap(QPixmap(PICTURE_PATH"voyantMoteurON.png"));
    }
    else if(message.payload()=="off") {
        this->ui->info->setPixmap(QPixmap(PICTURE_PATH"voyantMoteurOFF.png"));
    }

}


TestWidget1::~TestWidget1()
{
    delete ui;
}

