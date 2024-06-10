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
class Menu{
private:
    BbAlgorithm bbAlgorithm;

    void menu(int numJobs, int numMachines){
        DataGenerator generator(numJobs,numMachines);
        std::vector<std::vector<int>> processingTimesC = generator.generateRandomData(1,10);
        int processingTimesNeh[MAX_JOBS][MAX_MACHINES];
        int optimalOrder[MAX_JOBS];
        generator.convertVectorToArray(processingTimesC, processingTimesNeh, numJobs, numMachines);

        while(true){
            std::cout<<"Wybierz algorytm:";
            std::cout<<"1. Algorytm NEH w C++"<<std::endl;
            std::cout<<"2. Algorytm NEH w assemblerze"<<std::endl;
            std::cout<<"3. Algorytm Branch and Bound w C++"<<std::endl;
            std::cout<<"4. Algorytm Branch and Bound w assemblerze"<<std::endl;
            std::cout<<"0. Zmien liczbe zadan i maszyn"<<std::endl;
            int choice;
            std::cin>>choice;
            switch (choice) {
                case 0:
                    return;
                case 1: {
                    std::vector<int> optimalOrder = nehAlgorithm(processingTimesC);

                    std::cout << "Optimal job order: ";
                    for (int job: optimalOrder) {
                        std::cout << job << " ";
                    }
                    std::cout << std::endl;
                    break;
                }
                case 2:
                    neh_algorithm(processingTimesNeh,numJobs,numMachines, optimalOrder );
                    printf("\nOptimal job order: ");
                    for (int i = 0; i < numJobs; ++i) {
                        printf("%d ", optimalOrder[i] );
                    }
                    printf("\n");
                    break;
                case 3:
                    bbAlgorithm.solve(processingTimesC);

                    break;
                case 4:
                    //trzeba dodać funkcje assemblerową Bb
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
