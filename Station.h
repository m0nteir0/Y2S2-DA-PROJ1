//
// Created by Guilherme Monteiro on 03/03/2023.
//

#ifndef DA_PROJECT1_STATION_H
#define DA_PROJECT1_STATION_H
#include <string>

using namespace std;
class Station {
private:
    string name, district, municipality, township, line;

public:
    //constructor
    explicit Station(string &name);
    Station(string &name, string &district, string &municipality, string &township, string &line);

    //setters
    void setName(string &name);
    void setDistrict(string &district);
    void setMunicipality(string &municipality);
    void setTownship(string &township);
    void setLine(string &line);

    //getters
    const string &getName() const;
    const string &getDistrict() const;
    const string &getMunicipality() const;
    const string &getTownship() const;
    const string &getLine() const;

};


#endif //DA_PROJECT1_STATION_H
