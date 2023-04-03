#include "Interface.h"
#include <iostream>
#include <iomanip>

#define DEFAULT_STATIONS "../Data/Project1Data/stations.csv"
#define DEFAULT_NETWORKS "../Data/Project1Data/network.csv"

using namespace std;


/*
 * SOFIA:
 *
 * Os nomes das opções ainda estao compridos e podem ser diminuidos, se acrescentarmos uns couts a explicar as varias opções.
 * Os nomes das funções fui eu que dei provisoriamente e podem ser alteradas.
 *
 *
 * ESTRUTURA:
 *
 * welcomePage:
 * 1 - read files
 * 2 - credits
 * e - exit
 *
 * readFiles:
 * 1- default
 * 2- custom
 *
 * mainMenu:
 * 1 - full railway network (-->full)
 * 2 - costs depending on service type (-->costs)
 * 3 - with maintenance and line failures (-->subgraph)
 *
 * full:
 * 1 - int maxTrains() - T2.1
 * 2 - pair<vector<pair<Station*,Station*>>,double> stationPairs() - T2.2
 * 3 - vec<string> topM(int k) e vec<string> topD(int k) - T2.3
 * 4 - int nrTrainsArriving(int id); - T2.4
 *
 * costs:
 * 1 - vector<int> maxTrainsCost() - T3.1
 *
 * subgraph:
 * 1 - vector<int> maxTrainsSubgraph() - T4.1
 * 2 - vector<string> topKSubgraph(int k) - T4.2
 *
 */


Interface::Interface(): d_(Data()) {}

/**
 * Função imprime o menu inicial que permite ao utilizador escolher entre as opções: ler ficheiros, ver créditos ou sair do programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::welcomePage() {
    string input;
    while (true){
        cout << endl << "=========WELCOME PAGE=========" << endl;
        cout << endl << "Options:\n\t1-Read files\n\t2-Credits\n\te-Exit"<<endl;
        cout << "choose option: ";
        getline(cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            switch (input[0]) {
                case ('1'):
                    if (readFiles())
                        return;
                    else if (!d_.getStations().empty() && !d_.getNetwork().empty())
                        return mainMenu();
                    break;
                case ('2'):
                    if (credits())
                        return;
                    break;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}



/**
 * Função imprime o menu de leitura dos ficheiros, permite ao utilizador escolher entre os ficheiros "default" ou alterar os ficheiros
 *
 * COMPLEXIDADE: O(n).
 */
