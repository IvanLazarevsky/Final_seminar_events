#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include "observable.h"
#include <sensor_data.h>


class Sensor
{
    Observable* eventBus;
    int speedLimit;
public:
    Sensor(Observable* observable, int maxSpeed);
    void process(const SensorData& observation);
};

#endif // SENSOR_H
