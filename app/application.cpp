#include <user_config.h>
#include <sensor_config.h>
#include <SmingCore/SmingCore.h>
#include <TempSensor.h>
#include <DummySensor.h>

MqttClient *mqttClient;
Timer sleepTimer;
Timer connectionTimeoutTimer;

/**
 * Array of sensors that will be queried
 */
Sensor* sensors[] = {
        new DummySensor(),
        new TempSensor(12)
};

/**
 * Called by timer to put the ESP into deep sleep. Timer is used because deep sleep has to be a little bit delayed to be
 * sure that all of the data is published successfully via MQTT, because we are sending with QoS 0 at the moment.
 */
void deepSleep(){
    System.deepSleep(INTERVAL_SEK * 1000);
}

/**
 * Called by timer to check if the Wifi and MQTT connections are still alive.
 * If not, put the ESP into deep sleep
 */
void connectionTimeouts(){
    if(WifiStation.isConnected()){
        return;
    }
    if(mqttClient->getConnectionState() == eTCS_Connected){
        return;
    }
    deepSleep();
}

/**
 * Queries all sensors in the sensors array, converts measured data into JSON and pushes it to a MQTT channel according
 * to its name.
 */
void measure(){
    DynamicJsonBuffer jsonBuffer(400);
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

/**
 * Establishes connection to the MQTT broker. If SSL is enabled, the SHA1 hash of the server certificate will be compared
 * to the predefined hash in sensor_config.h so that we are sure we are connected to the right server.
 */
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
/**
 * Called if the wifi connection is established successfully. Will start the MQTT connection process, queries the sensors
 * and puts system into deep sleep afterwards.
 * @param ip
 * @param netmask
 * @param gateway
 */
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
