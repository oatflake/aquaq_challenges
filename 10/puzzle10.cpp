#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include "../helper.h"

struct Node {
    int edgesBegin;
    int numEdges;
    Node(int edgesBegin, int numEdges) : 
        edgesBegin(edgesBegin), numEdges(numEdges) {}
};

struct Edge {
    int toNode;
    int value;
    Edge(int toNode, int value) : 
        toNode(toNode), value(value) {}
};

typedef std::pair<int, int> Queued;

class Graph {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
public:
    Graph(std::vector<Node> nodes, std::vector<Edge> edges) :
        nodes(nodes), edges(edges) {}

    int bfs(int start, int goal) {
        std::priority_queue<Queued, std::vector<Queued>, std::greater<Queued>> queue;
        std::unordered_set<int> visited;
        queue.push({ 0, start });
        visited.insert(start);
        while (!queue.empty()) {
            Queued p = queue.top();
            int pathCost = p.first;
            int current = p.second;
            queue.pop();
            visited.insert(current);
            if (current == goal)
                return pathCost;
            if (nodes[current].edgesBegin == -1)
                continue;
            int edgesBegin = nodes[current].edgesBegin;
            int edgesEnd = nodes[current].edgesBegin + nodes[current].numEdges;
            for (int i = edgesBegin; i < edgesEnd; i++) {
                if (visited.find(edges[i].toNode) != visited.end())
                    continue;
                queue.push({ pathCost + edges[i].value, edges[i].toNode });
            }
        }
        return -1;
    }
};

auto readInput() {
    int i = -1;
    std::vector<std::tuple<std::string, std::string, int>> input;
    auto lambda = [&](const std::string& line){
        if (i >= 0) {
            auto parts = split(line, ",");
            input.push_back({ parts[0], parts[1], std::stoi(parts[2]) });
        }
        i++;
    };
    readInputFile(lambda);
    return input;
}

auto namesToIds(const std::vector<std::tuple<std::string, std::string, int>>& input) {
    int i = 0;
    std::unordered_map<std::string, int> dict;
    for (auto [name1, name2, value] : input) {
        if (dict.find(name1) == dict.end()) {
            dict[name1] = i++;
        }
        if (dict.find(name2) == dict.end()) {
            dict[name2] = i++;
        }
    }
    return dict;
}

Graph createGraph(const std::unordered_map<std::string, int>& ids, const std::vector<std::tuple<std::string, std::string, int>>& input) {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    for (int i = 0; i < ids.size(); i++) {
        nodes.push_back(Node(-1, 0));
    }
    for (auto [name1, name2, value] : input) {
        int name1ID = ids.at(name1);
        if (nodes[name1ID].edgesBegin == -1)
            nodes[name1ID].edgesBegin = edges.size();
        nodes[name1ID].numEdges++;
        edges.push_back(Edge(ids.at(name2), value));
    }
    return Graph(nodes, edges);
}

int main() {
    auto input = readInput();
    auto ids = namesToIds(input);
    Graph graph = createGraph(ids, input);
    std::cout << graph.bfs(ids.at("TUPAC"), ids.at("DIDDY")) << std::endl;
    return 0;
}
