#include "eventbus.h"
#include <algorithm>

void EventBus::subscribe(Observer *observer)
{
    subscribers.push_back(observer);
}

void EventBus::detach(Observer *observer)
{
    auto it = std::find(subscribers.begin(), subscribers.end(), observer);
    if(it != subscribers.end())
        subscribers.erase(it);
}

void EventBus::publish(Event *event)
{
    for(Observer* observer : subscribers) {
        observer->onEvent(event);
    }
}
