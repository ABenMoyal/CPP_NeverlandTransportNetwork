#include <iostream>
#include "Utils/Config.h"
#include "Utils/FileReader.h"
#include "Simulation.h"


void print(char* format){}

template <typename T, typename... Types>
void print(char* format, T current, Types... others){
    while(true){
        if(*format=='%'){
            cout << current;
            format += 2;
            print(format, others...);
            return;
        }
        cout << *format++;
    }
}

int main(int argc, char* argv[]) {
    print("first is %d, second is %s, third are %d and %d", 4, "hello", 3, 5);
//    Simulation simulation;
//    simulation.Start(argc, argv);
//    cout << "Program Finished" << endl;
    return 0;
}
