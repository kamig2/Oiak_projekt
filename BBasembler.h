//
// Created by Mela on 6/9/24.
//

#ifndef OIAK_PROJEKT_BBASEMBLER_H
#define OIAK_PROJEKT_BBASEMBLER_H
#include <iostream>
#include <stdio.h>



extern "C" void calculateBondAsm(int* perm, int permSize,
                                     int** processingTimes,
                                     int numJobs,
                                     int numMachines,
                                     int* makespan);



#endif //OIAK_PROJEKT_BBASEMBLER_H
