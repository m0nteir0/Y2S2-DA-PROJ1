#include "Interface.h"
#include <iostream>
#include <regex>
#define DEFAULT_STATIONS "../Data/Project1Data/stations.csv"
#define DEFAULT_NETWORKS "../Data/Project1Data/networks.csv"
using namespace std;

Interface::Interface() = default;

/**
 * Função imprime o menu inicial que permite ao utilizador escolher entre as opções: ler ficheiros, ver créditos ou sair do programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::welcomePage() {
    cout << endl << "=========WELCOME PAGE=========" << endl;
    cout << endl << "Options:\n\t1-Read files\n\t2-Credits\n\te-Exit"<<endl;
    char input;
    while (true){
        cout << "Choose option:";
        cin >> input;

        switch (input) {
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



/**
 * Função imprime o menu de leitura dos ficheiros, permite ao utilizador escolher entre os ficheiros "default" ou os ficheiros já alterados.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::readFiles() {
    cout << endl << "=========READ FILES=========" << endl;
    cout << endl;
    cout << "Which files do you want to read?" << endl;
    cout << endl << "Options:\n\t1-Default files\n\t2-Custom files\n\te-Exit"<<endl;
    char input;

    string in;

    while (true){
        cout << "Choose option:";
        cin >> input;
        switch (input) {
            case ('1'):
                d_.readStations(DEFAULT_STATIONS);
                d_.readNetworks(DEFAULT_NETWORKS);
                mainMenu();
                return readFiles();
            case ('2'):
                cout << endl << "Insert custom station file path:" << endl;
                cout << endl << "If you want default, write '-':" << endl;
                getline(cin >>ws, in);


                if (in != "-") d_.readStations(in);
                else d_.readStations(DEFAULT_STATIONS);

                cout << endl << "Insert custom network file path:" << endl;
                cout << endl << "If you want default, write '-':" << endl;

                if (in != "-") d_.readNetworks(in);
                else d_.readNetworks(DEFAULT_NETWORKS);

                mainMenu();
                return readFiles();
            case ('e'):
                return exitProgram();
            default:
                cout << endl << "Not a valid option" << endl;
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
    //explain the options
    cout << "Students -> View students info and filter lists of students." << endl;
    cout << "Classes -> View a class's number of students, capacity, and organize them." << endl;
    cout << "Timetables -> View student's/class's/UC's timetables" << endl;
    cout << "Requests -> Create and process requests" << endl;
    cout << endl << "Options:\n\t1-Students\n\t2-Timetables\n\t3-Requests\n\te-Exit"<<endl;
    char input;
    while (true){
        cout << "Choose option:";
        cin >> input;

        switch (input) {
            case ('1'):
                studentsMenu();
                return mainMenu();

            case ('2'):
                timetablesMenu();
                return mainMenu();
            case ('3'):
                requestsMenu();
                return mainMenu();
            case ('e'):
                return exitProgram();
            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}

//----------------------------------------------------------------------



//1

/**
 * Função imprime o menu principal que permite ao utilizador escolher o tipo de origem e de destino dos voos e inseri-los, com ou sem filtros. Também pode voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::getFlights() {
    cout << endl << "=========GET FLIGHTS=========" << endl;
    cout << endl;
    cout << "Choose the type of origin:" << endl;
    cout << endl << "Options:\n\t1-Airport\n\t2-City\n\t3-Country\n\t4-Coordinates\n\t5-Coordinate & Radius\n\tb-Back\n\te-Exit"<<endl;
    int flag = 1;
    char inputTypeO;
    string inputOrigin;
    int inputRadiusO = 0;
    while (flag){
        cout << "Choose option:";
        cin >> inputTypeO;
        switch (inputTypeO) {
            case ('1'):
                cout << endl << "Insert origin airport:" << endl;
                cin >> inputOrigin;
                if (d_.getAirports().find(inputOrigin) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getFlights();
                }
                flag = 0;
                break;
            case ('2'):
                cout << endl << "Insert origin city: [Format: <city>,<country> (because of repeated city names)]" << endl;
                getline(cin >>ws, inputOrigin);
                if (d_.getCities().find(inputOrigin) == d_.getCities().end()){
                    cout << "\nNot a valid city...\nTry again!\n\n";
                    getFlights();
                }

                flag = 0;
                break;

            case ('3'):
                cout << endl << "Insert origin country:" << endl;
                getline(cin >>ws, inputOrigin);
                if (d_.getCountries().find(inputOrigin) == d_.getCountries().end()){
                    cout << "\nNot a valid country...\nTry again!\n\n";
                    getFlights();
                }
                flag = 0;
                break;

            case ('4'):
                cout << endl << "Insert origin coordinates: [Format: x.(...),y.(...)]" << endl;
                cin >> inputOrigin;
                flag = 0;
                break;

            case ('5'):
                cout << endl << "Insert origin coordinates: [Format: x.(...),y.(...)]" << endl;
                cin >> inputOrigin;
                cout << endl << "Insert radius:" << endl;
                cin >> inputRadiusO;
                flag = 0;
                break;

            case ('b'):
                return;

            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }

    cout << endl;
    cout << "Choose the type of destination:" << endl;
    cout << endl << "Options:\n\t1-Airport\n\t2-City\n\t3-Country\n\t4-Coordinates\n\t5-Coordinates & radius\n\tb-Back\n\te-Exit"<<endl;

    char inputTypeD;
    string inputDestination;
    int inputRadiusD = 0;
    int flag2 = 1;
    while (flag2){
        cout << "Choose option:";
        cin >> inputTypeD;
        switch (inputTypeD) {
            case ('1'):
                cout << endl << "Insert destination airport:" << endl;
                cin >> inputDestination;
                if (d_.getAirports().find(inputDestination) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getFlights();
                }
                flag2 = 0;
                break;

            case ('2'):
                cout << endl << "Insert destination city: [Format: <city>,<country> (because of repeated city names)]" << endl;
                getline(cin >>ws, inputDestination);
                if (d_.getCities().find(inputDestination) == d_.getCities().end()){
                    cout << "\nNot a valid city...\nTry again!\n\n";
                    getFlights();
                }
                flag2 = 0;
                break;
            case ('3'):
                cout << endl << "Insert destination country:" << endl;
                getline(cin >>ws, inputDestination);
                if (d_.getCountries().find(inputDestination) == d_.getCountries().end()){
                    cout << "\nNot a valid country...\nTry again!\n\n";
                    getFlights();
                }
                flag2 = 0;
                break;
            case ('4'):
                cout << endl << "Insert destination coordinates: [Format: x.(...),y.(...)]" << endl;
                cin >> inputDestination;
                flag2 = 0;
                break;
            case ('5'):
                cout << endl << "Insert destination coordinates: [Format: x.(...),y.(...)]" << endl;
                cin >> inputDestination;
                flag2 = 0;
                cout << endl << "Insert radius:" << endl;
                cin >> inputRadiusD;
                break;
            case ('b'):
                return;

            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }

    //filtros
    cout << "Do you want an airline filter?" << endl;
    cout << endl << "Options:\n\t1-Yes\n\t2-No\n\t" <<endl;
    char yn;
    vector<string> filters = {};
    bool flag3 = true;
    while(flag3) {
        cout << "Choose option:";
        cin >> yn;
        switch (yn) {
            case ('1'):
                filters = createVec();
                flag3 = 0;
                break;
            case ('2'):
                flag3 = 0;
                break;
            default:
                cout << "Not a valid option." << endl;
        }
    }

    d_.flight(inputOrigin, inputDestination, inputTypeO-48, inputTypeD-48, filters,inputRadiusO ,inputRadiusD);
    lastPage();
    return welcomePage();
}



/**
 * Função imprime o menu das estatísticas que permite ao utilizador escolher o tipo de estatística que quer obter ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::getStatistics(){
    cout << endl << "=========GET STATISTICS=========" << endl;
    cout << endl;
    cout << "Choose the type of statistics:" << endl;
    cout << endl << "Options:\n\t1-Global\n\t2-Country\n\t3-City\n\t4-Airline\n\t5-Airport\n\tb-Back\n\te-Exit"<<endl;
    char inputType;
    string inputDestination;
    while (true){
        cout << "Choose option:";
        cin >> inputType;
        switch (inputType) {
            case ('1'):
                globalStatistic();
                return getStatistics();
            case ('2'):
                countryStatistic();
                return getStatistics();
            case ('3'):
                cityStatistic();
                return getStatistics();
            case ('4'):
                airlineStatistic();
                return getStatistics();
            case ('5'):
                airportStatistic();
                return getStatistics();
            case ('b'):
                return welcomePage();
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}


/**
 * Função imprime o menu das estatísticas globais que permite ao utilizador escolher a estatística que quer obter ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::globalStatistic(){
    cout << endl << "=========GLOBAL STATISTICS=========" << endl;
    cout << endl;
    cout << "Choose the statistic:" << endl;
    cout << endl << "Options:\n\t1-Total airports\n\t2-Total cities\n\t3-Total countries\n\t4-Total airlines\n\t5-Total flights\n\tb-Back\n\te-Exit"<<endl;

    char option;
    while (true){
        cout << "Choose option:";
        cin >> option;
        switch (option) {
            case ('1'):
                cout << "Number of airports: " << d_.totalAirports() << endl;
                lastPage();
                return getStatistics();
            case ('2'):
                cout << "Number of cities: " << d_.totalCities() << endl;
                lastPage();
                return getStatistics();
            case ('3'):
                cout << "Number of countries: " << d_.totalCountries() << endl;
                lastPage();
                return getStatistics();
            case ('4'):
                cout << "Number of airlines: " << d_.totalAirlines() << endl;
                lastPage();
                return getStatistics();
            case ('5'):
                cout << "Number of flights: " << d_.totalFlights() << endl;
                lastPage();
                return getStatistics();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}


/**
 * Função imprime o menu das estatísticas a nível de país que permite ao utilizador escolher a estatística que quer obter ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::countryStatistic(){
    cout << endl << "=========COUNTRY STATISTICS=========" << endl;
    cout << endl;
    cout << "Insert the name of the country:" << endl;
    string c;
    getline(cin >>ws, c);
    if (d_.getCountries().find(c) == d_.getCountries().end()){
        cout << "\nNot a valid country...\nTry again!\n\n";
        countryStatistic();
    }
    cout << "Choose the statistic:" << endl;
    cout << endl << "Options:\n\t1-Total airports\n\t2-Total flights\n\t3-Total airlines\n\t4-Total destinations\n\t5-Total cities\n\tb-Back\n\te-Exit"<<endl;

    char option;
    while (true){
        cout << "Choose option:";
        cin >> option;
        switch (option) {
            case ('1'):
                cout << "Number of airports: " << d_.nAirports1(c) << endl;
                lastPage();
                return getStatistics();
            case ('2'):
                cout << "Number of flights: " << d_.nFlights1(c) << endl;
                lastPage();
                return getStatistics();
            case ('3'):
                cout << "Number of airlines: " << d_.nAirlines1(c) << endl;
                lastPage();
                return getStatistics();
            case ('4'):
                cout << "Number of destinations: " << d_.nDestinations1(c) << endl;
                lastPage();
                return getStatistics();
            case ('5'):
                cout << "Number of cities: " << d_.nCities1(c) << endl;
                lastPage();
                return getStatistics();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}


/**
 * Função imprime o menu das estatísticas a nível de cidade que permite ao utilizador escolher a estatística que quer obter ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::cityStatistic(){ //DONE
    cout << endl << "=========CITY STATISTICS=========" << endl;
    cout << endl;
    cout << "Insert the name of the city: [Format: <city>,<country> (because of repeated city names)]" << endl;
    string c;
    getline(cin >>ws, c);
    if (d_.getCities().find(c) == d_.getCities().end()){
        cout << "\nNot a valid city...\nTry again!\n\n";
        cityStatistic();
    }
    cout << "Choose the statistic:" << endl;
    cout << endl << "Options:\n\t1-Total airports\n\t2-Total flights\n\t3-Total airlines\n\t4-Total destinations\n\tb-Back\n\te-Exit"<<endl;

    char option;
    while (true){
        cout << "Choose option:";
        cin >> option;
        switch (option) {
            case ('1'):
                cout << "Number of airports: " << d_.nAirports2(c) << endl;
                lastPage();
                return getStatistics();
            case ('2'):
                cout << "Number of flights: " << d_.nFlights2(c) << endl;
                lastPage();
                return getStatistics();
            case ('3'):
                cout << "Number of airlines: " <<  d_.nAirlines2(c) << endl;
                lastPage();
                return getStatistics();
            case ('4'):
                cout << "Number of destinations: " << d_.nDestinations2(c) << endl;
                lastPage();
                return getStatistics();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}


/**
 * Função imprime o menu das estatísticas a nível de companhia aérea que permite ao utilizador escolher a estatística que quer obter ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::airlineStatistic(){
    cout << endl << "=========AIRLINE STATISTICS=========" << endl;
    cout << endl;
    cout << "Insert the code of the airline:" << endl;
    string al;
    cin >> al;
    if (d_.getAirlines().find(al) == d_.getAirlines().end()){
        cout << "\nNot a valid airline...\nTry again!\n\n";
        airlineStatistic();
    }
    cout << "Choose the statistic:" << endl;
    cout << endl << "Options:\n\t1-Total flights\n\t2-Total destinations\n\tb-Back\n\te-Exit"<<endl;

    char option;
    while (true){
        cout << "Choose option:";
        cin >> option;
        switch (option) {
            case ('1'):
                cout << "Number of flights: " << d_.nFlights4(al) << endl;
                lastPage();
                return getStatistics();
            case ('2'):
                cout << "Number of destinations: " << d_.nDestinations4(al) << endl;
                lastPage();
                return getStatistics();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}


/**
 * Função imprime o menu das estatísticas a nível de Aeroporto que permite ao utilizador escolher a estatística que quer obter e o respetivo aeroporto ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::airportStatistic(){ //DONE
    cout << endl << "=========AIRPORT STATISTICS=========" << endl;
    cout << endl;
    string ap;
    cout << "Insert the airport code:" << endl;
    cin >> ap;
    if (d_.getAirports().find(ap) == d_.getAirports().end()){
        cout << "\nNot a valid airport...\nTry again!\n\n";
        airportStatistic();
    }
    cout << endl << "Choose the statistic:" << endl;
    cout << endl << "Options:\n\t1-Total flights\n\t2-Total airlines\n\t3-Total destinations\n\tb-Back\n\te-Exit"<<endl;

    char option;

    while (true){
        cout << "Choose option:";
        cin >> option;

        switch (option) {
            case ('1'):
                cout << "Number of flights:" << d_.nFlights3(ap) << endl;
                lastPage();
                return getStatistics();
            case ('2'):
                cout << "Number of airlines:" << d_.nAirlines3(ap) << endl;
                lastPage();
                return getStatistics();
            case ('3'):
                cout << "Number of destinations:" << d_.nDestinations3(ap) << endl;
                lastPage();
                return getStatistics();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}
/**
 * Função imprime outras informações pertinentes para o utilizador, nomeadamente o diametro do grafo, top-K aeroportos com mais voos e pontos de articulação
 *
 * COMPLEXIDADE: O(n)
 */
