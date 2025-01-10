#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_t;

void readInput() {
    int n, m;
    scanf("%d %d", &n, &m);
    graph = vector<vector<int>>(n, vector<int>());
    graph_t = vector<vector<int>>(n, vector<int>());
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x - 1].push_back(y - 1);
        graph_t[y - 1].push_back(x - 1);
    }
}

vector<int> getSources() {
    vector<int> sources = vector<int>();
    for (unsigned int i = 0; i < graph.size(); i++)
        if (graph_t[i].size() == 0)
            sources.push_back(i);
    return sources;
}

vector<int> topologicalSort(vector<int> sources) {
    vector<bool> visited = vector<bool>(graph.size(), false);
    vector<int> toVisit = sources;
    vector<int> sorted = vector<int>(graph.size());
    int index = graph.size() - 1;

    while (toVisit.size() != 0) {
        int u = toVisit[toVisit.size() - 1];
        toVisit.pop_back();
        visited[u] = true;
        bool visiting = false;

        for (auto v : graph[u]) {
            
            if (!visited[v]) {
                visiting = true;
                toVisit.push_back(u);
                visited[v] = true;
                toVisit.push_back(v);
                break;
            }
        }

        if (!visiting)
            sorted[index--] = u;
    }

    return sorted;
}

int longestPath(vector<int> sorted, vector<int> sources) {
    int max_dist = -1;
    vector<int> dist = vector<int>(graph.size(), -1);

    for (auto s : sources)
        dist[s] = 0;

    for (auto u : sorted) {
        for (auto v : graph[u])
            dist[v] = max(dist[v], dist[u] + 1);
    }

    for (auto d : dist)
        max_dist = max(max_dist, d);

    return max_dist + 1;
}

int main() {
    readInput();
    vector<int> sources = getSources();
    vector<int> sorted = topologicalSort(sources);
    int k = sources.size();
    int l = longestPath(sorted, sources);
    printf("%d %d\n", k, l);
    return 0;
}