bool Interface::readFiles() {
    cout << endl << "=========READ FILES=========" << endl;
    cout << endl;
    cout << "Which files do you want to read?" << endl;
    cout << endl << "Options:\n\t1-Default files\n\t2-Custom files\n\tb-Back\n\te-Exit"<<endl;

    string input, stations, network;

    while (true){
        cout << "choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            switch (input[0]) {
                case ('1'):
                    d_.readStations(DEFAULT_STATIONS);
                    d_.readNetwork(DEFAULT_NETWORKS);
                    d_.findTrainSources();
                    return false;
                case ('2'):
                    cout << endl << "Insert custom station file path (if you want default, write '-') : " << endl;
                    getline(cin, stations);
                    if (stations == "-") stations = DEFAULT_STATIONS;

                    cout << endl << "Insert custom network file path (if you want default, write '-') : " << endl;
                    getline(cin, network);
                    if (network == "-") network = DEFAULT_NETWORKS;

                    d_.readStations(stations);
                    d_.readNetwork(network);
                    d_.findTrainSources();

                    return false;
                case ('b'):
                    return false;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}

/**
 * Função imprime o menu principal do programa e permite ir para os outros "sub"-menus, com as funcionalidades específicas.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::mainMenu() {
    while (true){
        cout << endl << "=========MAIN MENU=========" << endl;
        cout << endl;

        cout << "I want to get informations regarding:" << endl;
        cout << endl << "Options:\n\t1-Full railway capacity\n\t2-Costs (depending on service type)\n\t3-Considering maintenance and line failures\n\te-Exit"<<endl;
        string input;
        cout << "choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {

            switch (input[0]) {
                case ('1'):
                    if (full())
                        return;
                    break;
                case ('2'):
                    if (costs())
                        return;
                    break;
                case ('3'):
                    if (subgraph())
                        return;
                    break;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}


bool Interface::full() {
    string input;
    while (true){
        cout << endl << "=========FULL RAILWAY NETWORK MENU=========" << endl;
        cout << endl << "I want to get informations regarding:" << endl;
        cout << endl << "Options:\n\t"
                        "1-Maximum number of trains that can simultaneously travel between two specific stations\n\t"
                        "2-Which pair(s) of stations require the most amount of trains [when taking full advantage of the existing network capacity]\n\t"
                        "3-Top-k municipalities and/or districts, regarding their transportation needs\n\t"
                        "4-Maximum number of trains that can simultaneously arrive at a given station"
                        "\n\tb-Back\n\te-Exit"<<endl;
        cout << "choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            string os, ds;
            string option, k;
            int k2;
            int source, target;

            switch (input[0]) {
                case ('1'): {
                    double res;
                    map<string, int> names = d_.getNames();

                    while (true){
                        cout << "Type origin station:" << endl;
                        getline(cin, os);

                        auto s = names.find(os);
                        if (s != names.end()) {
                            source = (*s).second;
                            break;
                        }
                        else cout << "Invalid Station\n";
                    }

                    while (true) {
                        cout << "Type destination station:" << endl;
                        getline(cin, ds);

                        auto t = names.find(ds);
                        if (t != names.end()) {
                            target = (*t).second;
                            break;
                        }
                        else cout << "Invalid Station\n";
                    }

                    res = d_.getMaxFlow(queue<int>({source}), target);
                    cout << "The maximum number of trains that can simultaneously travel between " << os << " and " << ds
                         << " is: " << res << endl;
                    break;
                }
                case ('2'): {
                    pair<vector<pair<Station*,Station*>>,double> pairs;
                    pairs = d_.stationPairs();

                    if (pairs.first.size() == 1) {
                        cout << "The pair is " << pairs.first[0].first->getName() << " , " << pairs.first[0].second->getName() << " with " << pairs.second << " trains." << endl;
                    }
                    else {
                        cout << "The pairs are:" << endl;

                        for (auto p : pairs.first){
                            cout << "[" << p.first->getName() << " , " << p.second->getName() << "]" << endl;
                        }

                        cout << "with " << pairs.second << " trains." << endl;
                    }
                    break;
                }
                case ('3'):
                    cout << "Choose an option" << endl << "1-Municipalities" << endl << "2-Districts" << endl;
                    getline(cin, option);
                    cout << "Choose the number of places for the 'top' station list: " << endl;
                    getline(cin, k);

                    try {
                        k2 = stoi(k);
                    } catch (std::invalid_argument& i) {
                        cout << "You must input a number" << endl;
                        break;
                    }

                    if (k2 < 0) cout << endl << "Not a valid number" << endl;

                    if(option.size()>1){
                        cout << endl << "Please, only type one of the characters in the options described above." << endl;
                    } else {
                        switch (option[0]) {
                            case ('1'): {
                                vector<pair<string, double>> municipalities = d_.topMunicipalities();
                                cout << setw(35) << "Municipality" << setw(30) << "Average Usage" << endl;
                                for (int i = 1; i <= k2 && i <= municipalities.size(); i++){
                                    cout << fixed << setprecision(2) << setw(5) << i
                                    << setw(30) << municipalities[i-1].first << setw(30)
                                    << municipalities[i-1].second << endl;
                                }
                                break;
                            }
                            case ('2'): {
                                vector<pair<string, double>> districts = d_.topDistricts();
                                cout << setw(35) << "District" << setw(30) << "Average Usage" << endl;
                                for (int i = 1; i <= k2 && i <= districts.size(); i++){
                                    cout << fixed << setprecision(2) << setw(5) << i
                                    << setw(30) << districts[i-1].first << setw(30)
                                    << districts[i-1].second << endl;
                                }
                                break;
                            }
                            default:
                                cout << endl << "Not a valid option" << endl;
                        }
                    }
                    break;
                case ('4'): {
                    string station;
                    cout << "Type the name of the station:" << endl;
                    getline(cin, station);
                    int id;

                    if (d_.getNames().find(station) != d_.getNames().end())
                        id = d_.getNames()[station];
                    else {
                        cout << "Invalid Station\n";
                        break;
                    }

                    double res = d_.nrTrainsArriving(id);

                    cout << "The maximum number of trains that can simultaneously arrive at " << station << " is: " << res;
                    break;
                }
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                case ('b'):
                    return false;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}

bool Interface::costs() {
    while (true) {
        cout << endl << "=========COSTS REGARDING SERVICE TYPE (standard or alpha pendular) MENU=========" << endl;
        cout << endl << "Options:\n\t1-Maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company\n\tb-Back\n\te-Exit"<< endl;
        string input;
        cout << "choose option: ";
        getline( cin, input);

        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            switch (input[0]) {
                case ('1'): {
                    pair<double, double> res;
                    string os, ds;
                    int source, target;
                    map<string, int> names = d_.getNames();

                    while (true){
                        cout << "Type origin station:" << endl;
                        getline(cin, os);

                        auto s = names.find(os);
                        if (s != names.end()) {
                            source = (*s).second;
                            break;
                        }
                        else cout << "Invalid Station\n";
                    }

                    while (true) {
                        cout << "Type destination station:" << endl;
                        getline(cin, ds);

                        auto t = names.find(ds);
                        if (t != names.end()) {
                            target = (*t).second;
                            break;
                        }
                        else cout << "Invalid Station\n";
                    }

                    res = d_.maxTrainsCost(source, target);

                    cout << "\nThe max number of trains is " << res.first << " with the minimum cost of " << res.second << endl;
                    break;
                }
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                case ('b'):
                    return false;
                default:
                    cout << endl << "Not a valid option" << endl;
            }

        }
    }
}


bool Interface::subgraph() {
    while (true){
        cout << endl << "==========SUBGRAPH==========" << endl;
        cout << endl << "Options:\n\t1-Disbale segments of the network\n\t2-Analyze the reduced connectivity network\n\tb-Back\n\te-Exit"<< endl;
        string input;
        cout << "choose option: ";
        getline( cin, input);

        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            switch (input[0]) {
                case '1':
                    if (disableSegments())
                        return true;
                    break;
                case '2':
                    if (subgraphAnalyze())
                        return true;
                    break;
                case 'b':
                    return false;
                case 'e':
                    cout << endl << "Exiting program..." << endl;
                    return true;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }

}

bool Interface::disableSegments() {
    while (true) {
        cout << endl << "=========DISABLE SEGMENTS=========" << endl;
        cout << "Do you want to type the affected LINE(S) or the affected STATION(S) to be cut off the railway network?"
             << endl;
        cout << endl << "Options:\n\t1-Lines\n\t2-Stations\n\tb-Back\n\te-Exit" << endl;

        string input0;
        cout << "choose option: ";
        getline(cin, input0);
        cout << endl << "Input: " << input0 << endl;

        if (input0.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
            return subgraph();
        } else {
            switch (input0[0]) {
                case 'b':
                    return false;
                case 'e':
                    cout << endl << "Exiting program..." << endl;
                    return true;
                case '1': {
                    cout << endl << "Type the affected lines(s) and hit 'd' when done.\n\n" << endl;
                    string s1;
                    vector<int> ids;
                    vector<pair<int, int>> lines;
                    bool flag = true;

                    while (flag) {
                        cout << endl
                             << "Affected lines have 2 connecting stations. Type one of them and we will print the connecting stations.\n\n"
                             << endl;
                        cout << "Station:";
                        getline(cin, s1);
                        cout << endl;

                        if (s1 == "d") {
                            flag = false;
                        } else {
                            if (d_.getNames().find(s1) != d_.getNames().end()) {
                                int id1 = d_.getNames()[s1];
                                for (auto connection: d_.getG().findVertex(id1)->getAdj()) {
                                    cout << connection->getDest()->getId() << " - "
                                         << connection->getDest()->getStation()->getName() << "\n";
                                    ids.push_back(connection->getDest()->getId());
                                }
                                cout << "Choose the ID of the connecting station. \n";
                                string s2;
                                getline(cin, s2);
                                int id2 = stoi(s2);
                                if (find(ids.begin(), ids.end(), id2) != ids.end()) {
                                    ids.clear();
                                    lines.push_back({id1, id2});
                                } else {
                                    cout << "You didn't chose a connecting station. Please choose one of the IDs above."
                                         << endl;
                                }
                            } else cout << "Not a valid station." << endl;
                        }
                    }
                    d_.getG().disableLines(lines);
                    cout << endl << "Lines removed." << endl;
                    return false;
                }
                case '2': {
                    cout << endl << "Type the affected station(s), hit enter between stations and 'd' when done.\n\n"
                         << endl;
                    bool flag = true;
                    vector<int> v;

                    while (flag) {
                        string inp;
                        cout << "Station: ";
                        getline(cin, inp);
                        if (inp == "d") {
                            flag = false;
                        } else {
                            if (d_.getNames().find(inp) != d_.getNames().end())
                                v.push_back(d_.getNames()[inp]);
                            else cout << "Not a valid station." << endl;
                        }
                    }
                    d_.getG().disableStations(v);
                    v.clear();
                    cout << "Stations removed." << endl;
                    return false;
                }
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}

bool Interface::subgraphAnalyze() {
    while (true) {
        cout << endl << "=========ANALYZE REDUCED CONNECTIVITY=========" << endl
             << "Options:\n\t1-Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity\n\t2-Top-k most affected stations for each segment to be considered\n\tb-Back\n\te-Exit"
             << endl;
        string input;
        cout << "choose option: ";
        getline(cin, input);

        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {
            string k;
            int k2;
            vector<string> vec;

            switch (input[0]) {
                case ('1'): {
                    double res;
                    string os, ds;
                    int source, target;
                    map<string, int> names = d_.getNames();

                    while (true){
                        cout << "Type origin station:" << endl;
                        getline(cin, os);

                        auto s = names.find(os);
                        if (s != names.end()) {
                            source = (*s).second;
                            break;
                        }
                        else cout << "Invalid Station\n";
                    }

                    while (true) {
                        cout << "Type destination station:" << endl;
                        getline(cin, ds);

                        auto t = names.find(ds);
                        if (t != names.end()) {
                            target = (*t).second;
                            break;
                        }
                        else cout << "Invalid Station\n";
                    }

                    res = d_.getMaxFlowSub(queue<int>({source}), target);
                    cout << "The maximum number of trains that can simultaneously travel between "
                         << os << " and " << ds << " is: " << res << endl;
                    break;
                }
                case ('2'): {
                    cout << "Choose the number of places for the 'top' station list: " << endl;
                    getline(cin, k);

                    try {
                        k2 = stoi(k);
                    } catch (std::invalid_argument &i) {
                        cout << "You must input a number" << endl;
                        break;
                    }

                    if (k2 < 0) cout << endl << "Not a valid number" << endl;

                    vector<Result> res = d_.topAffected(k2);
                    cout << "The top is: " << endl;
                    for (int i = 0; i < res.size(); i++) {
                        if (res[i].dif == 0) {
                            cout << "No more stations were affected\n";
                            break;
                        }
                        Result r = res[i];
                        cout << (i + 1) << "- "
                             << r.s->getName() << ", " << r.s->getLine() << ": "
                             << r.dif << "%\t"
                             << r.sumFlow << "->" << r.sumFlowSub
                             << endl;
                    }
                    break;
                }
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                case ('b'):
                    return false;
                default:
                    cout << endl << "Not a valid option." << endl;
            }
        }
    }
}


/**
 * Função mostra os autores do programa.
 *
 * COMPLEXIDADE: O(n).
 */
bool Interface::credits() const {
    cout << endl << "=========CREDITS=========" << endl;
    cout << endl;
    cout << "Made by:" << endl;
    cout << "Tomas Gaspar, up202108828" << endl;
    cout << "Guilherme Monteiro, up202108668" << endl;
    cout << "Sofia Sa, up202108676" << endl;
    cout << endl << endl << "Options:\n\tb-Back\n\te-Exit"<< endl;
    string input;
    while (true) {
        cout << "choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {

            switch (input[0]) {
                case ('b'):
                    return false;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}
