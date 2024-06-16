//
// Created by grons on 08.06.2024.
//

#ifndef OIAK_PROJEKT_BBALGORITHM_H
#define OIAK_PROJEKT_BBALGORITHM_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdint>
#include <chrono>
#include <queue>
#include "Timer.h"

using namespace std;

class BbAlgorithm {

public:
    vector<vector<int>> branchAndBound1(const vector<vector<int>> &processingTimes);

private:
    struct Node {
        vector<int> permutation;
        int lower_bound;
        int level;
    };

    struct Compare {
        bool operator()(const Node &a, const Node &b) {
            return a.lower_bound > b.lower_bound;
        }
    };

    int calculateMakespan(const vector<int> &permutation, const vector<vector<int>> &processingTimes);
    int calculateLowerBound(const vector<int> &permutation, const vector<vector<int>> &processingTimes);
};

int BbAlgorithm::calculateMakespan(const vector<int> &permutation, const vector<vector<int>> &processingTimes) {
    int numJobs = permutation.size();
    int numMachines = processingTimes[0].size();
    vector<vector<int>> completionTimes(numJobs + 1, vector<int>(numMachines + 1, 0));

    for (int i = 1; i <= numJobs; ++i) {
        for (int j = 1; j <= numMachines; ++j) {
            completionTimes[i][j] = max(completionTimes[i - 1][j], completionTimes[i][j - 1]) +
                                    processingTimes[permutation[i - 1]][j - 1];
        }
    }

    return completionTimes[numJobs][numMachines];
}

int BbAlgorithm::calculateLowerBound(const vector<int> &permutation, const vector<vector<int>> &processingTimes) {
    return calculateMakespan(permutation, processingTimes);
}

vector<vector<int>> BbAlgorithm::branchAndBound1(const vector<vector<int>> &processingTimes) {
    int numJobs = processingTimes.size();
    vector<int> bestSolution;
    int bestCost = INT_MAX;

    priority_queue<Node, vector<Node>, Compare> pq;
    Node initialNode = {{}, 0, 0};
    pq.push(initialNode);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.level == numJobs) {
            int makespan = calculateMakespan(node.permutation, processingTimes);
            if (makespan < bestCost) {
                bestCost = makespan;
                bestSolution = node.permutation;
            }
        } else {
            for (int i = 0; i < numJobs; ++i) {
                if (find(node.permutation.begin(), node.permutation.end(), i) == node.permutation.end()) {
                    Node child;
                    child.permutation = node.permutation;
                    child.permutation.push_back(i);
                    child.level = node.level + 1;
                    child.lower_bound = calculateLowerBound(child.permutation, processingTimes);
                    if (child.lower_bound < bestCost) {
                        pq.push(child);
                    }
                }
            }
        }
    }

    return {bestSolution, {bestCost}};
}








#endif //OIAK_PROJEKT_BBALGORITHM_H
