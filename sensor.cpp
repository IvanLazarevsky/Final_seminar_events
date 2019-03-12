#include "sensor.h"
#include "events.h"


Sensor::Sensor(Observable *observable, int maxSpeed) : eventBus(observable), speedLimit(maxSpeed)
{

}

void Sensor::process(const SensorData& observation) {
    if(observation.speed > speedLimit) {
        eventBus->publish(new TrafficViolationDetected(observation));
    }
    else {
        eventBus->publish(new PassageDetected(observation));
    }
}
