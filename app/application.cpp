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
    for(int i = 0; i<(sizeof(sensors) / sizeof(sensors[0])); i++){
        String jsonOut;
        Sensor* currentSensor = sensors[i];
        HashMap<String,float>& sensorData = currentSensor->measure();
        JsonObject& root = jsonBuffer.createObject();
        for(int j = 0; j<sensorData.count(); j++){
            root[sensorData.keyAt(j)] = sensorData.valueAt(j);
        }
        root.printTo(jsonOut);
        mqttClient->publish((String(MQTT_BASE_CHANNEL) + "/" + currentSensor->getName()), jsonOut);
    }
}

void gotIp(IPAddress ip, IPAddress netmask, IPAddress gateway){
    mqttClient->connect(DEVICE_NAME);
    measure();
    sleepTimer.start();
}

void init()
{
    WifiStation.enable(true);
    WifiStation.config("Testnedds","testitest552");
    WifiAccessPoint.enable(false);
    WifiEvents.onStationGotIP(gotIp);
    WifiStation.connect();

    mqttClient = new MqttClient(MQTT_HOST, MQTT_PORT);

    sleepTimer.initializeMs(2000, deepSleep);
    connectionTimeoutTimer.initializeMs(5000,connectionTimeouts).start(true);
}
