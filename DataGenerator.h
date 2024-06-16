//
// Created by grons on 08.06.2024.
//

#ifndef OIAK_PROJEKT_DATAGENERATOR_H
#define OIAK_PROJEKT_DATAGENERATOR_H

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

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
    std::vector<std::vector<int>> loaddata(std::string filename){
        std::cout<<filename<<std::endl;
        std::vector<std::vector<int>> data;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Nie można otworzyć pliku do odczytu!" << std::endl;
            return data;
        }
        std::string line;
        std::string size;
        std::getline(file, size);
        std::istringstream sizess(size);
        int machines = 0;
        int jobs = 0;
        sizess>>jobs;
        sizess>>machines;

        data.resize(jobs, std::vector<int>(machines));
        int iter = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<int> tokens;
            int token;
            while (iss >> token) {
                tokens.push_back(token);
            }
            for (int i = 0; i < tokens.size(); i++) {
                data[iter][i] = tokens[i];
            }
            iter++;
        }
        file.close();
        return data;
    }

    //metoda bedzie zapisywac też liczbe maszyn i zadań co jest potrzebne do wywołania funkcji assemblerowej
    std::vector<std::vector<int>> loaddata(const std::string& filename, int& numJobs, int& numMachines) {
        std::vector<std::vector<int>> data;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Nie można otworzyć pliku do odczytu!" << std::endl;
            return data;
        }
        std::string line;
        std::string size;
        std::getline(file, size);
        std::istringstream sizess(size);
        sizess >> numJobs >> numMachines;

        data.resize(numJobs, std::vector<int>(numMachines));
        int iter = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<int> tokens;
            int token;
            while (iss >> token) {
                tokens.push_back(token);
            }
            for (int i = 0; i < tokens.size(); i++) {
                data[iter][i] = tokens[i];
            }
            iter++;
        }
        file.close();
        return data;
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

    int** convertToPointer(const vector<vector<int>>& data) {
        int** arrayPointer = new int*[numJobs];
        for (int i = 0; i < numJobs; ++i) {
            arrayPointer[i] = new int[numMachines];
            for (int j = 0; j < numMachines; ++j) {
                arrayPointer[i][j] = data[i][j];
            }
        }
        return arrayPointer;
    }

    void freePointer(int** arrayPointer) {
        for (int i = 0; i < numJobs; ++i) {
            delete[] arrayPointer[i];
        }
    }
};




#endif //OIAK_PROJEKT_DATAGENERATOR_H
