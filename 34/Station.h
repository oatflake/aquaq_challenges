#pragma once

#include <queue>
#include <memory>
#include <vector>
#include <functional>

struct Train;

typedef std::tuple<std::weak_ptr<Train>, int> QueuedTrain;

struct Station {
    int id;
    std::priority_queue<QueuedTrain, std::vector<QueuedTrain>, 
        std::function<bool(QueuedTrain, QueuedTrain)>> queue;
    std::weak_ptr<Train> enteredTrain;
    Station(int id);
};