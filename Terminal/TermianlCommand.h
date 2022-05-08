//
// Created by adirr on 08/05/2022.
//

#ifndef HW2_TERMIANLCOMMAND_H
#define HW2_TERMIANLCOMMAND_H

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

struct TerminalCommand {
    string command_title;
    deque<string> args;

    friend ostream &operator<<(ostream &out, TerminalCommand &cmd) {
        out << "TerminalCommand: '" << cmd.command_title << "' with args: ";
        int length=(int)cmd.args.size();
        for (int i=0;i<length; i++) {
            cout << cmd.args[i];
            if(i<length-1) cout << ", ";
        }
        cout << endl;
        return out;
    }
};



#endif //HW2_TERMIANLCOMMAND_H
