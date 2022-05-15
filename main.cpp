#include <iostream>
#include "Utils/Config.h"
#include "Utils/FileReader.h"
#include "Simulation.h"


int main(int argc, char* argv[]) {
    Simulation simulation(argc, argv);
    simulation.Start();
    cout << "Program Finished" << endl;
    return 0;
}
