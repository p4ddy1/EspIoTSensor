#ifndef ESPTEMPSENSOR_DUMMYSENSOR_H
#define ESPTEMPSENSOR_DUMMYSENSOR_H
#include <Sensor.h>
#include <Libraries/DHTesp/DHTesp.h>
class DummySensor : public Sensor{
public:
    DummySensor();
    virtual void initialize();
    virtual HashMap<String,float>& measure();
    virtual String getName();
private:
    HashMap<String,float> data;
};
#endif //ESPTEMPSENSOR_TEMPSENSOR_H
