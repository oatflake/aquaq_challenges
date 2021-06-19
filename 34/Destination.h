#pragma once

#include <memory>

class Station;

struct Destination {
    std::weak_ptr<Station> station;
    int travelTime;
    Destination(std::weak_ptr<Station> station, int travelTime) : station(station), travelTime(travelTime) {}
};