#pragma once

#include <memory>
#include "Action.h"

class Train;
class Station;
class Departure;

struct Arrival : public Action {
    std::weak_ptr<Train> train;
    std::weak_ptr<Station> station;
    Arrival(int time, std::weak_ptr<Train> train, std::weak_ptr<Station> station) : 
        Action(time), train(train), station(station) {}
    virtual void perform(ActionQueue& actionQueue) override;
};