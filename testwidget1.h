#ifndef TESTWIDGET1_H
#define TESTWIDGET1_H

#include <QWidget>
#include <QMqttClient>
#include <QMessageBox>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class TestWidget1; }
QT_END_NAMESPACE

class TestWidget1 : public QWidget
{
    Q_OBJECT

public:
    TestWidget1(QWidget *parent = nullptr);
    ~TestWidget1();

public slots:
    void isConnected();
    void updateDisplay(int valeur);
    void receiveTopicInfo(const QMqttMessage &message);

private:
    Ui::TestWidget1 *ui;
    QMqttClient *clientMqtt;
    QMqttSubscription *topicInfo;

      int compteur;
};
#endif // TESTWIDGET1_H
