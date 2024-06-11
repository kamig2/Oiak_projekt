//
// Created by grons on 10.06.2024.
//

#ifndef OIAK_PROJEKT_MENU_H
#define OIAK_PROJEKT_MENU_H

#include <iostream>
#include "DataGenerator.h"
#include "NehAlgorithm.h"
#include "BbAlgorithm.h"

extern "C" void neh_algorithm(int processingTimes[MAX_JOBS][MAX_MACHINES],
                              int numJobs, int numMachines,
                              int optimalOrder[MAX_JOBS]);
extern "C" void branchAndBound(int* perm, int permSize,
                               int ** processingTimes, int numJobs,
                               int numMachines, int* bestMakespan,
                               int* bestPerm, int* bestPermSize,
                               int* currentPerm, int currentPermSize);

class Menu{
private:
    BbAlgorithm bbAlgorithm;


    void printVector(const std::vector<std::vector<int>>& vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            for (size_t j = 0; j < vec[i].size(); ++j) {
                std::cout << vec[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    void menu(int numJobs, int numMachines){
        DataGenerator generator(numJobs,numMachines);
        std::vector<std::vector<int>> processingTimesC = generator.generateRandomData(1,10);
        int processingTimesNeh[MAX_JOBS][MAX_MACHINES];
        int optimalOrder[MAX_JOBS];

        int bestMakespan = 9999999;
        int bestPerm[MAX_JOBS];
        int bestPermSize = 0;
        int perm[MAX_JOBS];
        int currentPerm[MAX_JOBS];

        generator.convertVectorToArray(processingTimesC, processingTimesNeh, numJobs, numMachines);

        cout << "Wygenerowana tablica:\n";

        printVector(processingTimesC);

        int ** processingTimesPOinter = generator.convertToPointer(processingTimesC);

        while(true){
            std::cout<<"\n\nWybierz algorytm:\n";
            std::cout<<"1. Algorytm NEH w C++"<<std::endl;
            std::cout<<"2. Algorytm NEH w assemblerze"<<std::endl;
            std::cout<<"3. Algorytm Branch and Bound w C++"<<std::endl;
            std::cout<<"4. Algorytm Branch and Bound w assemblerze"<<std::endl;
            std::cout<<"0. Zmien liczbe zadan i maszyn"<<std::endl;
            int choice;
            int makespan;
            std::cin>>choice;
            switch (choice) {
                case 0:
                    return;
                case 1: {
                    std::vector<int> optimalOrder = nehAlgorithm(processingTimesC);
                    makespan = calculateMakespan(processingTimesC, optimalOrder); //Calculate makespan z neh
                    std::cout << "Optimal job order: ";
                    for (int job: optimalOrder) {
                        std::cout << job << " ";
                    }
                    std::cout << std::endl;
                    cout << "Total makespan: " << makespan;
                    cout << endl;



                    break;
                }
                case 2:
                    neh_algorithm(processingTimesNeh,numJobs,numMachines, optimalOrder );
                    printf("\nOptimal job order: ");
                    for (int i = 0; i < numJobs; ++i) {
                        printf("%d ", optimalOrder[i] );
                    }
                    printf("\n");
                    cout << "Total makespan: " << makespan;
                    cout << endl;

                    break;
                case 3:
                    bbAlgorithm.solve(processingTimesC);

                    break;
                case 4:
                   // branchAndBound(perm, 0, processingTimesNeh, numJobs, numMachines, &bestMakespan, bestPerm, &bestPermSize, currentPerm, 0);
                    cout << "Best permutation: ";
                    for (int i : bestPerm) cout << i << " ";
                    cout << "\nBest makespan: " << bestMakespan << endl;
                    break;
                default:
                    break;

            }

        }

    }
public:
    void inputData(){
        std::cout<<"Podaj liczbe zadan: "<<std::endl;
        int numJobs;
        std::cin>>numJobs;
        std::cout<<"Podaj liczbe maszyn: "<<std::endl;
        int numMachines;
        std::cin>>numMachines;
        menu(numJobs,numMachines);
    }
};
#endif //OIAK_PROJEKT_MENU_H
