//
// Created by adirr on 04/05/2022.
//

#ifndef HW2_CONFIG_H
#define HW2_CONFIG_H

#include <iostream>
#include <map>

using namespace std;
typedef enum {BUS, TRAM, SPRINTER, RAIL} VehicleName;

class Config {
private:
    map<VehicleName, int> vehicle_to_stop_time = {
            {BUS,      1},
            {TRAM,     2},
            {SPRINTER, 3},
            {RAIL,     5},
    };
    map<string, int> station_to_transit_time = {
            {"intercity", 15},
            {"centraal",  10},
            {"stad",      5},
    };
    array<string, 4> vehicles = {"bus", "tram", "sprinter", "rail"};
    array<string, 3> stations_types = {"intercity", "centraal", "stad"};
    string output_file_name = "output.dat";
public:
    Config();

    Config(string &output_file_name);

    Config(map<VehicleName, int> &vehicle_to_stop_time);

    Config(map<VehicleName, int> &vehicle_to_stop_time, string &output_file_name);

    void SetOutputFileName(string &output_file_name);

    void SetVehicleStopTime(const VehicleName &vehicle, int &stop_time);
    void SetVehicleStopTime(const string &vehicle, int &stop_time);

    void SetStationTransitTime(string &station, int &transit_time);

    const string &GetOutputFileName() { return output_file_name; }

    const array<string , 4> &GetVehicles() const { return vehicles; }

    const array<string, 3> &GetStationsTypes() const { return stations_types; }

    int GetStopTimeByVehicle(const VehicleName vehicleName) const { return vehicle_to_stop_time.at(vehicleName); }

    int GetTransitTimeByStationName(const string& stationName) const;

    friend ostream &operator<<(ostream &os, Config &config) {
        map<VehicleName , int>::iterator it;
        os << "Config: " << endl << "vehicle_to_stop_time = ";
        for (it = config.vehicle_to_stop_time.begin(); it != config.vehicle_to_stop_time.end(); it++) {
            os << it->first << ": " << it->second << ", ";
        }
        map<string , int>::iterator iter;
        os << endl << "station_to_transit_time = ";
        for (iter = config.station_to_transit_time.begin(); iter != config.station_to_transit_time.end(); iter++) {
            os << it->first << ": " << it->second << ", ";
        }
        os << endl;
        os << "output_file_name = " << config.output_file_name << endl;
        return os;
    }

};


#endif //HW2_CONFIG_H
