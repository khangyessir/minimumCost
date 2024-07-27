#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_set>
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int n = source.length();
        if(n != target.length()) return -1;
        const long long INF = LLONG_MAX;
        unordered_map<char, vector<pair<char, long long>>> graph;
        for(int i=0; i<original.size(); i++) {
            graph[original[i]].emplace_back(changed[i], cost[i]);
        }
        auto dijkstra = [&](char start) {
            unordered_map<char, long long> minCost;
            for(char c = 'a'; c <= 'z'; c++) {
                minCost[c] = INF;
            }
            minCost[start] = 0;
            priority_queue<pair<long long, char>, vector<pair<long long, char>>, greater<pair<long long, char>>> pq;
            pq.emplace(0, start);
            while(!pq.empty()) {
                long long currCost = pq.top().first;
                char u = pq.top().second;
                pq.pop();
                if(currCost > minCost[u]) continue;
                for(auto& [v, w] : graph[u]) {
                    if(currCost + w < minCost[v]) {
                        minCost[v] = currCost + w;
                        pq.emplace(currCost + w, v);
                    }
                }
            }
            return minCost;
        };
        unordered_map<char, unordered_map<char, long long>> shortestPaths;
        for(char c = 'a'; c <= 'z'; c++) {
            shortestPaths[c] = dijkstra(c);
        }
        long long res = 0;
        for(int i=0; i<n; i++) {
            char sChar = source[i];
            char tChar = target[i];
            long long minToChange = shortestPaths[sChar][tChar];
            if(minToChange == INF) return -1;
            res += minToChange;
        }
        return res;
    } 
};
