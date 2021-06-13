#include <iostream>
#include <string>
#include <unordered_map>
#include <math.h>
#include <numeric>
#include "../helper.h"

auto readInput() {
    std::vector<std::tuple<std::string, std::string, bool>> matches;
    int i = -1;
    auto lambda = [&](auto line){
        if (i >= 0) {
            auto parts = split(line, ",");
            auto points = split(parts[2], "-");
            bool winner = std::stoi(points[0]) > std::stoi(points[1]);
            matches.push_back({ parts[0], parts[1], winner });
        }
        i++;
    };
    readInputFile(lambda);
    return matches;
}

float getElo(const std::string& player, std::unordered_map<std::string, float>& elos) {
    float elo = 1200.f;
    auto iter = elos.find(player);
    if (iter == elos.end()) {
        elos[player] = elo;
    } else {
        elo = iter->second;
    }
    return elo;
}

int main() {
    int result = 0;
    auto matches = readInput();
    std::unordered_map<std::string, float> elos;
    for (auto [player1, player2, player1Won] : matches) {
        float player1Elo = getElo(player1, elos);
        float player2Elo = getElo(player2, elos);
        float delta;
        if (player1Won) {
            float Ei = 1.f / (1.f + std::pow(10.f, ((player2Elo - player1Elo) / 400.f)));
            delta = 20.f * (1.f - Ei);
        } else {
            float Ei = 1.f / (1.f + std::pow(10.f, ((player1Elo - player2Elo) / 400.f)));
            delta = -20.f * (1.f - Ei);
        }
        elos[player1] = player1Elo + delta;
        elos[player2] = player2Elo - delta;
    }
    float minElo = std::numeric_limits<float>::max();
    float maxElo = std::numeric_limits<float>::min();
    for (const auto& elo : elos) {
        minElo = std::min(minElo, elo.second);
        maxElo = std::max(maxElo, elo.second);
    }
    std::cout << ((int)maxElo) - ((int)minElo) << std::endl;
    return 0;
}
