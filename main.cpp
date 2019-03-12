#include <iostream>
#include <fstream>
#include "observable.h"
#include "eventbus.h"
#include "events.h"
#include "sensor.h"
using namespace std;


class Logger : public Observer {
    ofstream logfile;
public:
    Logger(const string& filename) {
        logfile.open(filename, std::ios::app);
        if(!logfile)
            throw std::runtime_error("Can't open file");
    }

    void onEvent(Event* event) override {
        if(dynamic_cast<PassageDetected*>(event))
            logfile << event->toString() << endl;
    }
};

class Hist : public Observer {
    string violations;
    string passages;
public:
    void onEvent(Event* event) override {
        if(dynamic_cast<TrafficViolationDetected*>(event)) {
            violations += '!';
        }
        else if(dynamic_cast<PassageDetected*>(event)) {
            passages += '*';
        }
        else if(dynamic_cast<ResetViewEvent*>(event)) {
            violations = passages = {};
        }
        else if(dynamic_cast<ShowViewEvent*>(event)) {
            show();
        }
    }

    void show() {
        cout << endl;
        cout << passages << endl;
        cout << violations << endl;
        cout << endl;
    }
};

class Table : public Observer {
    int violations;
    int passages;
    double sumSpeed;
    double sumViolationSpeed;
public:
    void onEvent(Event* event) override {
        TrafficViolationDetected* tv  = dynamic_cast<TrafficViolationDetected*>(event);
        if(tv) {
            violations += 1;
            passages += 1;
            sumSpeed += tv->getSensorData().speed;
            sumViolationSpeed += tv->getSensorData().speed;
        }
        else {
            PassageDetected* p = dynamic_cast<PassageDetected*>(event);
            if(p) {
                passages += 1;
                sumSpeed += p->getSensorData().speed;
            }
            else if(dynamic_cast<ResetViewEvent*>(event)) {
                violations = passages = 0;
                sumSpeed = sumViolationSpeed = 0.0;
            }
            else if(dynamic_cast<ShowViewEvent*>(event)) {
                show();
            }
        }
    }

    void show() {
        cout << endl;
        cout << "Total passages: " << passages << endl;
        cout << "Total violations: " << violations << endl;
        cout << "Violation percent: " << violations * 100 / double(passages)  << "%" <<  endl;
        cout << "Average speed: " << sumSpeed / passages << " km/h" << endl;
        cout << "Average speed in violations: " << sumViolationSpeed / violations << " km/h" << endl;
        cout << endl;
    }
};

class App {
    Sensor* sensor;
    Table* tableView;
    Hist* histView;
    Logger* logger;
    EventBus* eventBus;

public:
    App() {
        eventBus = new EventBus(); // wiring
        tableView = new Table();
        histView = new Hist();
        logger = new Logger("app.log");
        sensor = new Sensor(eventBus, 60);
        eventBus->subscribe(tableView);
        eventBus->subscribe(histView);
        eventBus->subscribe(logger);
    }

    void test() {
        sensor->process(SensorData{1, "5421py11", 45});
        sensor->process(SensorData{2, "5511py43", 59});
        sensor->process(SensorData{3, "7642py41", 80});
        sensor->process(SensorData{4, "6441an11", 60});
        sensor->process(SensorData{5, "5431pa11", 45});
        sensor->process(SensorData{6, "8635hy93", 98});

        ShowViewEvent showEvent;
        ResetViewEvent resetEvent;

        eventBus->publish(&showEvent);
        eventBus->publish(&resetEvent);

        sensor->process(SensorData{7, "9365py11", 56});
        sensor->process(SensorData{8, "1965py07", 60});
        sensor->process(SensorData{9, "8692py77", 93});

        eventBus->publish(&showEvent);
    }
};

int main()
{
    App app;
    app.test();
    return 0;
}
