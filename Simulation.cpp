//
// Created by adirr on 08/05/2022.
//

#include "Simulation.h"
#include "Utils/FileReader.h"
#include <vector>

Simulation::Simulation(int argc, char *argv[]) {
    ParseArgs(argc, argv);
    config = FileReader::ReadConfigFile(config_file_name);
    for (const string &input_file_name: input_files) {
        try {
            FileReader::ReadInputFileAndUpdateNetwork(input_file_name, transportNetwork, config);
        }
        catch (exception &e) {
            cout << "Error on FileReader::ReadInputFileAndUpdateGraph. Reason: " << e.what() << endl;
            exit(1);
        }
    }
}

void Simulation::Start() {
    TerminalCommand cmd;
    while (true) {
        cmd = terminal.GetNextTerminalCommand();
        if (cmd.command_title == "EXIT")break;
        else if (cmd.command_title == "load") {
            try {
                FileReader::ReadInputFileAndUpdateNetwork(cmd.args[0], transportNetwork, config);
            }
            catch (exception &e) {
                Terminal::ShowOutput("ERROR opening the specified file.");
            }
        } else if (cmd.command_title == "inbound") transportNetwork.inbound(cmd.args[0]);
        else if (cmd.command_title == "outbound") transportNetwork.outbound(cmd.args[0]);
        else if (cmd.command_title == "uniExpress") transportNetwork.uniExpress(cmd.args[0], cmd.args[1], config);
        else if (cmd.command_title == "multiExpress") transportNetwork.multiExpress(cmd.args[0], cmd.args[1]);
        else if (cmd.command_title == "print") transportNetwork.print(config.GetOutputFileName());

    }
}

void SetFlags(bool &found_i, bool &found_c, bool &found_o, char &inside_char, const string &current_arg) {
    /*
     * Function is used when parsing args received from terminal.
     * found_i, found_c, found_o are for indication for flags we already saw.
     * inside_char is for indication which flag args we are currently parsing.
     * current_arg is the current argument we got from command line.
     * */
    if (current_arg == "-i") {
        if (found_i) throw runtime_error("Flag -i found twice");
        inside_char = 'i';
        found_i = true;
    } else if (current_arg == "-c") {
        if (found_c) throw runtime_error("Flag -c found twice");
        inside_char = 'c';
        found_c = true;
    } else if (current_arg == "-o") {
        if (found_o) throw runtime_error("Flag -o found twice");
        inside_char = 'o';
        found_o = true;
    } else throw runtime_error("Error: Unknown argument " + current_arg);
}

void Simulation::ParseArgs(int argc, char **argv) {
    if (argc < 3) {
        cout << "Error on Simulation::parse_args. Reason: argc=" << argc << endl;
        exit(1);
    }
    string current_arg;
    bool found_i = false, found_o = false, found_c = false;
    char inside_char;
    for (int i = 1; i < argc; i++) {
        current_arg = argv[i];
        if (current_arg[0] == '-') {
            SetFlags(found_i, found_c, found_o, inside_char, current_arg);
            continue;
        }
        if (inside_char == 'i') input_files.push_back(current_arg);
        else if (inside_char == 'c') config_file_name = current_arg;
        else if (inside_char == 'o') output_file_name = current_arg;
    }
    if (input_files.empty()) throw runtime_error("Error on Simulation::parse_args: Not received any input_files");
}


