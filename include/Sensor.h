#ifndef ESPTEMPSENSOR_SENSOR_H
#define ESPTEMPSENSOR_SENSOR_H
#include <SmingCore/SmingCore.h>

class Sensor{
public:
    virtual void initialize();
    virtual HashMap<String,float>& measure();
    virtual String getName();
};
#endif //ESPTEMPSENSOR_SENSOR_H
