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
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sys/resource.h>
#include <sys/time.h>
#include <malloc.h>

//#include <resource/h>

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



int test(int repNum, int code, int algorithmType,string fileName,int i){
    int numMachines,numJobs;
    Timer timer;
    DataGenerator generator = DataGenerator(numJobs, numMachines);

    uint64_t time = 0;
    float totalTime = 0;

    FileReader fileReader;
    BbAlgorithm bbAlgorithm = BbAlgorithm();
    vector<vector<int>> processingTimesC = generator.loaddata(fileName,numJobs,numMachines);
    int processingTimesNeh[MAX_JOBS][MAX_MACHINES];
    int optimalOrder[MAX_JOBS];
    generator.convertVectorToArray(processingTimesC, processingTimesNeh, numJobs, numMachines);

    string doPliku;
    string nazwaPliku = "";

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
        doPliku += "\"bb\", \n";
        nazwaPliku += "bb";
    } else {
        doPliku += "\"neh\"";
        nazwaPliku += "_neh";
    }
    nazwaPliku += "_" + to_string(i);
    doPliku += ",\n";


    doPliku += R"("Dane":")";

    for(int i = 0; i < repNum; i++){
        //cout << numJobs<<","<<numMachines<<":";
        // time  = bbAlgorithm.bb_time(processingTimesC);
        if(code == 0) {
            if(algorithmType == 0){
              //  time  += bbAlgorithm.bb_time(processingTimesC);
              //  cout << time << endl;
            }
            else {
                time += neh_time(processingTimesC);

            }
        }else if(code == 1){
            if(algorithmType== 0){
                // to samo dla ASM
            }else{
                Timer timer;
                timer.start();
                neh_algorithm(processingTimesNeh,numJobs,numMachines,optimalOrder);
                timer.stop();
                time += timer.timeperiod();
            }
        }
    }


    totalTime = time / repNum;

    string wyswietl = "(" + to_string(numJobs) + "-" + to_string(numMachines) + "," + to_string(totalTime) + ")";
    cout << wyswietl;

    doPliku += "(" + to_string(numJobs) + "-" + to_string(numMachines) + "," + to_string(totalTime) + ")\"";

    doPliku += "\n}\n";
    //cout << doPliku;

    nazwaPliku = "..//wyniki//" + nazwaPliku + ".json";
    fileReader.saveFile(nazwaPliku, doPliku);


    return timer.timeperiod();//czy ta funkcja musi coś zwracac czy możę być void?
}

void interatingThroughtFiles() {
    std::string fileName;
    for (int i = 1; i <= 90; i++) {
        if (i < 10) {
            fileName = "pliki testowe//ta00" + to_string(i) + ".txt";
        } else {
            fileName = "pliki testowe//ta0" + to_string(i) + ".txt";
        }
        for (int code = 0; code < 2; code++) {
            for (int algorithmType = 1; algorithmType < 2; algorithmType++) {//wywołanie testów tylko dla neh
                test(10,code,algorithmType,fileName, i);

            }
        }


    }
}
void interatingThroughtBigFiles() {
    std::string fileName;
    for (int i = 91; i <= 120; i++) {
        if (i < 100) {
            fileName = "pliki testowe//ta0" + to_string(i) + ".txt";
        } else {
            fileName = "pliki testowe//ta" + to_string(i) + ".txt";
        }
        for (int code = 0; code < 2; code++) {
            for (int algorithmType = 1; algorithmType < 2; algorithmType++) {//wywołanie testów tylko dla neh
                test(10,code,algorithmType,fileName, i);
            }
        }
    }
}
#endif //OIAK_PROJEKT_TEST_H