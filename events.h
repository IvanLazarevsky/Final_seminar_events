#ifndef EVENTS_H
#define EVENTS_H
#include "observable.h"
#include "sensor_data.h"
#include <sstream>

class PassageDetected : public Event {
    SensorData data;
protected:
    std::string formatData() const {
        std::ostringstream ostr;
        ostr << "Time: " << data.time << "s Id: " << data.id << " Speed: " << data.speed << " km/h";
        return ostr.str();
    }

public:
    PassageDetected(const SensorData& data) : data(data) {}
    std::string toString() const override {
        return "Passage: " + formatData();
    }
    SensorData getSensorData() const { return data; }
};

class TrafficViolationDetected : public PassageDetected {
public:
    using PassageDetected::PassageDetected;
    std::string toString() const override {
        return "Violation: " + formatData();
    }
};

class ResetViewEvent : public Event {
    std::string toString() const override {
        return "ResetEvent";
    }
};

class ShowViewEvent : public Event {
    std::string toString() const override {
        return "ViewEvent";
    }
};

#endif // EVENTS_H
