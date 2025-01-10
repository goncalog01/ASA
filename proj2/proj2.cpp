#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <list>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define SOURCE 0
#define TARGET 1

using namespace std;

vector<vector<int>> resG;
deque<int> path = deque<int>();
int result;
    
void readInput()
{
    uint n, k;
    scanf("%d %d", &n, &k);
    resG = vector<vector<int>>(n + 2, vector<int>(n + 2 , 0));

    for (uint i = 0; i < n; i++)
    {
        int costX, costY;
        scanf("%d %d", &costX, &costY);
        resG[SOURCE][i + 2] = costX;
        resG[i + 2][TARGET] = costY;
    }

    for (uint i = 0; i < k; i++)
    {
        int line, col, cost;
        scanf("%d %d %d", &line, &col, &cost);
        resG[line + 1][col + 1] = cost;
        resG[col + 1][line + 1] = cost;
    }
}

int BFS()
{
    vector<int> pi = vector<int>(resG[0].size(), -1);
    vector<int> color = vector<int>(resG[0].size(), WHITE);
    int increase = 0;
    bool foundTarget = false;
    int flowAugmentation = INT16_MAX;
    pi[SOURCE] = -1;
    color[SOURCE] = GRAY;
    deque<int> Q = deque<int>();
    Q.push_back(SOURCE);

    while (!foundTarget && !Q.empty())
    {
        int v = Q[0];
        Q.pop_front();
        for (uint i = 0; i < resG[0].size(); i++)
        {
            if (resG[v][i] && color[i] == WHITE)
            {
                Q.push_back(i);
                color[i] = GRAY;
                pi[i] = v;
                if (i == TARGET)
                {
                    foundTarget = true;
                    break;
                }
            }
        }
        color[v] = BLACK;
    }

    if (foundTarget)
    {
        int t = TARGET;
        while (pi[t] != -1)
        {
            flowAugmentation = min(flowAugmentation, resG[pi[t]][t]);
            path.push_front(t);
            t = pi[t];
        }
        path.push_front(t);
    }

    return flowAugmentation;
}

void edmonds_Karp()
{
    int cf;
    while ((cf = BFS()) != INT16_MAX)
    {
        result += cf;
        int u, v;
        do
        {
            u = path[0];
            v = path[1];
            path.pop_front();
            resG[u][v] -= cf;
            resG[v][u] += cf;

        } while (v != TARGET);
        path.pop_front();
    }
}

int main()
{
    readInput();
    edmonds_Karp();
    printf("%d\n", result);
    return 0;
}
