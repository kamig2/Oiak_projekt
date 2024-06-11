//
// Created by grons on 08.06.2024.
//

#ifndef OIAK_PROJEKT_NEHALGORITHM_H
#define OIAK_PROJEKT_NEHALGORITHM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Timer.h"

// Struktura do przechowywania zadań wraz z ich całkowitym czasem przetwarzania
struct Task {
    int id;                     // Identyfikator zadania
    int totalProcessingTime;    // Całkowity czas przetwarzania zadania

    // Konstruktor inicjalizujący id i całkowity czas przetwarzania
    Task(int id, int totalProcessingTime) : id(id), totalProcessingTime(totalProcessingTime) {}
};

// Funkcja do porównywania zadań na podstawie ich całkowitego czasu przetwarzania
bool compareTasks(const Task& a, const Task& b) {
    return a.totalProcessingTime > b.totalProcessingTime; // Sortowanie w porządku malejącym według całkowitego czasu przetwarzania
}

// Funkcja do obliczania makespan (czasu zakończenia) dla danego porządku zadań
int calculateMakespan(const std::vector<std::vector<int>>& processingTimes, const std::vector<int>& jobOrder) {
    int numJobs = jobOrder.size();             // Liczba zadań
    int numMachines = processingTimes[0].size(); // Liczba maszyn
    std::vector<std::vector<int>> completionTime(numJobs, std::vector<int>(numMachines, 0)); // Macierz czasu zakończenia

    // Obliczanie czasu zakończenia dla każdego zadania na każdej maszynie
    for (int i = 0; i < numJobs; ++i) {
        int job = jobOrder[i];                 // Aktualne zadanie
        for (int j = 0; j < numMachines; ++j) {
            if (i == 0 && j == 0) {            // Pierwsze zadanie na pierwszej maszynie
                completionTime[i][j] = processingTimes[job][j];
            } else if (i == 0) {               // Pierwsze zadanie na pozostałych maszynach
                completionTime[i][j] = completionTime[i][j - 1] + processingTimes[job][j];
            } else if (j == 0) {               // Pozostałe zadania na pierwszej maszynie
                completionTime[i][j] = completionTime[i - 1][j] + processingTimes[job][j];
            } else {                           // Pozostałe zadania na pozostałych maszynach
                completionTime[i][j] = std::max(completionTime[i - 1][j], completionTime[i][j - 1]) + processingTimes[job][j];
            }
        }
    }

    return completionTime[numJobs - 1][numMachines - 1]; // Zwracanie całkowitego czasu zakończenia
}

// Funkcja implementująca algorytm NEH (Nawaz-Enscore-Ham)
std::vector<int> nehAlgorithm(const std::vector<std::vector<int>>& processingTimes) {
    int numJobs = processingTimes.size();      // Liczba zadań
    int numMachines = processingTimes[0].size(); // Liczba maszyn

    // Obliczanie całkowitego czasu przetwarzania dla każdego zadania
    std::vector<Task> tasks;
    for (int i = 0; i < numJobs; ++i) {
        int totalProcessingTime = 0;           // Inicjalizacja całkowitego czasu przetwarzania
        for (int j = 0; j < numMachines; ++j) {
            totalProcessingTime += processingTimes[i][j]; // Sumowanie czasu przetwarzania na wszystkich maszynach
        }
        tasks.emplace_back(i, totalProcessingTime); // Dodanie zadania do listy
    }

    // Sortowanie zadań według malejącego całkowitego czasu przetwarzania
    std::sort(tasks.begin(), tasks.end(), compareTasks);

    // Konstrukcja optymalnego porządku zadań
    std::vector<int> jobOrder;                 // Optymalny porządek zadań
    for (const auto& task : tasks) {
        int bestMakespan = INT_MAX;            // Inicjalizacja najlepszego czasu zakończenia
        int bestPosition = 0;                  // Inicjalizacja najlepszej pozycji

        // Wstawianie zadania na każdą możliwą pozycję i obliczanie makespan (czasu zakończenia)
        for (int i = 0; i <= jobOrder.size(); ++i) {
            std::vector<int> tempOrder = jobOrder; // Tymczasowy porządek zadań
            tempOrder.insert(tempOrder.begin() + i, task.id); // Wstawienie zadania na pozycję i
            int makespan = calculateMakespan(processingTimes, tempOrder); // Obliczenie czasu zakończenia

            // Znajdowanie najlepszej pozycji dla zadania w celu minimalizacji makespan
            if (makespan < bestMakespan) {
                bestMakespan = makespan;       // Aktualizacja najlepszego czasu zakończenia
                bestPosition = i;              // Aktualizacja najlepszej pozycji
            }
        }

        jobOrder.insert(jobOrder.begin() + bestPosition, task.id); // Wstawienie zadania na optymalną pozycję
    }

    return jobOrder; // Zwracanie optymalnego porządku zadań
}

uint64_t neh_time(const vector<vector<int>> &processingTimes){
    Timer timer;
    timer.start();
    nehAlgorithm(processingTimes);
    timer.stop();
    return timer.timeperiod();

}


#endif //OIAK_PROJEKT_NEHALGORITHM_H