void Interface::otherInfo(){
    cout << endl << "=========OTHER INFORMATIONS=========" << endl;
    cout << endl;

    cout << endl << "What do you want to know:" << endl;
    cout << endl << "Options:\n\t1-Diameter\n\t2-Airports with top-K number of flights\n\t3-Articulation Points\n\tb-Back\n\te-Exit"<<endl;

    char option;
    string k;
    vector<string> filters = {};
    bool flag3 = true;
    while (true){
        cout << "Choose option:";
        cin >> option;

        switch (option) {
            case ('1'):
                cout << "The diameter of the graph is: " << d_.diameter() << endl;
                lastPage();
                return otherInfo();
            case ('2'):
                cout << "How many airports with most flights?";
                cin >> k;
                cout << "Top-" << k << " airports with most flights: " ;
                for (auto a: d_.topKairports(stoi(k))){
                    cout << a << " | " ;
                }
                cout << endl;
                lastPage();
                return otherInfo();
            case ('3'):
                cout << "Do you want an airline filter?" << endl;
                cout << endl << "Options:\n\t1-Yes\n\t2-No\n\t" <<endl;
                char yn;
                while(flag3) {
                    cout << "Choose option:";
                    cin >> yn;
                    switch (yn) {
                        case ('1'):
                            filters = createVec();
                            flag3 = 0;
                            break;
                        case ('2'):
                            flag3 = 0;
                            break;
                        default:
                            cout << "Not a valid option." << endl;
                    }
                }
                d_.printArtPoints(filters);
                lastPage();
                return otherInfo();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
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
    cout << "Carolina Viana, up202108802" << endl;
    cout << "Guilherme Monteiro, up202108668" << endl;
    cout << "Sofia Sa, up202108676" << endl;
    cout << endl << endl << "Options:\n\tb-Back\n\te-Exit"<< endl;
    char input;
    while (true) {
        cout << "Choose option:";
        cin >> input;

        switch (input) {
            case ('b'):
                return;
            case ('e'):
                return exitProgram();
            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}

/**
 * Função que permite ao utilizador submeter companhias aéreas como filtros.
 *
 * COMPLEXIDADE: O(n).
 * @return vetor de strings com as companhias de filtros escolhidas pelo utilizador
 */
vector<string> Interface::createVec() {
    bool flag = true;
    vector<string> v = {};
    cout << "Type airlines to filter and hit Enter and 'd' when done.\n\n";

    while(flag){
        string inp = "";
        cin >> inp;
        if ( inp == "d") flag = false;
        else{
            if (d_.getAirlines().find(inp) != d_.getAirlines().end())
                v.push_back(inp);
            else cout << "Not a valid airline."<< endl;
        }
    }
    cout << "Filters applied." << endl;
    return v;
}


/**
 * Função que representa a ultima pagina do menu. Dispoe de duas ultimas opções - voltar atrás e fechar o programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::lastPage() const {
    cout << endl << endl;
    cout << endl << "Options:\n\tb-Back\n\te-Exit"<<endl;
    char input;
    while (true){
        cout << "Choose option:";
        cin >> input;
        switch (input) {
            case ('b'):
                return;
            case ('e'):
                return exitProgram();
            default:
                cout << endl << "Not a valid option" << endl;
        }
    }
}

/**
 * Função que dispoe várias opções de métodos a escolher para o aeroporto escolhido ou voltar atrás no programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::getApMethods(){
    cout << endl << "=========AIRPORT METHODS=========" << endl;
    cout << endl;
    cout << endl << "Choose the method:" << endl;
    cout << endl << "Options:\n\t1-Total flights from airport\n\t2-Total airlines from airport\n\t3-Total city destinations from airport\n\t4-Total country destinations from airport\n\t5-Number of reachable airports with maximum of Y flights\n\t6-Number of reachable cities with maximum of Y flights\n\t7-Number of reachable countries with maximum of Y flights\n\tb-Back\n\te-Exit"<<endl;
    char option;
    int max;
    string ap;
    while (true){
        cout << "Choose option:";
        cin >> option;
        switch (option) {
            case ('1'):
                cout << "Insert the airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Number of flights: " << apm_.nFlightsAirport(ap) << endl;
                lastPage();
                return getApMethods();
            case ('2'):
                cout << "Insert the airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Number of airlines: " << apm_.nAirlines(ap) << endl;
                lastPage();
                return getApMethods();
            case ('3'):
                cout << "Insert the airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Number of city destinations: " << apm_.nCities(ap) << endl;
                lastPage();
                return getApMethods();
            case ('4'):
                cout << "Insert the airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Number of country destinations: " << apm_.nCountries(ap) << endl;
                lastPage();
                return getApMethods();
            case ('5'):
                cout << "Insert the origin airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Insert the maximum number of flights:" << endl;
                cin >> max;
                cout << "Number of reachable airports: " << apm_.nAirportsWithMaxFlights(ap,max) << endl;
                lastPage();
                return getApMethods();
            case ('6'):
                cout << "Insert the origin airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Insert the maximum number of flights:" << endl;
                cin >> max;
                cout << "Number of reachable cities: " << apm_.nCitiesWithMaxFlights(ap,max) << endl;
                lastPage();
                return getApMethods();
            case ('7'):
                cout << "Insert the origin airport code:" << endl;
                cin >> ap;
                if (d_.getAirports().find(ap) == d_.getAirports().end()){
                    cout << "\nNot a valid airport...\nTry again!\n\n";
                    getApMethods();
                }
                cout << "Insert the maximum number of flights:" << endl;
                cin >> max;
                cout << "Number of reachable countries: " << apm_.nCountriesWithMaxFlights(ap,max) << endl;
                lastPage();
                return getApMethods();
            case ('b'):
                return;
            case ('e'):
                return exitProgram();

            default:
                cout << endl << "Not a valid option" << endl;
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