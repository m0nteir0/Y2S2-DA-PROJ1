#include "Interface.h"
#include <iostream>
#include <regex>
#define DEFAULT_STATIONS "../Data/Project1Data/stations.csv"
#define DEFAULT_NETWORKS "../Data/Project1Data/networks.csv"
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
 * 2 - vector<string> stationPairs() - T2.2
 * 3 - vec<string> topM(int k) e vec<string> topD(int k) - T2.3
 * 4 - int nrTrainsArriving(station) - T2.4
 *
 * costs:
 * 1 - vector<int> maxTrainsCost() - T3.1
 *
 * subgraph:
 * 1 - vector<int> maxTrainsSubgraph() - T4.1
 * 2 - vector<string> topKSubgraph(int k) - T4.2
 *
 */


Interface::Interface() = default;

/**
 * Função imprime o menu inicial que permite ao utilizador escolher entre as opções: ler ficheiros, ver créditos ou sair do programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::welcomePage() {
    cout << endl << "=========WELCOME PAGE=========" << endl;
    cout << endl << "Options:\n\t1-Read files\n\t2-Credits\n\te-Exit"<<endl;
    string input;
    while (true){
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {

            switch (input[0]) {
                case ('1'):
                    readFiles();
                    return welcomePage();
                case ('2'):
                    credits();
                    return welcomePage();
                case ('e'):
                    return exitProgram();
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
void Interface::readFiles() {
    cout << endl << "=========READ FILES=========" << endl;
    cout << endl;
    cout << "Which files do you want to read?" << endl;
    cout << endl << "Options:\n\t1-Default files\n\t2-Custom files\n\te-Exit"<<endl;
    string input;

    string input2;

    while (true){
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {
            switch (input[0]) {
                case ('1'):
                    //d_.readStations(DEFAULT_STATIONS);
                    //d_.readNetworks(DEFAULT_NETWORKS);
                    mainMenu();
                case ('2'):
                    cout << endl << "Insert custom station file path:" << endl;
                    cout << endl << "If you want default, write '-':" << endl;
                    getline(cin, input2);


                    /*if (in != "-") d_.readStations(in);
                    else d_.readStations(DEFAULT_STATIONS);*/

                    cout << endl << "Insert custom network file path:" << endl;
                    cout << endl << "If you want default, write '-':" << endl;
