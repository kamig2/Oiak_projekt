//
// Created by grons on 08.06.2024.
//

#ifndef OIAK_PROJEKT_FILEREADER_H
#define OIAK_PROJEKT_FILEREADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class FileReader {

public:
    int saveFile(string nazwaPliku, string zawartosc) {

        ofstream plik(nazwaPliku); // Otwarcie pliku do zapisu

        if (!plik) {
            cerr << "Nie mozna utworzyc pliku." << endl;
            return 1;
        }

        plik << zawartosc; // Zapisanie zawartosci do pliku
        plik.close(); // Zamknięcie pliku


        return 0;
    }


};


#endif //OIAK_PROJEKT_FILEREADER_H
