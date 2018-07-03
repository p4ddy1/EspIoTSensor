#include <user_config.h>
#include <sensor_config.h>
#include <SmingCore/SmingCore.h>
#include <TempSensor.h>
#include <DummySensor.h>

MqttClient *mqttClient;
Timer sleepTimer;
Timer connectionTimeoutTimer;

Sensor* sensors[] = {
        new DummySensor(),
        new TempSensor(12)
};

void deepSleep(){
    System.deepSleep(INTERVAL_SEK * 1000);
}

void connectionTimeouts(){
    if(WifiStation.isConnected()){
        return;
    }
    if(mqttClient->getConnectionState() == eTCS_Connected){
        return;
    }
    deepSleep();
}

void measure(){
    StaticJsonBuffer<200> jsonBuffer;
    for(uint8 i = 0; i<(sizeof(sensors) / sizeof(sensors[0])); i++){
        String jsonOut;
        Sensor* currentSensor = sensors[i];
        HashMap<String,float>& sensorData = currentSensor->measure();
        JsonObject& root = jsonBuffer.createObject();
        for(uint8 j = 0; j<sensorData.count(); j++){
            root[sensorData.keyAt(j)] = sensorData.valueAt(j);
        }
        root.printTo(jsonOut);
        mqttClient->publish((String(MQTT_BASE_CHANNEL) + "/" + currentSensor->getName()), jsonOut);
    }
}

void mqttConnect(){
#ifdef ENABLE_SSL
    const uint8_t sha1Fingerprint[] = SSL_SHA1_FINGERPRINT;
    SSLFingerprints fingerprint;
    fingerprint.certSha1 = new uint8_t[SHA1_SIZE];
    memcpy(fingerprint.certSha1, sha1Fingerprint, SHA1_SIZE);
    mqttClient->addSslOptions(SSL_SERVER_VERIFY_LATER);
    mqttClient->pinCertificate(fingerprint);
    mqttClient->connect(DEVICE_NAME,MQTT_USER, MQTT_PWD, true);
#endif
#ifndef ENABLE_SSL
    mqttClient->connect(DEVICE_NAME,MQTT_USER, MQTT_PWD);
#endif
}

void gotIp(IPAddress ip, IPAddress netmask, IPAddress gateway){
    mqttConnect();
    measure();
    sleepTimer.start();
}

void init()
{
    WifiStation.enable(true);
    WifiStation.config(WIFI_SSID,WIFI_PWD);
    WifiAccessPoint.enable(false);
    WifiEvents.onStationGotIP(gotIp);
    WifiStation.connect();

    mqttClient = new MqttClient(MQTT_HOST, MQTT_PORT);

    sleepTimer.initializeMs(2000, deepSleep);
    connectionTimeoutTimer.initializeMs(5000,connectionTimeouts).start(true);
}
