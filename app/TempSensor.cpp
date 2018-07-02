#include <TempSensor.h>

TempSensor::TempSensor(int Pin) {
    dhtEsp = new DHTesp();
    dhtEsp->setup(Pin,DHTesp::DHT11);
}

void TempSensor::initialize() {
    //
}

String TempSensor::getName() {
    return "temp";
}

HashMap<String,float>& TempSensor::measure() {
    delay(dhtEsp->getMinimumSamplingPeriod());
    data["temperature"] = dhtEsp->getTemperature();
    data["humidity"] = dhtEsp->getHumidity();
    return data;
}


