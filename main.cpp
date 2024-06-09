#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include "BbAlgorithm.h"
#include "DataGenerator.h"
#include "Timer.h"
#include "FileReader.h"
#include "NehAlgorithm.h"

#define MAX_JOBS 100
#define MAX_MACHINES 100

using namespace std;
const int MIN_TIME = 1;
const int MAX_TIME = 10;

/* Do zrobienia:
 * - ujednolicic dane wejsciowe
 * - w branch and bound sprawdzic jak zadziajaja zakresy jak z neh
 * - mozliwosc wyboru liczby zadan i maszyn
 * - menu (wybor algorytmu, l zad i l masz
 * - uporzadkowac kod - prostszy main
 *          wyswietlenie czasu, permutacji + makespan(?))
 * - sprawdzic algorytmy (wyniki)
 * */


extern "C" void calculateMakespan(int* perm, int permSize,
                       int** processingTimes, int numJobs,
                       int numMachines, int* makespan);

extern "C" int lowerBound(int* perm, int permSize,
               int** processingTimes, int numJobs,
               int numMachines);
extern "C" void branchAndBound(int* perm, int permSize,
                    int** processingTimes, int numJobs,
                    int numMachines, int* bestMakespan,
                    int* bestPerm, int* bestPermSize,
                    int* currentPerm, int currentPermSize);

extern "C" void neh_algorithm(int processingTimes[MAX_JOBS][MAX_MACHINES],
                              int numJobs, int numMachines,
                              int optimalOrder[MAX_JOBS]);


// Wywolanie asemblera
int main() {
//    vector<vector<int>> processingTimes1 = { {2, 3, 2}, {4, 10, 3}, {3, 2, 4} };
//    vector<int> result = nehAlgorithm(processingTimes1);

    Timer timer;
    uint64_t time = 0;
    BbAlgorithm bbAlgorithm;
    int processingTimesArray[3][3] = { {15, 3, 2}, {4, 10, 3}, {3, 2, 4} };
    int* processingTimes[3];
    for (int i = 0; i < 3; ++i) {
        processingTimes[i] = processingTimesArray[i];
    }

    int numJobs = 3;
    int numMachines = 3;
    int bestMakespan = 9999999;
    int bestPerm[3];
    int bestPermSize = 0;
    int perm[3];
    int currentPerm[3];

    timer.start();
    branchAndBound(perm, 0, processingTimes, numJobs, numMachines, &bestMakespan, bestPerm, &bestPermSize, currentPerm, 0);
    timer.stop();
    time = timer.timeperiod();

    printf("Branch and bound\n");   // ujednolicic wyswietlanie
    cout << "Czas asm: " << time;
    printf("\nBest permutation: ");
    for (int i = 0; i < bestPermSize; ++i) {
        printf("%d ", bestPerm[i]);
    }
    printf("\nBest makespan: %d\n", bestMakespan);

    /************************************************************/


    int processingTimesNEH[MAX_JOBS][MAX_MACHINES] = {

            {15, 3,  2},
            {4, 10, 3},
            {3, 2,  4}
    };
    int optimalOrder[MAX_JOBS];

    cout << "Algorytm NEH: \n";

    time = 0;
    timer.start();
    neh_algorithm(processingTimesNEH,numJobs,numMachines, optimalOrder );
    timer.stop();
    time = timer.timeperiod();
    cout << "czas: " << time;
    printf("\nOptimal job order: ");
    for (int i = 0; i < numJobs; ++i) {
        printf("%d ", optimalOrder[i] ); // +1 aby używać numeracji zadań od 1
    }
    printf("\n");

    timer.start();
    // bbAlgorithm.branchAndBound1(); tu trzeba bedzie dobrze parametry dodac
    timer.stop();
    time = timer.timeperiod();






    return 0;
}


int test(int repNum, int code, int algorithmType, int numJobs, int numMachines, int minTime, int maxTime){
    Timer timer;
    DataGenerator dataGenerator = DataGenerator(numJobs, numMachines);

    uint64_t time = 0;
    float totalTime = 0;

    BbAlgorithm bbAlgorithm = BbAlgorithm();
    vector<vector<int>> processingTimes = dataGenerator.generateRandomData(MIN_TIME, MAX_TIME);
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
                // time = nehAlgorithm.neh_time(processingTimes);
            }
        }else if(code == 1){
            //tutaj to samo ale w ASM!!!
        }
    }

    totalTime = time / repNum;
    doPliku += "(" + to_string(numJobs) + "-" + to_string(numMachines) + "," + to_string(totalTime) + ")";

    doPliku += "\n}\n";
    cout << doPliku;

    FileReader fileReader;
    nazwaPliku = "../OIAK/wyniki/" + nazwaPliku + ".json";
    fileReader.saveFile(nazwaPliku, doPliku);




    cout << "Czasy przetwarzania: " << endl;
    cout << "---------------------" << endl;
    for(int i = 0; i < numJobs; i++){
        for(int j = 0; j < numMachines; j++){
            cout << processingTimes[i][j] << " ";
        }
        cout << endl;
    }
    timer.start();
    bbAlgorithm.solve(processingTimes);
    timer.stop();
    return timer.timeperiod();
}


// Menu progrmau jesli bedzie wersja konsolowa
void menu(){

}




int main1() {
    int numJobs = 5;
    int numMachines = 5;
    int repNum = 5;


    vector<vector<int>> dataSets = {
            {10, 5},    {20, 10},   {20, 20},
            {50, 5},    {50, 10},   {50,20},
            {100, 5},   {100, 10},  {100, 20},
            {200, 5},   {200,20},   {500,20}
    };
    for( int code = 0; code < 1; code++){
        for(int algorithmType = 0; algorithmType < 1; algorithmType++) {
            for (vector<int> tabs: dataSets) {
                test(repNum, code, algorithmType, tabs[0], tabs[1], MIN_TIME, MAX_TIME);
            }
        }
    }


    DataGenerator dataGenerator = DataGenerator(numJobs, numMachines);
    BbAlgorithm bbAlgorithm = BbAlgorithm();
    vector<vector<int>> processingTimes = dataGenerator.generateRandomData(MIN_TIME, MAX_TIME);
    cout << "Czasy przetwarzania: " << endl;
    cout << "---------------------" << endl;
    for(int i = 0; i < numJobs; i++){
        for(int j = 0; j < numMachines; j++){
            cout << processingTimes[i][j] << " ";
        }
        cout << endl;
    }
    bbAlgorithm.solve(processingTimes);
    return 0;
}