#include "testwidget1.h"
#include "ui_testwidget1.h"

TestWidget1::TestWidget1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget1)
{
    ui->setupUi(this);
    this->compteur = 0;

    this->ui->info->setPixmap(QPixmap(QPIX_PATH"/voyantMoteurOFF.png"));

    //Phase de connexion au broker MQTT
    this->clientMqtt = new QMqttClient(this);
    //this->clientMqtt->setHostname("manmiddle.local");
    this->clientMqtt->setHostname("127.0.0.1");
    this->clientMqtt->setPort(1883);
    this->clientMqtt->setClientId("pc");
    this->clientMqtt->connectToHost();

    //Connexion du signal "connected()" du client MQTT avec le slot "isConnected()" de l'application
    connect(this->clientMqtt,SIGNAL(connected()),this,SLOT(isConnected()));
}

void TestWidget1::isConnected() {
    //Création d'un filtre pour récupérer les messages venant sur le topic "info"
    QMqttTopicFilter topicInfo("info");

    //Abonnement aux messages du topic "info"
    this->topicInfo = this->clientMqtt->subscribe(topicInfo);
    if (!this->topicInfo) {
        //Si l'abonnement es impossible, afficher un message d'erreur
        QMessageBox::critical(this,"ERREUR","Souscription au topic info impossible");
        return;
    }
    else {
        //Sinon, connecter le signal "messageReceived" au slot "receiveTopicInfo"
        connect(this->topicInfo, &QMqttSubscription::messageReceived,this, &TestWidget1::receiveTopicInfo );
    }
}


void TestWidget1::updateDisplay(int valeur) {
    ui->lcdNumber->display(valeur);
}

void TestWidget1::receiveTopicInfo(const QMqttMessage &message) {
    //si le message reçu sur le topic "info" est "on", alors on allume le voyant moteur
    if(message.payload()=="on") {
        this->ui->info->setPixmap(QPixmap(QPIX_PATH"/voyantMoteurON.png"));
    }
    //sinon, si on reçoit "off", on éteint le voyant moteur.
    else if(message.payload()=="off") {
        this->ui->info->setPixmap(QPixmap(QPIX_PATH"/voyantMoteurOFF.png"));
    }
}


TestWidget1::~TestWidget1()
{
    delete ui;
}

