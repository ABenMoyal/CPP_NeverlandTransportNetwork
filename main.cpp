#include <iostream>
#include "Utils/Config.h"
#include "Utils/FileReader.h"
#include "Simulation.h"

int main(int argc, char* argv[]) {
    Simulation simulation;
    simulation.Start(argc, argv);
    cout << "Program Finished" << endl;
    return 0;
}
