#pragma once

#include <vector>
#include "Destination.h"

struct Train {
    int id;
    int currentStationId = -1;
    std::vector<Destination> destinations;
    int lastDepartureTime = -1;
    Train(int id) : id(id) {}
};