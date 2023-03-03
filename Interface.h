#ifndef DA_PROJECT1_INTERFACE_H
#define DA_PROJECT1_INTERFACE_H


using namespace std;
class Interface {

public:
    Data d_;

    void setData(Data d){d_ = d;}

    Interface();
    void welcomePage();
    void mainMenu();
    void readFiles();


    //-----------------------
    void getFlights();
    void credits() const;

    void exitProgram() const;
    void getStatistics();
    void getApMethods();

    void globalStatistic();
    void countryStatistic();
    void cityStatistic();
    void airlineStatistic();
    void airportStatistic();
    void lastPage() const;
    vector<string> createVec();
    void otherInfo();

};



#endif //DA_PROJECT1_INTERFACE_H
