#include <core/observer.hpp>
#include <iostream>

void core::Observable::notify(core::GameEvent event)
{
    for (auto* obs : _observers) {
        obs->update(this, event);
    }
}

void core::Observable::add_observer(core::Observer& observer)
{
    auto itr = std::find(_observers.begin(), _observers.end(), &observer);
    if (itr != _observers.end()) {
        _observers.push_back(&observer);
    }
    else {
        std::cout << "Observer already in observer list" << std::endl;
    }
}

void core::Observable::remove_observer(core::Observer& observer)
{
    _observers.erase(
        std::remove(_observers.begin(), _observers.end(), &observer),
        _observers.end());
}
