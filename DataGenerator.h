//
// Created by grons on 08.06.2024.
//

#ifndef OIAK_PROJEKT_DATAGENERATOR_H
#define OIAK_PROJEKT_DATAGENERATOR_H

#include <vector>
#include <random>

#include <iostream>
#include <vector>
#include <random>

#define MAX_JOBS 100
#define MAX_MACHINES 100

using namespace std;

class DataGenerator {
    int numJobs;
    int numMachines;

public:
    DataGenerator(int numJobs, int numMachines){
        this->numJobs = numJobs;
        this->numMachines = numMachines;
    }

    vector<vector<int>> generateRandomData(int minProcessingTime, int maxProcessingTime) {
        vector<vector<int>> processingTimes(numJobs, vector<int>(numMachines));
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(minProcessingTime, maxProcessingTime);
        for (int i = 0; i < numJobs; ++i) {
            for (int j = 0; j < numMachines; ++j) {
                processingTimes[i][j] = dis(gen);
            }
        }
        return processingTimes;
    }

    //nie wiem czy to zadziała a nie moge sprawdzić
    void convertVectorToArray(const std::vector<std::vector<int>>& vec, int array[MAX_JOBS][MAX_MACHINES], int& numJobs, int& numMachines) {
        numJobs = vec.size();
        numMachines = vec[0].size();

        for (int i = 0; i < numJobs; ++i) {
            for (int j = 0; j < numMachines; ++j) {
                array[i][j] = vec[i][j];
            }
        }
    }
};
/*
int () {
    DataGenerator dg(20, 10);
    vector<vector<int>> processingTimes = dg.generateRandomData(1, 100);
    for (const auto& row : processingTimes) {
        for (int time : row) {
            cout << time << " ";
        }
        cout << endl;
    }
    return 0;
}*/


#endif //OIAK_PROJEKT_DATAGENERATOR_H
