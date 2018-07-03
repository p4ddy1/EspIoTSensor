//
// Created by patric on 02.07.2018.
//

#ifndef ESPTEMPSENSOR_SENSOR_CONFIG_H
#define ESPTEMPSENSOR_SENSOR_CONFIG_H
    #define DEVICE_NAME "TestSensor"
    #define INTERVAL_SEK 30
    #define WIFI_SSID ""
    #define WIFI_PWD ""

    #define MQTT_HOST ""
    #define MQTT_PORT 8883
    #define MQTT_USER ""
    #define MQTT_PWD ""
    #define MQTT_BASE_CHANNEL "home/sensors/testsensor"

    #ifdef ENABLE_SSL

        #define SSL_SHA1_FINGERPRINT {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    #endif
#endif //ESPTEMPSENSOR_SENSOR_CONFIG_H
