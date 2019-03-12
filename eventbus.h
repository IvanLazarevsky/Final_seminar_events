#ifndef EVENTBUS_H
#define EVENTBUS_H
#include "observable.h"
#include <vector>

class EventBus : public Observable
{
    std::vector<Observer*> subscribers;
public:
    void subscribe(Observer* observer) override;
    void detach(Observer* observer) override;
    void publish(Event* event) override;
};

#endif // EVENTBUS_H