/*
                if (in != "-") d_.readNetworks(in);
                else d_.readNetworks(DEFAULT_NETWORKS);*/

                    mainMenu();

                case ('e'):
                    return exitProgram();
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
    cout << endl << "=========MAIN MENU=========" << endl;
    cout << endl;

    cout << endl << "I want to get informations regarding:" << endl;
    cout << endl << "Options:\n\t1-Full railway capacity\n\t2-Costs (depending on service type)\n\t3-Considering maintenance and line failures\n\te-Exit"<<endl;
    string input;
    while (true){
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {

            switch (input[0]) {
                case ('1'):
                    full();
                    return mainMenu();
                case ('2'):
                    costs();
                    return mainMenu();
                case ('3'):
                    subgraph();
                    return mainMenu();
                case ('e'):
                    return exitProgram();
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}


void Interface::full() {
    cout << endl << "=========FULL RAILWAY NETWORK MENU=========" << endl;
    cout << endl << "I want to get informations regarding:" << endl;
    cout << endl << "Options:\n\t"
                    "1-Maximum number of trains that can simultaneously travel between two specific stations\n\t"
                    "2-Which pair(s) of stations require the most amount of trains [when taking full advantage of the existing network capacity]\n\t"
                    "3-Top-k municipalities and/or districts, regarding their transportation needs\n\t"
                    "4-Maximum number of trains that can simultaneously arrive at a given station"
                    "b-Back\n\te-Exit"<<endl;
    string input;
    while (true){
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {

            //for functions
            string os;
            string ds;
            vector <string> vec;
            char in;
            string k;
            int k2;
            string station;
            int res;
            int source, target;
            //---------------

            switch (input[0]) {
                case ('1'):
                    cout << "Type origin station:" << endl;
                    getline(cin >> ws, os);
                    cout << "Type destination station:" << endl;
                    getline(cin >> ws, ds);
                    source = d_.getNames()[os];
                    target = d_.getNames()[ds];
                    res = d_.getMaxFlow(source, target);
                    cout << "The maximum number of trains that can simultaneously travel between" << os << " and " << ds
                         << "is:" << res << endl;
                    lastPage();
                    return full();

                case ('2'):
                    //vec = stationPairs();
                    cout << "The pair(s) are:" << endl << vec[0]; //tratar depois
                    lastPage();
                    return full();
                case ('3'):
                    cout << "Choose an option" << endl << "1-Municipalities" << endl << "2-Districts" << endl;
                    cin >> in;
                    cout << "Choose the number of places for the 'top' station list: " << endl;
                    cin >> k;
                    k2 = stoi(k);

                    if (k2 < 0) cout << endl << "Not a valid number" << endl;

                    switch (in) {
                        case ('1'): //vec = topM(k2);
                            break;
                        case ('2'): // vec = topD(k2);
                            break;
                        default:
                            cout << endl << "Not a valid option" << endl;
                    }

                    cout << "The top is: " << endl;
                    for (int i = 0; i < vec.size(); i++) {
                        cout << "-" << vec[i] << endl;
                    }

                    lastPage();
                    return full();
                case ('4'):
                    cout << "Type destination station:" << endl;
                    getline(cin >> ws, station);
                    //res = nrTrainsArriving(station);
                    cout << "The maximum number of trains that can simultaneously arrive at " << station << " is: "
                         << res;
                    lastPage();
                    return full();
                case ('e'):
                    return exitProgram();
                case ('b'):
                    return mainMenu();
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}

void Interface::costs() {
    cout << endl << "=========COSTS REGARDING SERVICE TYPE (standard or alpha pendular) MENU=========" << endl;
    cout << endl << "Options:\n\t1-Maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company"<< endl;
    string input;
    while (true) {
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {
            //for functions:
            vector<int> res;

            switch (input[0]) {

                case ('1'):
                    //res = maxTrainsCost;
                    cout << "The max nr of trains is " << res[0] << "with the minimum cost of" << res[1] << endl;
                    lastPage();
                    return costs();
                case ('e'):
                    return exitProgram();
                case ('b'):
                    return mainMenu();
                default:
                    cout << endl << "Not a valid option" << endl;
            }

        }
    }
}


void Interface::subgraph() {
    cout << endl << "=========RAILWAY NETWORK WITH POSSIBLE LINE FAILURES MENU=========" << endl;


    cout << endl << "Do you want to type the affected LINE(S) or the affected STATION(S) to be cut of the railway network?" << endl;
    cout << endl << "Options:\n\t1-Lines\n\t2-Stations" << endl;

    string input0;
    cout << "Choose option:";
    getline( cin, input0);
    cout << endl << "Input: " << input0 << endl;

    if(input0.size()>1){
        cout << endl << "Please, only type one of the characters in the options described above." << endl;
    }

    else {

        if (input0[0] == 1) {
            cout << endl << "Type the affected lines: " << endl; //ver como receber isto depois
            //
        } else {
            cout << endl << "Type the affected stations:" << endl; //ver como receber isto depois
        }
    }


    cout << endl << "Options:\n\t1-Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity\n\t2-Top-k most affected stations for each segment to be considered\n\tb-Back\n\te-Exit" << endl;
    string input;

    while (true) {
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {
            vector<int> res;
            string k;
            int k2;
            vector <string> vec;

            switch (input[0]) {

                case ('1'):
                    //res = maxTrainsSubgraph;
                    cout << "The max nr of trains is " << res[0] << "with the minimum cost of" << res[1] << endl;
                    return subgraph();

                case ('2'):
                    cout << "Choose the number of places for the 'top' station list: " << endl;
                    cin >> k;
                    k2 = stoi(k);
                    if (k2 < 0) cout << endl << "Not a valid number" << endl;

                    //vec = topKSubgraph(int k);
                    cout << "The top is: " << endl;
                    for (int i = 0; i < vec.size(); i++) {
                        cout << "-" << vec[i] << endl;
                    }
                    lastPage();
                    return subgraph();

                case ('e'):
                    return exitProgram();
                case ('b'):
                    return mainMenu();
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }

    }
}


/**
 * Função mostra os autores do programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::credits() const {
    cout << endl << "=========CREDITS=========" << endl;
    cout << endl;
    cout << "Made by:" << endl;
    cout << "Tomas Gaspar, up202108828" << endl;
    cout << "Guilherme Monteiro, up202108668" << endl;
    cout << "Sofia Sa, up202108676" << endl;
    cout << endl << endl << "Options:\n\tb-Back\n\te-Exit"<< endl;
    string input;
    while (true) {
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {

            switch (input[0]) {
                case ('b'):
                    return;
                case ('e'):
                    return exitProgram();
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}

/**
 * Função que representa a ultima pagina do menu. Dispoe de duas ultimas opções - voltar atrás e fechar o programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::lastPage() const {
    cout << endl << endl;
    cout << endl << "Options:\n\tb-Back\n\te-Exit"<<endl;
    string input;
    while (true){
        cout << "Choose option:";
        getline( cin, input);
        //cout << endl << "Input: " << input << endl;
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }

        else {
            switch (input[0]) {
                case ('b'):
                    return;
                case ('e'):
                    return exitProgram();
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}



/**
 * Função que imprime ao utilizador a saída do programa.
 *
 * COMPLEXIDADE: O(1).
 */
void Interface::exitProgram() const {
    cout << endl << "Exiting program..." << endl;
    throw 200;
}