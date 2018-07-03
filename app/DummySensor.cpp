#include <DummySensor.h>

/**
 * Use this as template to implement new sensors. Look at the TempSensor if you need a real world example
 */

DummySensor::DummySensor() {

}

/**
 * Do your initialization stuff here
 */
void DummySensor::initialize() {
    //
}

/**
 * Return the name of the sensor as String here
 * @return Name of the sensor
 */
String DummySensor::getName() {
    return "dummy";
}

/**
 * Do your measurements and return them here
 * @return measured data as HashMap
 */
HashMap<String,float>& DummySensor::measure() {
    data["Measurement1"] = 1;
    data["Measurement2"] = 2;
    data["Measurement3"] = 3;
    return data;
}


