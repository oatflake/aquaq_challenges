#include "Arrival.h"
#include "Train.h"
#include "Station.h"
#include "Departure.h"

void Arrival::perform(ActionQueue& actionQueue) {
    train.lock()->currentStationId++;
    auto myStation = station.lock();
    myStation->queue.push({ train, time });
}