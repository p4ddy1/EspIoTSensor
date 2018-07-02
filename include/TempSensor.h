#ifndef ESPTEMPSENSOR_TEMPSENSOR_H
#define ESPTEMPSENSOR_TEMPSENSOR_H
#include <Sensor.h>
#include <Libraries/DHTesp/DHTesp.h>
class TempSensor : public Sensor{
public:
    TempSensor(int Pin);
    virtual void initialize();
    virtual HashMap<String,float>& measure();
    virtual String getName();
private:
    DHTesp* dhtEsp;
    HashMap<String,float> data;
};
#endif //ESPTEMPSENSOR_TEMPSENSOR_H
