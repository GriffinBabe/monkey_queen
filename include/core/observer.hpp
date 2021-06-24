#pragma once

#include <vector>

namespace core {

enum GameEvent {

};

class Observer; // forward declaration

class Observable {
public:

    void add_observer(Observer& observer);

    void remove_observer(Observer& observer);

protected:
    void notify(GameEvent event);
private:
    std::vector<Observer*> _observers;
};

class Observer {
public:
    virtual void update(Observable* observer, GameEvent& event) = 0;
};
}