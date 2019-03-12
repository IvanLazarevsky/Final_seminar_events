#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <string>

class Event {
public:
    virtual ~Event() {}
    virtual std::string toString() const = 0;
};

class Observer { // Наблюдатель
public:
    virtual void onEvent(Event* event) = 0;
    virtual ~Observer() {}
};

class Observable // Шина событий
{
public:
    virtual void subscribe(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void publish(Event* event) = 0;
    virtual ~Observable() {}
};



#endif // OBSERVABLE_H
