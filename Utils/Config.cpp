//
// Created by adirr on 04/05/2022.
//

#include "Config.h"
#include "UtilsFunctions.h"

Config::Config() = default;

Config::Config(string &output_file_name)
        : output_file_name(output_file_name) {}

Config::Config(map<VehicleName, int> &vehicle_to_stop_time) : vehicle_to_stop_time(vehicle_to_stop_time) {}

Config::Config(map<VehicleName, int> &vehicle_to_stop_time, string &output_file_name)
        : vehicle_to_stop_time(vehicle_to_stop_time), output_file_name(output_file_name) {}

void Config::SetOutputFileName(string &new_output_file_name) {
    output_file_name = new_output_file_name;
}

void Config::SetStationTransitTime(string &station, int &transit_time) {
    if (!contains(stations_types, station)) {
        // TODO: ERROR
        cout << "Config::SetStationTransitTime: " << station << " is illegal station." << endl;
        exit(1);
    }
    this->station_to_transit_time[station] = transit_time;
}

int Config::GetTransitTimeByStationName(const string &stationName) const {
    if (stationName.find("IC") == 0) return station_to_transit_time.at("intercity");
    else if (stationName.find("CS") == 0) return station_to_transit_time.at("centraal");
    else return station_to_transit_time.at("stad");
}

void Config::SetVehicleStopTime(const string &vehicle, int &stop_time) {
    if (vehicle == "bus") vehicle_to_stop_time[BUS] = stop_time;
    else if (vehicle == "tram") vehicle_to_stop_time[TRAM] = stop_time;
    else if (vehicle == "sprinter") vehicle_to_stop_time[SPRINTER] = stop_time;
    else if (vehicle == "rail") vehicle_to_stop_time[RAIL] = stop_time;
    else {
        // TODO: ERROR
        cout << "Config::SetVehicleStopTime: " << vehicle << " is illegal vehicle." << endl;
        exit(1);
    }
}
