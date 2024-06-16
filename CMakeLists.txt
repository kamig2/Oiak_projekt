cmake_minimum_required(VERSION 3.23)
project(oiak_projekt)

set(CMAKE_CXX_STANDARD 20)

enable_language(ASM)

# Dodanie pliku asemblera do listy źródeł
set(SOURCE_FILES
        main.cpp
        NehAlgorithm.h
        DataGenerator.h
        Timer.h
        BbAlgorithm.h
        FileReader.h
        BBasembler.cpp
        BBasembler.h
        bb_algorithm.s  # Dodaj plik asemblera
        neh_assembler.s
        Menu.h Test.h)

# Tworzenie wykonywalnego pliku
add_executable(oiak_projekt ${SOURCE_FILES})

# Specjalne opcje dla plików asemblera
set_source_files_properties(bb_algorithm.s PROPERTIES LANGUAGE ASM)
set_source_files_properties(neh_assembler.s PROPERTIES LANGUAGE ASM)