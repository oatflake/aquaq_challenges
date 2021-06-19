#pragma once

#include <queue>
#include <memory>
#include <functional>

struct Action;

typedef std::priority_queue<std::shared_ptr<Action>, std::vector<std::shared_ptr<Action>>, 
    std::function<bool(std::shared_ptr<Action> action1, std::shared_ptr<Action> action2)>> ActionQueue;

struct Action {
    int time;
    virtual void perform(ActionQueue& actionQueue) = 0;
    Action(int time) : time(time) {}
};