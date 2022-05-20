//
// Created by adirr on 08/05/2022.
//

#ifndef HW2_TERMINAL_H
#define HW2_TERMINAL_H

#include "TermianlCommand.h"
#include <map>
class Terminal {
private:
    array<string, 7> possible_commands = {"load", "outbound", "inbound", "uniExpress", "multiExpress", "print", "EXIT"};
    map<string, int> command_args_num = {
            {"load", 1},
            {"outbound", 1},
            {"inbound", 1},
            {"uniExpress", 2},
            {"multiExpress", 2},
            {"print", 0},
            {"EXIT", 0},
    };
public:
    TerminalCommand GetNextTerminalCommand();
    static void ShowOutput(const string& outputLine);
    static void ShowOutput(const string &outputTitle, const vector<string> &outputData, const string &msgIfEmpty);
    static void ShowOutput(const string &outputTitle, const double& outputData, const string &msgIfEmpty);
};

#endif //HW2_TERMINAL_H
