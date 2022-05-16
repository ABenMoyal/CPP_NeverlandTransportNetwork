cmake_minimum_required(VERSION 3.21)
project(hw2)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw2 main.cpp Utils/FileReader.cpp Utils/FileReader.h Graph/Graph.cpp Graph/Graph.h Utils/Config.cpp Utils/Config.h Utils/UtilsFunctions.h Simulation.cpp Simulation.h Terminal/TermianlCommand.h Terminal/Terminal.cpp Terminal/Terminal.h TransportNetwork/TransportNetwork.cpp TransportNetwork/TransportNetwork.h Utils/IOStructs.h)
