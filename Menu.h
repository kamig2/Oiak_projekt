////
//// Created by grons on 10.06.2024.
////
//
//#ifndef OIAK_PROJEKT_MENU_H
//#define OIAK_PROJEKT_MENU_H
//
//#include <iostream>
//#include "DataGenerator.h"
//#include "NehAlgorithm.h"
//#include "BbAlgorithm.h"
//
//extern "C" void neh_algorithm(int processingTimes[MAX_JOBS][MAX_MACHINES],
//                              int numJobs, int numMachines,
//                              int optimalOrder[MAX_JOBS]);
//extern "C" void branchAndBound(int* perm, int permSize,
//                               int ** processingTimes, int numJobs,
//                               int numMachines, int* bestMakespan,
//                               int* bestPerm, int* bestPermSize,
//                               int* currentPerm, int currentPermSize);
//
//class Menu{
//private:
//    BbAlgorithm bbAlgorithm;
//
//
//    void printVector(const vector<vector<int>>& vec) {
//        for (size_t i = 0; i < vec.size(); ++i) {
//            for (size_t j = 0; j < vec[i].size(); ++j) {
//                cout << vec[i][j] << "\t";
//            }
//            cout << endl;
//        }
//    }
//
//    void menu(int numJobs, int numMachines){
//        DataGenerator generator(numJobs,numMachines);
//        vector<vector<int>> processingTimesC = generator.generateRandomData(1,10);
//    //  processingTimesC = generator.loaddata("pliki testowe//ta001.txt");
//
//        int processingTimesNeh[MAX_JOBS][MAX_MACHINES];
//        int optimalOrder[MAX_JOBS];
//
//        int bestMakespan = 9999999;
//        int bestPerm[MAX_JOBS];
//        int bestPermSize = 0;
//        int perm[MAX_JOBS];
//        int currentPerm[MAX_JOBS];
//
//        generator.convertVectorToArray(processingTimesC, processingTimesNeh, numJobs, numMachines);
//
//        cout << "Wygenerowana tablica:\n";
//
//        printVector(processingTimesC);
//
//        int ** processingTimesPOinter = generator.convertToPointer(processingTimesC);
//
//        while(true){
//            cout<<"\n\nWybierz algorytm:\n";
//            cout<<"1. Algorytm NEH w C++"<<endl;
//            cout<<"2. Algorytm NEH w assemblerze"<<endl;
//            cout<<"3. Algorytm Branch and Bound w C++"<<endl;
//            cout<<"4. Algorytm Branch and Bound w assemblerze"<<endl;
//            cout<<"0. Zmien liczbe zadan i maszyn"<<endl;
//            int choice;
//            int makespan;
//            cin>>choice;
//            switch (choice) {
//                case 0:
//                    return;
//                case 1: {
//                    vector<int> optimalOrder = nehAlgorithm(processingTimesC);
//                    makespan = calculateMakespan(processingTimesC, optimalOrder); //Calculate makespan z neh
//                    cout << "Optymalna kolejnosc zadan: ";
//                    for (int job: optimalOrder) {
//                        cout << job << " ";
//                    }
//                    cout << endl;
//                    cout << "Calkowity czas wykonywania: " << makespan;
//                    cout << endl;
//
//
//                    break;
//                }
//                case 2:
//                    neh_algorithm(processingTimesNeh,numJobs,numMachines, optimalOrder );
//                    printf("\nOptymalna kolejnosc zadan: ");
//                    for (int i = 0; i < numJobs; ++i) {
//                        printf("%d ", optimalOrder[i] );
//                    }
//                    printf("\n");
//                    cout << "Calkowity czas wykonywania: " << makespan;
//                    cout << endl;
//
//                    break;
//                case 3: {
//                    vector<vector<int>> result = bbAlgorithm.branchAndBound1(processingTimesC);
//                    cout << "Najlepsza permutacja: ";
//                    for (int job: result[0]) {
//                        cout << job << " ";
//                    }
//                    cout << "\nBest makespan: " << result[1][0] << endl;
//                }
//                    break;
//                case 4:
//                    branchAndBound(perm, 0, processingTimesPOinter, numJobs, numMachines, &bestMakespan, bestPerm, &bestPermSize, currentPerm, 0);
//                    cout << "Best permutation: ";
//                    for (int i : bestPerm) cout << i << " ";
//                    cout << "\nBest makespan: " << bestMakespan << endl;
//                    break;
//                default:
//                    break;
//
//            }
//
//        }
//
//    }
////public:
////    void menu(int numJobs, int numMachines, int nrPliku){
////        DataGenerator generator(numJobs,numMachines);
////        vector<vector<int>> processingTimesC;
////        BbAlgorithm bbAlgorithm;
////     //   processingTimesC = generator.loaddata("pliki testowe//ta001.txt");
////
////        int processingTimesNeh[MAX_JOBS][MAX_MACHINES];
////        int optimalOrder[MAX_JOBS];
////
////        int bestMakespan = 9999999;
////        int bestPerm[MAX_JOBS];
////        int bestPermSize = 0;
////        int perm[MAX_JOBS];
////        int currentPerm[MAX_JOBS];
////
////       // generator.convertVectorToArray(processingTimesC, processingTimesNeh, numJobs, numMachines);
////
//////        cout << "\n\n"
//////                "_______________________________________\n"
//////                "Wygenerowana tablica:\n\n";
//////
//////        printVector(processingTimesC);
////
////
////       if(nrPliku == -1){
////            processingTimesC = generator.generateRandomData(1,10);
////            generator.convertVectorToArray(processingTimesC, processingTimesNeh, numJobs, numMachines);
////            cout << "\n_______________________________________\n"
////                    "   Wygenerowana tablica:\n"
////                    "_______________________________________\n";
////            printVector(processingTimesC);
////            cout << "_______________________________________\n";
////
////       }
////       else {
////           string fileName;
////           if (nrPliku < 10) {
////               fileName = "pliki testowe//ta00" + nrPliku;
////           }
////           else if (nrPliku < 91) {
////               fileName = "pliki testowe//ta0" + nrPliku;
////
////           }
////           else cout << "Bledny numer pliku";
////
////           fileName += ".txt";
////           cout<<fileName;
////           processingTimesC = generator.loaddata(fileName);
////
////
////       }
////
////        while(true){
////            cout<<"\n\nWybierz algorytm:\n";
////            cout<<"1. Algorytm NEH w C++"<<endl;
////            cout<<"2. Algorytm NEH w assemblerze"<<endl;
////            cout<<"3. Algorytm Branch and Bound w C++"<<endl;
////            cout<<"4. Algorytm Branch and Bound w assemblerze"<<endl;
////            cout<<"0. Zmien liczbe zadan i maszyn"<<endl;
////            int choice;
////            int makespan;
////            cin>>choice;
////            switch (choice) {
////                case 1: break;
////                case 2: break;
////            }
////
////            switch (choice) {
////                case 0:
////                    return;
////                case 1: {
////                    vector<int> optimalOrder = nehAlgorithm(processingTimesC);
////                    makespan = calculateMakespan(processingTimesC, optimalOrder); //Calculate makespan z neh
////                    cout << "Optimal job order: ";
////                    for (int job: optimalOrder) {
////                        cout << job << " ";
////                    }
////                    cout << endl;
////                    cout << "Total makespan: " << makespan;
////                    cout << endl;
////
////                    break;
////                }
////                case 2:
////                    neh_algorithm(processingTimesNeh,numJobs,numMachines, optimalOrder );
////                    printf("\nOptimal job order: ");
////                    for (int i = 0; i < numJobs; ++i) {
////                        printf("%d ", optimalOrder[i] );
////                    }
////                    printf("\n");
////                    cout << "Total makespan: " << makespan;
////                    cout << endl;
////
////                    break;
////                case 3: {
////                    vector<vector<int>> result = bbAlgorithm.branchAndBound1(processingTimesC);
////                    cout << "Najlepsza permutacja: ";
////                    for (int job: result[0]) {
////                        cout << job << " ";
////                    }
////                    cout << "\nBest makespan: " << result[1][0] << endl;
////                }
////                    break;
////                case 4:{
////                    int ** processingTimesPOinter = generator.convertToPointer(processingTimesC);
////                    branchAndBound(perm, 0, processingTimesPOinter, numJobs, numMachines, &bestMakespan, bestPerm, &bestPermSize, currentPerm, 0);
////                    cout << "Best permutation: ";
////                    for (int i : bestPerm) cout << i << " ";
////                    cout << "\nBest makespan: " << bestMakespan << endl;
////                    break;
////                }
////                default:
////                    break;
////
////            }
////
////        }
////
////    }
//
//private:
//    void inputData(){
//        while(true){
//            int choice = -1;
//            int nrPliku = 1;
//            cout << "Wybierz sposób generowania danych;\n";
//            cout << "1. Wczytaj z pliku\n";
//            cout << "2. Wygeneruj tablice\n";
//            cin >> choice;
//
//            switch (choice) {
//                case 1: {
//                    cout << "Podaj numer pliku: ";
//                    cin >> nrPliku;
//                    menu(1,1);
//                    break;
//                }
//                case 2:{
//                    cout<<"Podaj liczbe zadan: "<<endl;
//                    int numJobs = 7;
//                    cin>>numJobs;
//                    cout<<"Podaj liczbe maszyn: "<<endl;
//                    int numMachines = 4;
//                    cin>>numMachines;
//                    cout << "test1";
//                    menu(4, 7);
//                    break;}
//                default: {
//                    cout << "Podano bledny numer";
//                break; }
//            }
//
//        }
//    }
//
//
////    void inputData(){
////        while(true){
////
////
////
////
////            cout<<"Podaj liczbe zadan: "<<endl;
////            int numJobs;
////            cin>>numJobs;
////            cout<<"Podaj liczbe maszyn: "<<endl;
////            int numMachines;
////            cin>>numMachines;
////            menu(numJobs, numMachines);
////
////        }
////    }
//
//
//};
//#endif //OIAK_PROJEKT_MENU_H

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
        Timer timer;
        uint64_t time = 0;
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
           // std::cout<<"4. Algorytm Branch and Bound w assemblerze"<<std::endl;
            std::cout<<"0. Zmien liczbe zadan i maszyn"<<std::endl;
            int choice;
            int makespan;
            std::cin>>choice;
            switch (choice) {
                case 0:
                    return;
                case 1: {
                    timer.start();
                    std::vector<int> optimalOrder = nehAlgorithm(processingTimesC);
                    timer.stop();
                    time = timer.timeperiod();
                    makespan = calculateMakespan(processingTimesC, optimalOrder); //Calculate makespan z neh
                    std::cout << "Optimal job order: ";
                    for (int job: optimalOrder) {
                        std::cout << job << " ";
                    }
                    std::cout << std::endl;
                    cout << "Total makespan: " << makespan;
                    cout << endl;
                    cout << "Time: " << time/1000 << " [mikro_s]\n";
                    break;
                }
                case 2:
                    time = 0;
                    timer.start();
                    neh_algorithm(processingTimesNeh,numJobs,numMachines, optimalOrder );
                    timer.stop();
                    time = timer.timeperiod();

                    printf("\nOptimal job order: ");
                    for (int i = 0; i < numJobs; ++i) {
                        printf("%d ", optimalOrder[i] );
                    }
                    printf("\n");
                    cout << "Total makespan: " << makespan;
                    cout << endl;
                    cout << "Time: " << time/1000 << " [mikro_s]\n";
                    break;
                case 3: {
                    time = 0;
                    timer.start();
                    vector<vector<int>> result = bbAlgorithm.branchAndBound1(processingTimesC);
                    timer.stop();
                    time = timer.timeperiod();
                    cout << "Najlepsza permutacja: ";
                    for (int job: result[0]) {
                        cout << job << " ";
                    }
                    cout << "\nBest makespan: " << result[1][0] << endl;
                }
                    cout << "Time: " << time/1000 << " [mikro_s]\n";
                    break;
//                case 4:
//                    branchAndBound(perm, 0, processingTimesPOinter, numJobs, numMachines, &bestMakespan, bestPerm, &bestPermSize, currentPerm, 0);
//                    cout << "Best permutation: ";
//                    for (int i : bestPerm) cout << i << " ";
//                    cout << "\nBest makespan: " << bestMakespan << endl;
//                    break;
                default:
                    break;

            }

        }

    }
public:
    void inputData(){
        while(true){
            std::cout<<"Podaj liczbe zadan: "<<std::endl;
            int numJobs;
            std::cin>>numJobs;
            std::cout<<"Podaj liczbe maszyn: "<<std::endl;
            int numMachines;
            std::cin>>numMachines;
            menu(numJobs, numMachines);

        }
    }
};
#endif //OIAK_PROJEKT_MENU_H