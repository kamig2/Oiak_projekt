//
// Created by grons on 11.06.2024.
//

#ifndef OIAK_PROJEKT_TEST_H
#define OIAK_PROJEKT_TEST_H

#include "Timer.h"
#include "DataGenerator.h"
#include "BbAlgorithm.h"
#include "FileReader.h"
#include "NehAlgorithm.h"

using namespace std;
const int MIN_TIME = 1;
const int MAX_TIME = 10;


extern "C" void neh_algorithm(int processingTimes[MAX_JOBS][MAX_MACHINES],
                              int numJobs, int numMachines,
                              int optimalOrder[MAX_JOBS]);

extern "C" void branchAndBound( int* perm, int permSize,
                                int **processingTimes, int numJobs,
                                int numMachines, int* bestMakespan,
                                int* bestPerm, int* bestPermSize,
                                int* currentPerm, int currentPermSize);

    int test(int repNum, int code, int algorithmType, int numJobs, int numMachines,string fileName/*, int minTime, int maxTime*/){
        Timer timer;
//        DataGenerator dataGenerator = DataGenerator(numJobs, numMachines);

        uint64_t time = 0;
        float totalTime = 0;

        FileReader fileReader;
        BbAlgorithm bbAlgorithm = BbAlgorithm();
        vector<vector<int>> processingTimes = fileReader.loadFromFile(fileName);

        string doPliku;
        string nazwaPliku;

        doPliku += "{\n";

        doPliku += "\"Jezyk\":";
        if (code == 0){
            doPliku += "\"cpp\", \n";
            nazwaPliku += "_cpp";
        } else {
            doPliku += "\"asm\", \n";
            nazwaPliku += "_asm";
        }

        doPliku += "\"Nazwa_algorytmu\":";
        if(algorithmType == 0){
            doPliku = "\"bb\", \n";
            nazwaPliku = "bb";
        } else {
            doPliku = "\"neh\"";
            nazwaPliku = "neh";
        }

        doPliku += R"("Dane":")";

        for(int i = 0; i < repNum; i++){
            cout << numJobs<<","<<numMachines<<":";
            // time  = bbAlgorithm.bb_time(processingTimes);
            if(code == 0) {
                if(algorithmType == 0){
                    time  += bbAlgorithm.bb_time(processingTimes);
                    cout << time << endl;
                }
                else {
                    time += neh_time(processingTimes);
                }
            }else if(code == 1){
                if(algorithmType== 0){
                    // to samo dla ASM
                }
            }
        }

        totalTime = time / repNum;
        doPliku += "(" + to_string(numJobs) + "-" + to_string(numMachines) + "," + to_string(totalTime) + ")";

        doPliku += "\n}\n";
        cout << doPliku;

        nazwaPliku = "../OIAK/wyniki/" + nazwaPliku + ".json";
        fileReader.saveFile(nazwaPliku, doPliku);




        /*cout << "Czasy przetwarzania: " << endl;
        cout << "---------------------" << endl;
        for(int i = 0; i < numJobs; i++){
            for(int j = 0; j < numMachines; j++){
                cout << processingTimes[i][j] << " ";
            }
            cout << endl;
        }*/
        timer.start();
        bbAlgorithm.solve(processingTimes);
        timer.stop();
        return timer.timeperiod();
    }

    void interatingThroughtFiles(){
        //dodać pętle iterującą po nazwach plików z danymi
    }




#endif //OIAK_PROJEKT_TEST_H
