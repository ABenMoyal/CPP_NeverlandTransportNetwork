//
// Created by adirr on 02/05/2022.
//

#include <fstream>
#include <sstream>
#include "FileReader.h"
#include "UtilsFunctions.h"

bool ValidateOneSpace(ifstream &file) {
    // used in ReadConfig function. validating existence of 1 space character (with digit afterwards).
    char c;
    if (file.eof()) {
        cout << "FileReader::ValidateOneSpace: expected for ' ' but found EOF" << endl;
        return false;
    }
    file.get(c);
    if (c != ' ') {
        cout << "FileReader::ValidateOneSpace: expected for ' ' but found '" << c << "'." << endl;
        return false;
    }
    if (!isdigit((char) file.peek())) {
        cout << "FileReader::ValidateOneSpace: expected for digit but found '" << (char) file.peek() << "'." << endl;
        return false;
    }
    return true;
}

array<string, 3> ReadLineFromInputFile(ifstream &input_file, const string &input_file_name) {
    // TODO: Clear all printing
    string source, dest, line, extra_data;
    int duration;
    char c = 'c';
    getline(input_file, line);
//    cout << "line = " << line << endl;
    if (line.empty()) throw runtime_error("found empty line in: " + input_file_name);
    stringstream ss(line);
    ss >> noskipws;
    ss >> source;
//    cout << "s: " << source << endl;
    if (source.empty()) throw runtime_error("ReadLineFromInputFile: Missing information");
    ss >> c;
    if (c != '\t') throw runtime_error("expected for '\\t' but found: '" + to_string(c) + "'");
    ss >> dest;
//    cout << "d: " << dest << endl;
    ss >> c;
    if (c != '\t') throw runtime_error("expected for '\\t' but found: '" + to_string(c) + "'");
    ss >> duration;
//    cout << "duration: " << duration << endl;
    ss >> skipws >> extra_data;
    if (!extra_data.empty()) throw runtime_error("expected for '\\n' but found: '" + extra_data + "'");
    return {source, dest, to_string(duration)};
}

bool ValidateInputFileName(const string &file_name, const Config &config) {
    return any_of(config.GetVehicles().begin(), config.GetVehicles().end(),
               [file_name](const string &vehicle) { return file_name.find(vehicle) == 0; });
}

void FileReader::ReadInputFileAndUpdateGraph(const string &file_name, Graph &graph_to_update, const Config &config) {
    if(!ValidateInputFileName(file_name, config)){
        // TODO: ERROR
        cout << "FileReader::ReadInputFileAndUpdateGraph: Filename is invalid " << file_name << "." << endl;
        exit(1);
    }
    ifstream input_file(file_name);
    if (!input_file) {
        // TODO: ERROR
        cout << "FileReader::ReadInputFileAndUpdateGraph: Failed to open " << file_name << "." << endl;
        exit(1);
    }
    input_file >> noskipws;
    array<string, 3> data;
    while (!input_file.eof()) {
        try {
            data = ReadLineFromInputFile(input_file, file_name);
            // TODO: update graph
        }
        catch (runtime_error &e) {
            // TODO: ERROR
            cout << "ERROR on ReadLineFromInputFile. Reason: " << e.what() << endl;
            exit(1);
        }
        if (data[0].empty()) break;
    }
}

Config FileReader::ReadConfigFile(const string &config_file_name) {
    ifstream config_file(config_file_name);
    if (!config_file) {
        // TODO: ERROR
        cout << "FileReader::ReadConfigFile: Failed to open " << config_file_name << "." << endl;
        exit(1);
    }
    string line;
    string input_word;
    int input_time;
    char c;
    Config config;
    if (config_file.peek() == -1) {
        // TODO: ERROR
        cout << "FileReader::ReadConfigFile: File " << config_file_name << " is empty" << endl;
        exit(1);
    } else if (!isalpha(config_file.peek())) {
        // TODO: ERROR
        cout << "FileReader::ReadConfigFile: expected to string but found " << (char) config_file.peek() << endl;
        exit(1);
    }
    while (true) {
        config_file >> input_word;
        if (!ValidateOneSpace(config_file)) {
            // TODO: ERROR
            exit(1);
        }
        config_file >> input_time;
        if (contains(config.GetVehicles(), input_word)) config.SetVehicleStopTime(input_word, input_time);
        else if (contains(config.GetStationsTypes(), input_word)) config.SetStationTransitTime(input_word, input_time);
        else {
            cout << "FileReader::ReadConfigFile: " << input_word << " is not a vehicle and not a stop_type" << endl;
            exit(1);
        }
        if (config_file.eof()) break;
        if (config_file.peek() != '\n') {
            // TODO: ERROR
            cout << "FileReader::ReadConfigFile: expected for '\\n' but found '" << (char) config_file.peek() << "'."
                 << endl;
            exit(1);
        }

    }
    return config;
}