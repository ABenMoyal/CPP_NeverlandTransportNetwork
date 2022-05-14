//
// Created by adirr on 08/05/2022.
//

#ifndef HW2_TERMINAL_H
#define HW2_TERMINAL_H

#include "TermianlCommand.h"

class Terminal {
private:
    array<string, 7> possible_commands = {"load", "outbound", "inbound", "uniExpress", "multiExpress", "print", "EXIT"};

public:
    TerminalCommand GetNextTerminalCommand();
    void ShowOutput(const string& outputLine);
};

#endif //HW2_TERMINAL_H
