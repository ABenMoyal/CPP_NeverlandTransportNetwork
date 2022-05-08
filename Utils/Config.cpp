//
// Created by adirr on 04/05/2022.
//

#include "Config.h"
#include "UtilsFunctions.h"

Config::Config() = default;

Config::Config(string &output_file_name)
        : output_file_name(output_file_name) {}

Config::Config(map<string, int> &vehicle_to_stop_time) : vehicle_to_stop_time(vehicle_to_stop_time) {}

Config::Config(map<string, int> &vehicle_to_stop_time, string &output_file_name)
        : vehicle_to_stop_time(vehicle_to_stop_time), output_file_name(output_file_name) {}

void Config::SetOutputFileName(string &new_output_file_name) {
    output_file_name = new_output_file_name;
}

void Config::SetVehicleStopTime(string &vehicle, int &stop_time) {
    if (!contains(vehicles, vehicle)) {
        // TODO: ERROR
        cout << "Config::SetVehicleStopTime: " << vehicle << " is illegal vehicle." << endl;
        exit(1);
    }
    this->vehicle_to_stop_time[vehicle] = stop_time;
}

void Config::SetStationTransitTime(string &station, int &transit_time) {
    if (!contains(stations_types, station)) {
        // TODO: ERROR
        cout << "Config::SetStationTransitTime: " << station << " is illegal station." << endl;
        exit(1);
    }
    this->station_to_transit_time[station] = transit_time;
}
