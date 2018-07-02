#include <DummySensor.h>

DummySensor::DummySensor() {

}

void DummySensor::initialize() {
    //
}

String DummySensor::getName() {
    return "dummy";
}

HashMap<String,float>& DummySensor::measure() {
    data["Measurement1"] = 1;
    data["Measurement2"] = 2;
    data["Measurement3"] = 3;
    return data;
}


