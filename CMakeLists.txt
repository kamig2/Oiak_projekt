cmake_minimum_required(VERSION 3.23)
project(oiak_projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(oiak_projekt main.cpp NehAlgorithm.h DataGenerator.h Timer.h BbAlgorithm.h FileReader.h)
