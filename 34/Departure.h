#pragma once

#include <memory>
#include <queue>
#include "Action.h"

class Station;
class Destination;

struct Departure : public Action {
    std::weak_ptr<Station> station;
    Departure(int time, std::weak_ptr<Station> station) : Action(time), station(station) {}
    virtual void perform(ActionQueue& actionQueue) override;
};