//
// Created by adirr on 04/05/2022.
//

#ifndef HW2_CONFIG_H
#define HW2_CONFIG_H
#include <iostream>
#include <map>
using namespace std;

class Config {
private:
    map<string, int> vehicle_to_stop_time = {
            {"bus", 1},
            {"tram", 2},
            {"sprinter", 3},
            {"rail", 5},
    };
    map<string, int> station_to_transit_time = {
            {"intercity", 15},
            {"centraal", 10},
            {"stad", 5},
    };
    array<string, 4> vehicles = {"bus", "tram", "sprinter", "rail"};
    array<string, 3> stations_types = {"intercity", "centraal", "stad"};
    string output_file_name = "output.dat";
public:
    Config();
    Config(string& output_file_name);
    Config(map<string, int>& vehicle_to_stop_time);
    Config(map<string, int>& vehicle_to_stop_time, string& output_file_name);

    void SetOutputFileName(string& output_file_name);
    void SetVehicleStopTime(string& vehicle, int& stop_time);
    void SetStationTransitTime(string& station, int& transit_time);
    const array<string, 4>& GetVehicles() const { return vehicles;}
    const array<string, 3>& GetStationsTypes() const { return stations_types;}
    friend ostream& operator<<(ostream& os, Config& config){
        map<string, int>::iterator it;
        os << "Config: " << endl << "vehicle_to_stop_time = ";
        for(it = config.vehicle_to_stop_time.begin(); it != config.vehicle_to_stop_time.end(); it++){
            os << it->first << ": " << it->second << ", ";
        }
        os << endl << "station_to_transit_time = ";
        for(it = config.station_to_transit_time.begin(); it != config.station_to_transit_time.end(); it++){
            os << it->first << ": " << it->second << ", ";
        }
        os << endl;
        os << "output_file_name = " << config.output_file_name << endl;
        return os;
    }

};


#endif //HW2_CONFIG_H
