//
// Created by adirr on 08/05/2022.
//

#include <sstream>
#include <array>
#include <deque>
#include "Terminal.h"
#include "../Utils/UtilsFunctions.h"

deque<string> SplitCommandToWords(const string &cmd) {
    stringstream cmd_ss(cmd);
    string word;
    deque<string> cmd_words;
    while (!cmd_ss.eof()) {
        cmd_ss >> word;
        cmd_words.push_back(word);
    }
    return cmd_words;
}

TerminalCommand Terminal::GetNextTerminalCommand() {
    cout << "[input]";
    string command;
    getline(cin, command);
    deque<string> commandWords = SplitCommandToWords(command);
    if (!contains(possible_commands, commandWords[0]))
        throw runtime_error("Error on Terminal. Unknown Terminal Command: " + commandWords[0]);
    TerminalCommand terminalCommand;
    terminalCommand.command_title = commandWords[0];
    commandWords.pop_front();
    terminalCommand.args = commandWords;
    return terminalCommand;
}

void Terminal::ShowOutput(const string &outputLine) {
    cout << "[output]\t" << outputLine << endl;
}


