#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include "BbAlgorithm.h"
#include "DataGenerator.h"
#include "Timer.h"
#include "FileReader.h"
#include "NehAlgorithm.h"
#include "Menu.h"
#include "Test.h"

#define MAX_JOBS 500
#define MAX_MACHINES 100

using namespace std;

extern "C" void calculateMakespan(  int* perm, int permSize,
                                    int** processingTimes, int numJobs,
                                    int numMachines, int* makespan);

extern "C" int lowerBound(  int* perm, int permSize,
                            int** processingTimes, int numJobs,
                            int numMachines);

extern "C" void branchAndBound( int* perm, int permSize,
                                int **processingTimes, int numJobs,
                                int numMachines, int* bestMakespan,
                                int* bestPerm, int* bestPermSize,
                                int* currentPerm, int currentPermSize);

extern "C" void neh_algorithm(int processingTimes[MAX_JOBS][MAX_MACHINES],
                              int numJobs, int numMachines,
                              int optimalOrder[MAX_JOBS]);


int main1(){
    interatingThroughtFiles();
}


int main(){
    Menu menu;
    menu.inputData();
    return 0;
}

