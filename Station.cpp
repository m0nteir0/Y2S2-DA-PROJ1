//
// Created by Guilherme Monteiro on 03/03/2023.
//

#include "Station.h"

Station::Station(string &name) : name(name) {}
Station::Station(string &name, string &district, string &municipality, string &township,string &line)
                : name(name), district(district), municipality(municipality), township(township), line(line) {}

const string &Station::getName() const {
    return name;
}

void Station::setName(string &name) {
    Station::name = name;
}

const string &Station::getDistrict() const {
    return district;
}

void Station::setDistrict(string &district) {
    Station::district = district;
}

const string &Station::getMunicipality() const {
    return municipality;
}

void Station::setMunicipality(string &municipality) {
    Station::municipality = municipality;
}

const string &Station::getTownship() const {
    return township;
}

void Station::setTownship(string &township) {
    Station::township = township;
}

const string &Station::getLine() const {
    return line;
}

void Station::setLine(string &line) {
    Station::line = line;
}


