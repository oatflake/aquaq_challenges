#include "Departure.h"
#include "Station.h"
#include "Train.h"
#include "Destination.h"
#include "Arrival.h"

void Departure::perform(ActionQueue& actionQueue) {
    auto myStation = station.lock();
    auto departingTrain = myStation->enteredTrain.lock();
    myStation->enteredTrain.reset();
    if (departingTrain->currentStationId < departingTrain->destinations.size() - 1) {
        Destination next = departingTrain->destinations[departingTrain->currentStationId + 1];
        int arrivalTime = time + next.travelTime;
        actionQueue.push(std::make_shared<Arrival>(arrivalTime, departingTrain, next.station));
    } else {
        departingTrain->lastDepartureTime = time;
    }
}