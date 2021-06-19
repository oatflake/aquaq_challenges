#include "Station.h"
#include "Train.h"

auto trainComparator = [](QueuedTrain queuedTrain1, QueuedTrain queuedTrain2) {
    auto [train1, queuedTime1] = queuedTrain1;
    auto [train2, queuedTime2] = queuedTrain2;
    auto t1 = train1.lock();
    auto t2 = train2.lock();
    int lastStationId1 = t1->currentStationId - 1;
    int lastStationId2 = t2->currentStationId - 1;
    if (lastStationId1 == -1 || lastStationId2 == -1) {
        if (lastStationId1 != lastStationId2) {
            return lastStationId1 > lastStationId2;
        }
    } else {
        auto station1 = t1->destinations[lastStationId1].station.lock();
        auto station2 = t2->destinations[lastStationId2].station.lock();
        if (station1->id != station2->id) {
            return station1->id > station2->id;
        }
    }
    if (queuedTime1 != queuedTime2)
        return queuedTime1 > queuedTime2;
    return t1->id > t2->id;
};

Station::Station(int id) : id(id), queue(trainComparator) {}