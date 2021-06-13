#include <iostream>
#include <string>
#include "../helper.h"
#include "date.h"   // seems to be builtin c++ 20...? https://en.cppreference.com/w/cpp/chrono/year_month_day/operator_days

auto readInput() {
    std::vector<std::tuple<date::year_month_day, std::string, int>> result;
    int i = 0;
    auto lambda = [&](const std::string& line){
        if (i > 0) {
            auto parts = split(line, ",");
            auto dateParts = split(parts[0], "-");
            auto year = date::year(std::stoi(dateParts[0]));
            auto month = date::month(std::stoi(dateParts[1]));
            auto day = date::day(std::stoi(dateParts[2]));
            auto date = date::year_month_day(year, month, day);
            result.push_back({ date, parts[1], std::stoi(parts[3]) });
            result.push_back({ date, parts[2], std::stoi(parts[4]) });
        }
        i++;
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    std::unordered_map<std::string, date::year_month_day> currentStreaks;
    std::unordered_map<std::string, std::tuple<date::year_month_day, date::year_month_day>> longestStreaks;
    for (auto [date, team, score] : input) {
        if (score == 0) {
            if (currentStreaks.find(team) == currentStreaks.end()) {
                currentStreaks[team] = date;
            }
        }
        if (score > 0) {
            auto currentIter = currentStreaks.find(team);
            if (currentIter != currentStreaks.end()) {
                auto currentStreakBegin = currentIter->second;
                currentStreaks.erase(team);
                auto currentStreakLength = date::sys_days(date) - date::sys_days(currentStreakBegin);
                auto longestIter = longestStreaks.find(team);
                if (longestIter != longestStreaks.end()) {
                    auto [longestStreakBegin, longestStreakEnd] = longestIter->second;
                    auto longestStreakLength = date::sys_days(longestStreakEnd) - date::sys_days(longestStreakBegin);
                    if (currentStreakLength <= longestStreakLength) {
                        continue;
                    }
                }
                longestStreaks[team] = { currentStreakBegin, date };
            }
        }
    }
    date::days maxStreakLength(0);
    std::string team;
    for (const auto& entry : longestStreaks) {
        auto [longestStreakBegin, longestStreakEnd] = entry.second;
        auto longestStreakLength = date::sys_days(longestStreakEnd) - date::sys_days(longestStreakBegin);
        if (maxStreakLength < longestStreakLength) {
            maxStreakLength = longestStreakLength;
            team = entry.first;
        }
    }
    auto [streakBegin, streakEnd] = longestStreaks[team];
    std::cout << team << " ";
    date::to_stream(std::cout, "%Y%m%d", streakBegin);
    std::cout << " ";
    date::to_stream(std::cout, "%Y%m%d", streakEnd);
    std::cout << std::endl;
    return 0;
}
