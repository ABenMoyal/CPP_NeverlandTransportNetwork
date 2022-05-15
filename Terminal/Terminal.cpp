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
    if (terminalCommand.args.size() != command_args_num[terminalCommand.command_title]) {
        throw runtime_error("Error on Terminal. Received wrong number of arguments for the command " +
                            terminalCommand.command_title);
    }
    return terminalCommand;
}

void Terminal::ShowOutput(const string &outputLine) {
    cout << "[output] " << outputLine << endl;
}

void Terminal::ShowOutput(const string &outputTitle, const vector<string> &outputData, const string &msgIfEmpty) const {
    cout << "[output] " << outputTitle << ": ";
    if (outputData.empty()) cout << msgIfEmpty;
    else for (const string &s: outputData) cout << s << ' ';
    cout << endl;
}


