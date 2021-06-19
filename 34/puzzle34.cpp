#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include "../helper.h"
#include "Action.h"
#include "Station.h"
#include "Train.h"
#include "Arrival.h"
#include "Departure.h"

auto readInput() {
    int i = -1;
    std::vector<std::shared_ptr<Train>> trains;
    std::vector<std::shared_ptr<Station>> stations;
    auto lambda = [&](const std::string& line) {
        if (i == -1) {
            int n = std::count(line.begin(), line.end(), ',');
            for (int k = 0; k < n; k++) {
                trains.push_back(std::make_shared<Train>(k));
            }
        }
        if (i >= 0) {
            auto station = std::make_shared<Station>(i);
            stations.push_back(station);
            auto parts = split(line, ",");
            for (int p = 1; p < parts.size(); p++) {
                if (parts[p].length() == 0)
                    continue;
                auto time = split(parts[p], ":");
                int timeInMinutes = std::stoi(time[0]) * 60 + std::stoi(time[1]);
                trains[p - 1]->destinations.push_back(Destination(station, timeInMinutes));
            }
        }
        i++;
    };
    readInputFile(lambda);
    for (auto train : trains) {
        for (int i = train->destinations.size() - 1; i > 0; i--) {
            train->destinations[i].travelTime -= train->destinations[i - 1].travelTime;
        }
    }
    return std::make_tuple(stations, trains);
}

int main() {
    auto [stations, trains] = readInput();
    auto actionComparator = [](std::shared_ptr<Action> action1, std::shared_ptr<Action> action2) { 
        return action1->time > action2->time; 
    };
    ActionQueue actions(actionComparator);
    for (auto train : trains) {
        actions.push(std::make_shared<Arrival>(train->destinations[0].travelTime, train, train->destinations[0].station));
    }
    while (!actions.empty()) {
        auto action = actions.top();
        actions.pop();
        action->perform(actions);
        if (actions.empty() || actions.top()->time > action->time) {
            for (auto station : stations) {
                if (station->enteredTrain.expired() && !station->queue.empty()) {
                    auto [queuedTrain, queuedTime] = station->queue.top();
                    station->enteredTrain = queuedTrain;
                    station->queue.pop();
                    actions.push(std::make_shared<Departure>(action->time + 5, station));
                }
            }
        }
    }
    int maxTime = -1;
    for (auto train : trains) {
        maxTime = std::max(maxTime, train->lastDepartureTime - train->destinations[0].travelTime);
    }
    std::cout << maxTime << std::endl;
    return 0;
}
